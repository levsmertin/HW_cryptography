//Домашняя работа от 12 мая 2016
//Уланов А БАС-14
#include "iostream"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <string>
#include "..\..\MyFile.h"
#pragma warning(disable : 4996)
#define _CRT_NO_WARNINGS





class  O_T_P
{
public:
	O_T_P()
	{
	}
	~O_T_P()
	{
	}


	void Init(std::string &plaintext, std::string &key, std::string &ciphertext)
	{
		_plaintext = plaintext;
		_key = key;
		_ciphertext = ciphertext;

	}


	std::string Encrypt()
	{
		bool rez = true;
		MyFile plaintext;
		MyFile key;
		MyFile ciphertex;
		rez = rez && plaintext.Open(_plaintext, "rb");
		rez = rez && key.Open(_key, "rb");
		rez = rez && ciphertex.Open(_ciphertext, "wb");
		if (!rez) return "OPEN_FILE_ERROR";
		rez = rez && VerrnamCipher(plaintext, key, ciphertex);
		if (!rez) return "SIZE_FILE_ERROR";
		plaintext.Close(false);
		key.Close(false);
		ciphertex.Close(true);
		return "SUCCESS\n";

	}

	std::string Decript()
	{
		bool rez = true;
		MyFile plaintext;
		MyFile key;
		MyFile ciphertex;
		rez = rez && plaintext.Open(_plaintext, "wb");
		rez = rez && key.Open(_key, "rb");
		rez = rez && ciphertex.Open(_ciphertext, "rb");
		if (!rez) return "OPEN_FILE_ERROR\n";
		rez = rez && VerrnamCipher(ciphertex, key, plaintext);
		if (!rez) return "SIZE_FILE_ERROR\n";
		plaintext.Close(true);
		key.Close(false);
		ciphertex.Close(false);
		return "SUCCESS\n";

	}

	std::string Keygen()

	{
		bool rez = true;
		MyFile plaintext;
		MyFile key;
		rez = rez && plaintext.Open(_plaintext, "rb");
		rez = rez && key.Open(_key, "wb");
		if (!rez) return "OPEN_FILE_ERROR\n";
		srand(time(NULL));
		rand() % 0 + 255;
		char random_char;
		unsigned int i = 0;
		int i_max = plaintext.GetData().size();
		int i_progress = i_max / 20;
		for (; i < i_max; i++)
		{
			if (i % i_progress == 0) std::cout << "&";
			fwrite(&random_char, 1, 1, key.GetFile());
		}
		std::cout << "\n";
		plaintext.Close(false);
		key.Close(false);
		return "SUCCESS\n";

	}

private:
	std::string _plaintext;
	std::string _key;
	std::string _ciphertext;

	bool VerrnamCipher(MyFile &oper1, MyFile &oper2, MyFile &rez)
	{

		unsigned int i = 0;
		bool ret = false;
		if (oper1.GetData().size() == oper2.GetData().size())
		{
			ret = true;
			int i_max = oper1.GetData().size();
			int i_progress = i_max / 20;
			for (; i < i_max; i++)
			{
				if (i % i_progress == 0) std::cout << "&";
				rez.GetData().push_back(oper1.GetData().at(i) ^ oper2.GetData().at(i));
			}
			std::cout << "\n";
		}
		return ret;

	}

};

int main()
{
	std::string plaintext_file = "";
	std::string key_file = "";
	std::string ciphertext_file = "";
	O_T_P my_OTP;
	char mode;
	bool flag_exit = true;
	do
	{
		system("cls");
		std::cout << " One-time pad\n 1 - encrypt \n 2 - decrypt\n 3 - generate a key\n 4 - exit  \n";
		std::cin >> mode;

		switch (mode)
		{
		case '1':
			std::cout << "plaintext = \n";
			std::cin >> plaintext_file;
			std::cout << "key = \n";
			std::cin >> key_file;
			std::cout << "ciphertext = \n";
			std::cin >> ciphertext_file;
			my_OTP.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_OTP.Encrypt();
			system("pause");
			break;
			
		case '2':

			std::cout << "ciphertext = \n";
			std::cin >> ciphertext_file;
			std::cout << "key = \n";
			std::cin >> key_file;
			std::cout << "plaintext = \n";
			std::cin >> plaintext_file;
			my_OTP.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_OTP.Decript();
			system("pause");
			break;


		case '3':

			std::cout << "plaintext = \n";
			std::cin >> plaintext_file;
			std::cout << "key filename = \n";
			std::cin >> key_file;
			my_OTP.Init(plaintext_file, key_file, ciphertext_file);
			std::cout << my_OTP.Keygen();
			system("pause");
			break;


		case '4': flag_exit = false; break;

		default:
			break;
		}


	} while (flag_exit);
	system("pause");



}
