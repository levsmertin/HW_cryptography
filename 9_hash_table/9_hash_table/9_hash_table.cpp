// 9_hash_table.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Vector>
#include <cstdint>


class  FILE_ATRIBUT
{
public:

	FILE_ATRIBUT();
	std::vector <uint8_t> Key();

};

class  HASH_TABLE
{
public:
	
	HASH_TABLE()
	{
		table.resize(65537);

	}
	~ HASH_TABLE();

	void Add(FILE_ATRIBUT new_element)
	{
		table.at(hash1(new_element.Key())).push_back(new_element);

	}
	void Get_Referencevalues();

private:
	std::vector < std::vector<FILE_ATRIBUT>> table;

	uint16_t hash1(std::vector <uint8_t> key);
	uint16_t hash2(std::vector <uint8_t> key);
};



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

