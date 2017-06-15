#include "iostream"
#include <string>
#include <conio.h>
#include <string>
#include "..\..\cryptopp\rsa.h"
#include "..\..\cryptopp\cryptlib.h"
#include "..\..\cryptopp\modes.h"
#include "..\..\cryptopp\osrng.h"
#include "..\..\cryptopp\filters.h"
#include "..\..\cryptopp\cbcmac.h"
#include "..\..\cryptopp\base64.h"
#include "..\..\cryptopp\files.h"
#include "comutil.h"
#include <vector>
#include "..\..\MyFile.h"
#pragma comment(lib,"..\\..\\cryptopp\\cryptlib.lib")
#pragma warning(disable : 4996)
#define _CRT_NO_WARNINGS



 class RSA

{
public:
	static bool keygen(std::string f_public, std::string f_privat)
	{
		bool rez = true;
		MyFile privatekey;
		MyFile publickey;
		rez = rez && privatekey.Open(f_privat, "wb");
		rez = rez && publickey.Open(f_public, "wb");
		if (!rez) return false;
		CryptoPP::AutoSeededRandomPool rng;
		std::string privateKey_s;
		std::string	publicKey_s;
		CryptoPP::InvertibleRSAFunction privateKey;
		privateKey.Initialize(rng, 1024);
		CryptoPP::RSAFunction publicKey(privateKey);

		CryptoPP::Base64Encoder pr(new CryptoPP::StringSink(privateKey_s), false);
		privateKey.DEREncode(pr);
		pr.MessageEnd();



		CryptoPP::Base64Encoder pu(new CryptoPP::StringSink(publicKey_s), false);
		publicKey.DEREncode(pu);
		pu.MessageEnd();

		privatekey.GetData().resize(privateKey_s.size());
		memcpy(&privatekey.GetData()[0], &privateKey_s[0], privateKey_s.size());

		publickey.GetData().resize(publicKey_s.size());
		memcpy(&publickey.GetData()[0], &publicKey_s[0], publicKey_s.size());
		//for (int i = 0; i < publicKey_s.size(); i++)
		//{
		//	publickey.GetData().push_back(publicKey_s[i]);
		//}

		privatekey.Close(true);
		publickey.Close(true);
		return rez;
	}
	static bool Decrypt(std::string plain, std::string my_key, std::string cipher)
	{

		bool rez = true;
		MyFile plaintext;
		MyFile key;
		MyFile ciphertext;
		rez = rez && plaintext.Open(plain, "wb");
		rez = rez && key.Open(my_key, "rb");
		rez = rez && ciphertext.Open(cipher, "rb");
		if (!rez) return false;
		std::string Key_s = "";
		std::string cipher_s = "";
		std::string plain_s = "";
		Key_s.resize(key.GetData().size());
		memcpy(&Key_s[0], &key.GetData()[0], Key_s.size());
		//CryptoPP::StringSource K(Key_s, true, new CryptoPP::Base64Decoder);
		CryptoPP::RSAES_OAEP_SHA_Decryptor D(CryptoPP::StringSource (Key_s, true, new CryptoPP::Base64Decoder));
		CryptoPP::AutoSeededRandomPool rng;
		int block_size = 128;
		std::vector<byte> tmp;
		tmp.resize(block_size);
		int i_max = ciphertext.GetData().size() / block_size;
		int i_progress = i_max / 20;
		for (int i = 0; i < i_max; i++)
		{
			if (i % i_progress == 0) std::cout << "&";
			plain_s = "";
			cipher_s = "";
			for (int j = 0; j < block_size; j++)
			{
				tmp.at(j) = ciphertext.GetData().at(i * block_size + j);
			}
			for each  (byte var in tmp)
			{
				cipher_s += var;
			}
			CryptoPP::StringSource(cipher_s, true, new CryptoPP::PK_DecryptorFilter(rng, D, new CryptoPP::StringSink(plain_s)));
			for (int i = 0; i < plain_s.size(); i++)
			{
				plaintext.GetData().push_back(plain_s[i]);
			}
		}
		std::cout << std::endl;
		plaintext.Close(true);
		ciphertext.Close(false);
		key.Close(false);
		return true;
	}
	static bool Encrypt(std::string plain, std::string my_key, std::string cipher)
	{
		CryptoPP::AutoSeededRandomPool rng;
		bool rez = true;
		MyFile plaintext;
		MyFile key;
		MyFile ciphertext;
		rez = rez && plaintext.Open(plain, "rb");
		rez = rez && key.Open(my_key, "rb");
		rez = rez && ciphertext.Open(cipher, "wb");
		if (!rez) return false;
		std::string Key_s = "";
		std::string cipher_s = "";
		std::string plain_s = "";

		Key_s.resize(key.GetData().size());
		memcpy(&Key_s[0], &key.GetData()[0], Key_s.size());



		//CryptoPP::StringSource K(Key_s, true, new CryptoPP::Base64Decoder);
		CryptoPP::RSAES_OAEP_SHA_Encryptor E(CryptoPP::StringSource (Key_s, true, new CryptoPP::Base64Decoder));
		CryptoPP::AutoSeededRandomPool rnd;


		int block_size = 86;
		int i_max = plaintext.GetData().size() / block_size;
		//byte *current = &plaintext.GetData()[0];
		int current = 0;
		int k = 0;
		int i_progress = i_max / 20;
		for (int i = 0; i < i_max; i++)
		{
			//memcpy(&plain_s, &plaintext.GetData()[i*block_size], block_size);
			if (i % i_progress == 0) std::cout << "&";
			current += block_size;
			for (; k < current; k++)
			{
				plain_s += plaintext.GetData()[k];
			}


			CryptoPP::StringSource(plain_s, true, new CryptoPP::PK_EncryptorFilter(rnd, E, new CryptoPP::StringSink(cipher_s)));



			for (int i = 0; i < cipher_s.size(); i++)
			{
				ciphertext.GetData().push_back(cipher_s[i]);
			}
			plain_s = "";
			cipher_s = "";
		}

		int last_size = plaintext.GetData().size() - (i_max*block_size);
		//memcpy(&plain_s, current, last_size);

		current += last_size;
		for (; k < current; k++)
		{
			plain_s += plaintext.GetData().at(k);
		}
		CryptoPP::StringSource(plain_s, true, new CryptoPP::PK_EncryptorFilter(rnd, E, new CryptoPP::StringSink(cipher_s)));

		for (int i = 0; i < cipher_s.size(); i++)
		{
			ciphertext.GetData().push_back(cipher_s[i]);
		}
		std::cout << std::endl;
		plaintext.Close(false);
		ciphertext.Close(true);
		key.Close(false);

		return rez;
	}
};





void main()
{
	std::string f_public = "..\\out\\public";
	std::string f_privat = "..\\out\\privat";
	std::string f_plain = "..\\..\\1.docx";
	std::string f_cipher = "..\\out\\cipher";
	std::string f_decrypt = "..\\out\\decript.docx";
	bool flag;
	
	std::cout << "default \npublic key file =..\\out\\public\n";
	std::cout << "privat key file =..\\out\\public\n";
	std::cout << "plaintext file = ..\\out\\1.docx\n";
	std::cout << "ciphertext file = ..\\out\\cipher\n";
	std::cout << "decript file = ..\\out\\decript.docx\n";
	std::cout << "Change ? (1 - yes, 0 - no)\n";
	int default_flag = 0;
	std::cin >> default_flag;
	system("cls");
	if (default_flag == 1)
	{
		std::cout << "public key file =  \n";
		std::cin >> f_public;
		std::cout << "privat key file =  \n";
		std::cin >> f_privat;
		std::cout << "plaintext file =  \n";
		std::cin >> f_plain;
		std::cout << "ciphertext file =  \n";
		std::cin >> f_cipher;
		std::cout << "decript file =  \n";
		std::cin >> f_decrypt;

	}
	system("cls");


	flag = RSA::keygen(f_public, f_privat);
	if (!flag) std::cout <<  "OPEN_FILE_ERROR\n";
	else 
	{
		std::cout << "Key generation : success" << std::endl;
	}
	flag = RSA::Encrypt(f_plain, f_public, f_cipher);
	if (!flag) std::cout << "OPEN_FILE_ERROR\n";
	else
	{
		std::cout << "Encrypt : success" << std::endl;
	}
	flag = RSA::Decrypt(f_decrypt, f_privat, f_cipher);
	if (!flag) std::cout << "OPEN_FILE_ERROR\n";
	else
	{
		std::cout << "Decrypt : success" << std::endl;
	}



	system("pause");

}