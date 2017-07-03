#include "iostream"
#include <string>
#include "des.h"
#include "cryptlib.h"
#include "modes.h"
#include "osrng.h"
#include "filters.h"
#include "cbcmac.h"
#include <vector>
#include "MyFile.h"


class DES
{
public:
	DES()
	{
		_plaintext = "";
		_key = "";
		_ciphertext = "";
	}
	~DES()
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
		byte new_key[CryptoPP::DES::DEFAULT_KEYLENGTH];
		rand.GenerateBlock(new_key, sizeof (new_key));
		for each (byte i in new_key)
		{
			key.GetData().push_back(i);
		}

		if (cipher_mode != '0')
		{

			byte new_iv[CryptoPP::DES::BLOCKSIZE];
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
		if (!(cipher_mode > '5' || cipher_mode < '1') && (key.GetData().size() != CryptoPP::DES::DEFAULT_KEYLENGTH + CryptoPP::DES::BLOCKSIZE)) return "KEY_SIZE_ERROR\n";
		if (cipher_mode == '0' && key.GetData().size() != CryptoPP::DES::DEFAULT_KEYLENGTH) return "KEY_SIZE_ERROR\n";

		byte file_key[CryptoPP::DES::DEFAULT_KEYLENGTH];
		byte file_iv[CryptoPP::DES::BLOCKSIZE];
		int i = 0;

		for (; i < CryptoPP::DES::DEFAULT_KEYLENGTH; i++)
		{
			file_key[i] = key.GetData().at(i);
		}
		if (cipher_mode != '0')
		{
			for (int j = 0; i < CryptoPP::DES::DEFAULT_KEYLENGTH + CryptoPP::DES::BLOCKSIZE; i++)
			{
				file_iv[j] = key.GetData().at(i);
				j++;
			}
		}
		ciphertext.GetData().resize(plaintext.GetData().size() + CryptoPP::DES::BLOCKSIZE);
		CryptoPP::ArraySink cs(&ciphertext.GetData()[0], ciphertext.GetData().size());
		switch (cipher_mode)
		{
		case '0':

		{
					CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption E(file_key, sizeof (file_key));
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '1':

		{
					CryptoPP::CBC_Mode<CryptoPP::DES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '2':
		{
					CryptoPP::CFB_Mode<CryptoPP::DES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '3':
		{
					CryptoPP::OFB_Mode<CryptoPP::DES>::Encryption E(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(plaintext.GetData().data(), plaintext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
					break;
		}
		case '4':
		{
					CryptoPP::CTR_Mode<CryptoPP::DES>::Encryption E(file_key, sizeof (file_key), file_iv);
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
		if (!(cipher_mode > '5' || cipher_mode < '1') && (key.GetData().size() != CryptoPP::DES::DEFAULT_KEYLENGTH + CryptoPP::DES::BLOCKSIZE)) return "KEY_SIZE_ERROR\n";
		if (cipher_mode == '0' && key.GetData().size() != CryptoPP::DES::DEFAULT_KEYLENGTH) return "KEY_SIZE_ERROR\n";
		byte file_key[CryptoPP::DES::DEFAULT_KEYLENGTH];
		byte file_iv[CryptoPP::DES::BLOCKSIZE];
		int i = 0;
		for (; i < CryptoPP::DES::DEFAULT_KEYLENGTH; i++)
		{
			file_key[i] = key.GetData().at(i);
		}


		if (cipher_mode != '0')
		{
			for (int j = 0; i < CryptoPP::DES::DEFAULT_KEYLENGTH + CryptoPP::DES::BLOCKSIZE; i++)
			{
				file_iv[j] = key.GetData().at(i);
				j++;
			}
		}
		plaintext.GetData().resize(ciphertext.GetData().size() + CryptoPP::DES::BLOCKSIZE);
		CryptoPP::ArraySink ds(&plaintext.GetData()[0], plaintext.GetData().size());
		switch (cipher_mode)
		{
		case '0':

		{
					CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption D(file_key, sizeof (file_key));
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '1':

		{
					CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '2':
		{
					CryptoPP::CFB_Mode<CryptoPP::DES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '3':
		{
					CryptoPP::OFB_Mode<CryptoPP::DES>::Decryption D(file_key, sizeof (file_key), file_iv);
					CryptoPP::ArraySource(ciphertext.GetData().data(), ciphertext.GetData().size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
					break;
		}
		case '4':
		{
					CryptoPP::CTR_Mode<CryptoPP::DES>::Decryption D(file_key, sizeof (file_key), file_iv);
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

void main()
{
	std::string plaintext_file;
	std::string key_file;
	std::string ciphertext_file;
	char cipher_mode = 0;
	DES my_DES;
	char mode;
	bool flag_exit = false;


	do
	{
		system("cls");
		std::cout << "DES (data encryption standard)\n 1 - encrypt \n 2 - decrypt\n 3 - generate a key\n 4 - exit  \n";
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
			my_DES.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_DES.Encrypt(cipher_mode);
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
			my_DES.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_DES.Decrypt(cipher_mode);
			system("pause");
			break;


		case '3':
			std::cout << "key filename = \n";
			std::cin >> key_file;
			my_DES.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << "Block cipher mode of operation\n 0:ECB 1:CBC 2:CFB 3:OFB 4:CRT\n";
			std::cin >> cipher_mode;
			std::cout << my_DES.Keygen(cipher_mode);
			system("pause");
			break;

		case '4': flag_exit = true; break;
		default:
			break;
		}


	} while (!flag_exit);
	system("pause");
	return;
}

