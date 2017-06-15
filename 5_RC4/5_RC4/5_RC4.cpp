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

class RC4

{
public:
	RC4()
	{

	}
	~RC4()
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
		metadata_shedule(key);
		my_XOR(plaintext, ciphertex);
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
		metadata_shedule(key);
		my_XOR(ciphertex, plaintext);
		plaintext.Close(true);
		key.Close(false);
		ciphertex.Close(false);
		return "SUCCESS\n";
	}

private:
	std::string _plaintext;
	std::string _key;
	std::string _ciphertext;
	unsigned char S[256];
	int I = 0;
	int J = 0;

	void metadata_shedule(MyFile &key)
	{
		I = 0;
		for (; I < 256; I++)
		{
			S[I] = I;
		}
		J = 0;
		I = 0;
		for (; I < 256; I++)
		{
			J = (J + S[I] + key.GetData().at(I % key.GetData().size())) % 256;
			swap_S();
		}
		J = 0;
		I = 0;
	}
	char get_key_i()
	{
		I = (I + 1) % 256;
		J = (J + S[I]) % 256;
		swap_S();
		return S[(S[I] + S[J]) % 256];
	}
	void swap_S()
	{
		unsigned char tmp = S[I];
		S[I] = S[J];
		S[J] = tmp;

	}
	void my_XOR(MyFile &IN, MyFile &OUT)

	{
		int i_max = IN.GetData().size();
		int i_progress = i_max / 20;
		for (int k = 0; k < i_max; k++)
		{
			if (k % i_progress == 0) std::cout << "&";
			OUT.GetData().push_back(IN.GetData().at(k) ^ get_key_i());
		}
		std::cout << "\n";
	}

};


void main()
{
	std::string plaintext_file = "..\\..\\1.docx";
	std::string key_file = "..\\key_for_rc4";
	std::string ciphertext_file = "..\\out\\cipher";
	std::string decrypt_file = "..\\out\\decript.docx";
	RC4 my_RS4;
	std::cout << "default \nkey file = ..\\out\\key" << std::endl;
	std::cout << "plaintext file = ..\\..\\1.docx" << std::endl;
	std::cout << "ciphertext file = ..\\out\\cipher" << std::endl;
	std::cout << "decript file = ..\\out\\decript.docx" << std::endl;
	std::cout << "use? (1 - yes, 0 - no)\n";
	int default_flag = 0;
	std::cin >> default_flag;
	system("cls");
	if (default_flag == 1)
	{
		my_RS4.Init(plaintext_file, key_file, ciphertext_file);
		std::cout << "Encrypt :" << my_RS4.Encrypt();
		my_RS4.Init(decrypt_file, key_file, ciphertext_file);
		std::cout << "Decrypt :"<< my_RS4.Decript();
	}
	else
	{

		char mode;
		bool flag_exit = true;
		do
		{
			system("cls");
			std::cout << " RC4\n 1 - encrypt \n 2 - decrypt\n 3 - exit  \n";
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
				my_RS4.Init(plaintext_file, key_file, ciphertext_file);
				std::cout << my_RS4.Encrypt();
				system("pause");
				break;

			case '2':

				std::cout << "ciphertext = \n";
				std::cin >> ciphertext_file;
				std::cout << "key = \n";
				std::cin >> key_file;
				std::cout << "plaintext = \n";
				std::cin >> plaintext_file;
				my_RS4.Init(plaintext_file, key_file, ciphertext_file);
				std::cout << my_RS4.Decript();
				system("pause");
				break;




			case '3': flag_exit = false; break;

			default:
				break;
			}


		} while (flag_exit);

	}
	system("pause");


}

