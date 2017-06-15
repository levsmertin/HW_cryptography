#include "stdafx.h"
#include "iostream"
#include <string>
#include "..\..\cryptopp\aes.h"
#include "..\..\cryptopp\cryptlib.h"
#include "..\..\cryptopp\modes.h"
#include "..\..\cryptopp\osrng.h"
#include "..\..\cryptopp\filters.h"
#include "..\..\cryptopp\cbcmac.h"
#include <vector>
#include "..\..\MyFile.h"
#pragma comment(lib,"..\\..\\cryptopp\\cryptlib.lib")
#pragma warning(disable : 4996)
#define _CRT_NO_WARNINGS


class AES
{
public:
	AES()
	{
		_plaintext = "";
		_key = "";
		_ciphertext = "";
	}
	~AES()
	{

	}

	void Init(std::string &plaintext, std::string &key, std::string &ciphertext)
	{
		_plaintext = plaintext;
		_key = key;
		_ciphertext = ciphertext;

	}

	std::string Keygen(char &cipher_mode)
	{
		if (cipher_mode > '5' || cipher_mode < '0') return "MODE_SELECTION_ERROR\n";
		bool rez = true;
		MyFile key;
		rez = rez && key.Open(_key, "wb");
		if (!rez) return "OPEN_FILE_ERROR";
		CryptoPP::AutoSeededRandomPool rand(true);
		byte new_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
		rand.GenerateBlock(new_key, sizeof (new_key));
		for each (byte i in new_key)
		{
			key.GetData().push_back(i);
		}

		if (cipher_mode != '0')
		{

			byte new_iv[CryptoPP::AES::BLOCKSIZE];
			rand.GenerateBlock(new_iv, sizeof (new_iv));
			for each (byte i in new_iv)
			{
				key.GetData().push_back(i);
			}
		}

		key.Close(true);
		return "SUCCESS\n";
	}



	std::string Encrypt(char &cipher_mode)
	{
		if (cipher_mode > '5' || cipher_mode < '0') return "MODE_SELECTION_ERROR\n";
		bool rez = true;
		MyFile plaintext;
		MyFile key;
		MyFile ciphertext;
		rez = rez && plaintext.Open(_plaintext, "rb");
		rez = rez && key.Open(_key, "rb");
		rez = rez && ciphertext.Open(_ciphertext, "wb");
		if (!rez) return "OPEN_FILE_ERROR\n";
		if (!(cipher_mode > '5' || cipher_mode < '1') && (key.GetData().size() != CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE)) return "KEY_SIZE_ERROR\n";
		if (cipher_mode == '0' && key.GetData().size() != CryptoPP::AES::DEFAULT_KEYLENGTH) return "KEY_SIZE_ERROR\n";

		byte file_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
		byte file_iv[CryptoPP::AES::BLOCKSIZE];
		int i = 0;

		for (; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
		{
			file_key[i] = key.GetData().at(i);
		}
		if (cipher_mode != '0')
		{
			for (int j = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE; i++)
			{
				file_iv[j] = key.GetData().at(i);
				j++;
			}
		}
		ciphertext.GetData().resize(plaintext.GetData().size() + CryptoPP::AES::BLOCKSIZE);
		CryptoPP::ArraySink cs(&ciphertext.GetData()[0], ciphertext.GetData().size());
		switch (cipher_mode)
		{
		case '0':

		{
					CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption E(file_key, sizeof (file_key));
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '1':

		{
					CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '2':
		{
					CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '3':
		{
					CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '4':
		{
					CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		default:
			break;
		}
		ciphertext.GetData().resize(cs.TotalPutLength());
		plaintext.Close(false);
		key.Close(false);
		ciphertext.Close(true);
		return "SUCCESS\n";
	}

	std::string Decrypt(char &cipher_mode)
	{
		if (cipher_mode > '5' || cipher_mode < '0') return "MODE_SELECTION_ERROR\n";
		bool rez = true;
		MyFile plaintext;
		MyFile key;
		MyFile ciphertext;
		rez = rez && plaintext.Open(_plaintext, "wb");
		rez = rez && key.Open(_key, "rb");
		rez = rez && ciphertext.Open(_ciphertext, "rb");
		if (!rez) return "OPEN_FILE_ERROR\n";
		if (!(cipher_mode > '5' || cipher_mode < '1') && (key.GetData().size() != CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE)) return "KEY_SIZE_ERROR\n";
		if (cipher_mode == '0' && key.GetData().size() != CryptoPP::AES::DEFAULT_KEYLENGTH) return "KEY_SIZE_ERROR\n";
		byte file_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
		byte file_iv[CryptoPP::AES::BLOCKSIZE];
		int i = 0;
		for (; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
		{
			file_key[i] = key.GetData().at(i);
		}


		if (cipher_mode != '0')
		{
			for (int j = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE; i++)
			{
				file_iv[j] = key.GetData().at(i);
				j++;
			}
		}
		plaintext.GetData().resize(ciphertext.GetData().size() + CryptoPP::AES::BLOCKSIZE);
		CryptoPP::ArraySink ds(&plaintext.GetData()[0], plaintext.GetData().size());
		switch (cipher_mode)
		{
		case '0':

		{
					CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption D(file_key, sizeof (file_key));
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '1':

		{
					CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '2':
		{
					CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '3':
		{
					CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '4':
		{
					CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		default:
			break;
		}

		plaintext.GetData().resize(ds.TotalPutLength());
		plaintext.Close(true);
		key.Close(false);
		ciphertext.Close(false);
		return "SUCCESS\n";

	}

private:
	std::string _plaintext;
	std::string _key;
	std::string _ciphertext;

};


int _tmain(int argc, _TCHAR* argv[])
{
	std::string plaintext_file;
	std::string key_file;
	std::string ciphertext_file;
	char cipher_mode = 0;
	AES my_AES;
	char mode;
	bool flag_exit = false;


	do
	{
		system("cls");
		std::cout << "AES (advanced encryption standard)\n 1 - encrypt \n 2 - decrypt\n 3 - generate a key\n 4 - exit  \n";
		std::cin >> mode;

		switch (mode)
		{
		case '1':
			std::cout << "Block cipher mode of operation\n 0:ECB 1:CBC 2:CFB 3:OFB 4:CRT\n";
			std::cin >> cipher_mode;
			std::cout << "plaintext = \n";
			std::cin >> plaintext_file;
			std::cout << "key = \n";
			std::cin >> key_file;
			std::cout << "ciphertext = \n";
			std::cin >> ciphertext_file;
			my_AES.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_AES.Encrypt(cipher_mode);
			system("pause");
			break;

		case '2':
			std::cout << "Block cipher mode of operation\n 0:ECB 1:CBC 2:CFB 3:OFB 4:CRT\n";
			std::cin >> cipher_mode;
			std::cout << "ciphertext = \n";
			std::cin >> ciphertext_file;
			std::cout << "key = \n";
			std::cin >> key_file;
			std::cout << "plaintext = \n";
			std::cin >> plaintext_file;
			my_AES.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_AES.Decrypt(cipher_mode);
			system("pause");
			break;


		case '3':
			std::cout << "key filename = \n";
			std::cin >> key_file;
			my_AES.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << "Block cipher mode of operation\n 0:ECB 1:CBC 2:CFB 3:OFB 4:CRT\n";
			std::cin >> cipher_mode;
			std::cout << my_AES.Keygen(cipher_mode);
			system("pause");
			break;

		case '4': flag_exit = true; break;
		default:
			break;
		}


	} while (!flag_exit);
	system("pause");
}
