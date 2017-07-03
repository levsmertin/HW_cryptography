#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include <MyLib.h>
	uint8_t plas(uint64_t &o11, uint64_t &o12, uint64_t o21, uint64_t o22)
	{
		int ret = 0;
		uint64_t b2 = o12 + o22;
		uint64_t b1 = o11 + o21;
		uint8_t *buf;
		buf = (uint8_t *)&b2;
		buf += 7;
		if (*buf != 0) 
		{
			b1 += *buf;
			return *buf;			
		}
		o11 = b1;
		o12 = b2;			
	}
	void print_v(std::vector<byte> &out)
	{
		for (int j = 0; j < out.size(); j++)
		{
			std::cout <<out.at(j);			
		}
		std::cout << std::endl;
	}
	void GenerateTable(uint64_t key_start, std::map <std::vector<byte>, uint64_t> &table, 
		uint64_t shift, 
		std::vector<byte> text, 
		std::vector<byte>(*F)(std::vector<byte> &, const uint64_t))
	{

		for (int i = 0; i < shift; i++)
		{
			table.insert(std::pair <std::vector<byte>, uint64_t >(F(text, key_start), key_start));
			key_start++;
		}
	}
	void Search(std::map <std::vector<byte>, uint64_t> table1, std::map <std::vector<byte>, uint64_t> &table2, uint64_t &key2_r, uint64_t &key1_r)
	{

		if (table2.find((*table1.begin()).first) != table2.end())
		{
			key2_r = (*table1.begin()).second;
			key1_r = (*table2.find((*table1.begin()).first)).second;
		}
		
	}
	
	int main()
{
	uint64_t shift_max1 = 0;//262144;
	uint64_t shift_max2 = 262144;//262144;
	uint64_t start_key1=0;
	uint64_t start_key2=0;
	uint64_t shift2=0;
	uint64_t my_key1=0;
	uint64_t my_key2=0;
	uint64_t for_print1 = 0;
	uint64_t for_print2 = 0;
	byte plain[] = "I love cryptography";
	std::vector<byte> plain_v;
	std::vector<byte> cipher_v;
	std::vector<byte> decrypt_v;
	
	CryptoPP::AutoSeededRandomPool rand(true);
	rand.GenerateBlock((byte *)&start_key1,7);
	rand.GenerateBlock((byte *)&start_key2,7);
	rand.GenerateBlock((byte *)&shift2, 8);
	shift2 = shift2 % (shift_max2 + 1);
	
	my_key1 = start_key1;
	my_key2 = start_key2;
	plas(my_key1, my_key2,0,shift2);

	plain_v.resize(sizeof (plain));
	memcpy(plain_v.data(), plain, sizeof(plain));
	cipher_v = E(E(plain_v, my_key2), my_key1);
	decrypt_v = D(D(cipher_v, my_key1), my_key2);
	print_v(plain_v);
	print_v(cipher_v);
	print_v(decrypt_v);


	KeyConvert(my_key1, for_print1);
	KeyConvert(my_key2, for_print2);
	std::cout << std::hex << for_print1 << std::endl;
	std::cout << std::hex << for_print2 << std::endl;
	
	uint64_t shift1 = 1 + shift_max1;
	std::map <std::vector<byte>, uint64_t> d;
	std::map <std::vector<byte>, uint64_t> e1;
	std::map <std::vector<byte>, uint64_t> e2;
	std::map <std::vector<byte>, uint64_t> e3;
	std::map <std::vector<byte>, uint64_t> e4;
	uint64_t key1 = start_key1;
	uint64_t key2 = start_key2;
	std::vector<byte>(*ENC)(std::vector<byte> &, const uint64_t) = NULL;
	std::vector<byte>(*DCR)(std::vector<byte> &, const uint64_t) = NULL;
	ENC = &E;
	DCR = &D;
	std::thread Thread1(GenerateTable, key2, std::ref(e1), shift_max2 / 4, plain_v, ENC);
	std::cout << "Create tables...\n";
	std::thread Thread2(GenerateTable, key2 + (shift_max2 / 4), std::ref(e2), shift_max2 / 4, plain_v, ENC);
	std::cout << "Create tables...\n";
	std::thread Thread3(GenerateTable, key2 + (shift_max2 / 4) * 2, std::ref(e3), shift_max2 / 4, plain_v, ENC);
	std::cout << "Create tables...\n";
	std::thread Thread4(GenerateTable, key2 + (shift_max2 / 4) * 3 + 3, std::ref(e4), shift_max2 / 4, plain_v, ENC);
	std::cout << "Create tables...\n";
	std::thread Thread5(GenerateTable, key1, std::ref(d), shift1, cipher_v, DCR);
	std::cout << "Create tables...\n";
	Thread1.join();
	Thread2.join();
	Thread3.join();
	Thread4.join();
	Thread5.join();
	std::cout << std::endl;
	uint64_t key2_r = 0;
    uint64_t key1_r = 0;
	std::cout << "Search...\n";
	Search(d, e1, key2_r, key1_r);
	Search(d, e2, key2_r, key1_r);
	Search(d, e3, key2_r, key1_r);
	Search(d, e4, key2_r, key1_r);
	decrypt_v.clear();
	decrypt_v = D(D(cipher_v, key2_r), key1_r);
	KeyConvert(key1_r, for_print1);
	KeyConvert(key2_r, for_print2);
	std::cout << std::hex << for_print2 << std::endl;
	std::cout << std::hex << for_print1 << std::endl;
	print_v(decrypt_v);
	std::cout << std::endl;
	system("pause");
	return 0;

}

