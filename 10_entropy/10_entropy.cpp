#define ZLIB_WINAPI
#include "iostream"
#include <string>
#include <vector>
#include <cstdint>
#include <string.h>
#include <stdlib.h>
#include "MyFile.h"
#include "zlib.h"
#include "zconf.h"


int c_8(MyFile &_object, std::vector<int> &dictionary)
{
	uint8_t*  var = (uint8_t *)&_object.GetData().at(0);
	int i_max = _object.GetData().size();
	for (int i = 0; i < i_max; i++)
	{
		dictionary.at(*var)++;
		var++;
	}
	return i_max;
}

int c_32(MyFile &_object, std::vector<int> &dictionary)
{
	uint32_t *var = (uint32_t *)&_object.GetData().at(0);
	int i_max = _object.GetData().size() / 4;
	for (int i = 0; i < i_max; i++)
	{
		dictionary[*var]++;
		var++;
	}
	return i_max;
}
int c_16(MyFile &_object, std::vector<int> &dictionary)
{
	uint16_t *var = (uint16_t *)&_object.GetData().at(0);
	int i_max = _object.GetData().size() / 2;
	for (int i = 0; i < i_max; i++)
	{
		dictionary.at(*var)++;
		var++;
	}
	return i_max;
}


int c_16_2(MyFile &_object, std::vector<int> &dictionary)
{
	uint8_t *pointer = (uint8_t *)&_object.GetData().at(0);
	uint16_t *var;
	int i_max = _object.GetData().size() - 1;
	for (int i = 0; i < i_max; i++)
	{
		var = (uint16_t *)pointer;
		dictionary.at(*var)++;
		pointer++;
	}
	return i_max;
}



double entropy(std::vector<int> &dictionary, int size_of_text, double size_entropy)
{
	double result = 0;
	double temp = 0;
	for (int j = 0; j < dictionary.size(); j++)
	{
		temp = (double)dictionary[j] / (double)size_of_text;
		if (temp != 0)result += temp * (log(temp) / log(size_entropy));
	}
	return -result;
}


double by_archiving(std::vector<unsigned char> &text)
{
	std::vector<int> buf;
	buf.resize((int)text.size());
	unsigned long len_text = text.size();
	unsigned long len_rez = buf.size();
	compress((Bytef*)&buf[0], &len_rez, (Bytef*)&text[0], len_text);
	return (double)len_rez / (double)len_text;


}



void for_main(std::string &file_name)
{

	std::vector<int> dictionary8;
	std::vector<int> dictionary16;
	std::vector<int> dictionary16_2;
	dictionary8.resize(256);
	dictionary16.resize(65536);
	dictionary16_2.resize(65536);
	MyFile text;
	if (text.Open(file_name, "rb"))
	{
		//system("cls");
		c_8(text, dictionary8);
		c_16(text, dictionary16);
		c_16_2(text, dictionary16_2);
		std::cout << " 8:" << entropy(dictionary8, text.GetData().size(), 8.0) << std::endl;
		std::cout << " 16:" << entropy(dictionary16, text.GetData().size() / 2, 16.0) << std::endl;
		std::cout << " 16_2:" << entropy(dictionary16_2, text.GetData().size() - 1, 16.0) << std::endl;
		std::cout << " compress:" << by_archiving(text.GetData()) << std::endl;
	}
	else
	{
		std::cout << "OPEN_FILE_ERROR";
	}
	std::cout << std::endl;
	text.Close(false);
}



int main()
{

	std::string	original = "..\\..\\6_hash\\out\\1.docx";
	std::string	my_hash = "..\\..\\6_hash\\out\\my_hash";
	std::string	sha = "..\\..\\6_hash\\out\\sha256";


	std::cout << "default \noriginal = ..\\..\\6_hash\\out\\1.docx,\nmy_hash = ..\\..\\6_hash\\out\\my_hash\nsha = ..\\..\\6_hash\\out\\sha256\nChange ? (1 - yes, 0 - no)\n";
	int flag = 0;
	std::cin >> flag;
	if (flag == 1)
	{
		std::cout << "original =  \n";
		std::cin >> original;
		std::cout << "my_hash =  \n";
		std::cin >> original;
		std::cout << "sha =  \n";
		std::cin >> original;
	}
	system("cls");


	std::cout << original << std::endl;
	for_main(original);

	std::cout << my_hash << std::endl;
	for_main(my_hash);

	std::cout << sha << std::endl;
	for_main(sha);


	system("pause");

	return 0;
}
