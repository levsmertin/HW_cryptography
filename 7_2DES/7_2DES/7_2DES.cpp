#include "stdafx.h"
#include "iostream"
#include <string>
#include "..\cryptopp565\des.h"
#include "..\cryptopp565\cryptlib.h"
#include "..\cryptopp565\modes.h"
#include "..\cryptopp565\osrng.h"
#include "..\cryptopp565\filters.h"
#include "..\cryptopp565\cbcmac.h"
#include <vector>
#include <map>



	//fwrite(_data.data(), _data.size(), 1, _file)

	std::vector<byte> E(std::vector<byte> &plaintext, byte key[])
	{

		std::vector<byte> ciphertext;
		ciphertext.resize(plaintext.size() + CryptoPP::DES::BLOCKSIZE);
		CryptoPP::ArraySink cs(&ciphertext[0], ciphertext.size());
					
		CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption E(key, 8);
		CryptoPP::ArraySource(plaintext.data(), plaintext.size(), true, new CryptoPP::StreamTransformationFilter(E, new CryptoPP::Redirector(cs)));
			
		ciphertext.resize(cs.TotalPutLength());
		
		return ciphertext;

	}
	std::vector<byte> D(std::vector<byte> &ciphertext, byte key[])
	{

		std::vector<byte> plaintext;
		
		plaintext.resize(ciphertext.size() + CryptoPP::DES::BLOCKSIZE);
		CryptoPP::ArraySink ds(&plaintext[0], plaintext.size());
		
		CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption D(key, 8);
		CryptoPP::ArraySource(ciphertext.data(), ciphertext.size(), true, new CryptoPP::StreamTransformationFilter(D, new CryptoPP::Redirector(ds)));
			
		plaintext.resize(ds.TotalPutLength());
		
		return plaintext;
	}
	bool next(byte key1[])
	{
		bool flag = true;
		for (int i = 0; i < 8 && flag; i++)
		{
			if (key1[i] != 255) 
			{
				key1[i]++; 
				flag = false;
				return flag;
			}
			else
			{
				key1[i] = 0;
			}
		}
		return flag;		
	}
	bool plass(byte O_1[] , byte O_2[])
	{
		
		int buf = 0;
		bool flag = false;
		for (int i = 0; i < 8; i++)
		{
			buf = 0;
			buf += O_1[i];
			buf += O_2[i];
			if (flag)
			{
				buf++;
				flag = false;
			}
			if (buf <255)
			{
				O_1[i] = buf;
			}
			else
			{
				O_1[i] = buf%256;
				flag = true;
			}
		}
		return flag;
	}
	void int_in_array_byte(int key, byte key_mass[])
	{
		for (int i = 0; i < 8; i++)
		{
			key_mass[i] = key%256;
			key /= 256;
		}
	}

	int binpow(int a, int n) {
		int res = 1;
		while (n)
		if (n & 1) {
			res *= a;
			--n;
		}
		else {
			a *= a;
			n >>= 1;
		}
		return res;
	}

	unsigned __int32 array_byte_to_int( const byte key_mass[])
	{
		/*unsigned __int32 buf=0, ret=0;
		for (int i = 0; i < 8; i++)
		{
			buf = key_mass[i];
			buf << (i * 8);
			ret += buf;
		}

		return ret;*/

		unsigned __int32 buf=0, ret=0;
		for (int i = 0; i < 8; i++)
		{
		buf = binpow(key_mass[i],i+1);
		ret += buf;
		}
		return ret;
	}


int main()
{
	int key_min = 65536;
	int key_max = 262144;
	byte key_1[8];
	byte key_2[8];
	byte key_1_next[8];
	byte key_2_next[8];
	byte shift[8];
	char my_p_ [] = "I love cryptography";
	std::vector<byte> my_pl;
	std::vector<byte> my_c;

	for (int j = 0; j < 20; j++)
	{
		my_pl.push_back(my_p_[j]);
	}

	byte k[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
	for (int p = 0; p < 50; p++)
	{
		
		next(k);
		std::cout << array_byte_to_int(k) << std::endl;
	}


	srand(time(NULL));
	rand() % 0 + 262144;
	int i_shift = rand();
	rand() % 0 + 256;
	int_in_array_byte(i_shift, shift);

	for (int i = 0; i < 8; i++)
	{
		key_1[i] = rand();
		key_1_next[i] = key_1[i];
		key_2[i] = rand();
		key_2_next[i] = key_2[i];
	}
	if (plass(key_1, shift)) next(key_2);
	
	my_c = E(E(my_pl, key_1), key_2);


	std::map <std::vector<byte>, unsigned __int32> d;
	std::map <std::vector<byte>, unsigned __int32> e;
	
	bool flag = true;
	
	int i_max = 262144;
	int i_progress = i_max / 20;
	for (int i = 0; i < 10; i++)
	{			
		e.insert(std::pair <std::vector<byte>, unsigned __int32>(E(my_pl, key_1_next), array_byte_to_int(key_1_next)));
		std::cout << array_byte_to_int(key_1_next) << std::endl;
		if (flag)
		{
			d.insert(std::pair <std::vector<byte>, unsigned __int32>(D(my_c, key_2_next), array_byte_to_int(key_2_next)));
			std::cout << array_byte_to_int(key_2_next) << std::endl;
			flag = false;
		}
		if (next(key_1_next))
		{ 
			next(key_2_next); 
			flag = true; 
		}
		if (i % i_progress == 0) std::cout << "&";
	}

	std::cout << std::endl << e.size();
	std::cout << std::endl << d.size();

	
	
	 system("pause");




}

