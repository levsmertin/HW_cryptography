#include "..\..\cryptopp\des.h"
#include "..\..\cryptopp\cryptlib.h"
#include "..\..\cryptopp\modes.h"
#include "..\..\cryptopp\osrng.h"
#include "..\..\cryptopp\filters.h"
#include "..\..\cryptopp\cbcmac.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

	std::vector<byte> E(std::vector<byte> &plaintext, const uint64_t key)
	{
		std::vector<byte> ciphertext;
		ciphertext.resize(plaintext.size() + CryptoPP::DES::BLOCKSIZE);
		CryptoPP::ArraySink cs(&ciphertext[0], ciphertext.size());			
		CryptoPP::ArraySource(plaintext.data(), plaintext.size(), true, 
			new CryptoPP::StreamTransformationFilter(CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption ((byte *)&key, 8),
			new CryptoPP::Redirector(cs)));
		ciphertext.resize(cs.TotalPutLength());
		
		return ciphertext;
	}
	std::vector<byte> D(std::vector<byte> &ciphertext, const uint64_t &key)
	{	
		std::vector<byte> plaintext;
		plaintext.resize(ciphertext.size() + CryptoPP::DES::BLOCKSIZE);
		CryptoPP::ArraySink ds(&plaintext[0], plaintext.size());
		CryptoPP::ArraySource(ciphertext.data(), ciphertext.size(), true, 
			new CryptoPP::StreamTransformationFilter(CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption((byte *)&key, 8),
			new CryptoPP::Redirector(ds)));
		plaintext.resize(ds.TotalPutLength());
		
		return plaintext;
	}

	bool plas(uint64_t &o11, uint64_t &o12, uint64_t o21, uint64_t o22)
	{
		uint64_t b2 = o12 + o22;
		uint64_t b1 = o11 + o21;
		if (b2 < o12) 
		{
			b1++; 
			return true; 
		}
		if (b1 < o11)
		{
			throw 1;
		}
		o11 = b1;
		o12 = b2;		
		return false;
	}

	void print_v(std::vector<byte> &out)
	{
		for (int j = 0; j < out.size(); j++)
		{
			std::cout <<out.at(j);			
		}
		std::cout << std::endl;
	}



int main()
{
	uint64_t shift_max = 2000;
	uint64_t start_key1;
	uint64_t start_key2;
	uint64_t shift2;
	uint64_t my_key1;
	uint64_t my_key2;
	byte plain[] = "I love cryptography";
	std::vector<byte> plain_v;
	std::vector<byte> cipher_v;
	std::vector<byte> decrypt_v;
	
	

	CryptoPP::AutoSeededRandomPool rand(true);
	rand.GenerateBlock((byte *)&start_key1,8);
	rand.GenerateBlock((byte *)&start_key2,8);
	rand.GenerateBlock((byte *)&shift2, 8);
	shift2 = shift2 % (shift_max + 1);

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


	std::cout << std::hex << my_key1 << std::endl << my_key2 << std::endl;


	std::map <std::vector<byte>, uint64_t> d;
	std::map <std::vector<byte>, uint64_t> e;

	uint64_t key1 = start_key1;
	uint64_t key2 = start_key2;
	bool flag = true;
	int i_progress = shift_max / 20;
	for (int i = 0; i < shift_max; i++)
	{
		if (i % i_progress == 0) std::cout << "&";
		e.insert(std::pair <std::vector<byte>, uint64_t >(E(plain_v, key2), key2));
		if (flag) d.insert(std::pair <std::vector<byte>, uint64_t >(D(cipher_v, key1), key1));
		plas(key1, key2, 0, 1);
	}
	std::cout << std::endl;
	uint64_t key2_r = (*d.begin()).second;
	uint64_t key1_r = (*e.find((*d.begin()).first)).second;
	decrypt_v.clear();
	decrypt_v = D(D(cipher_v, key2_r), key1_r);
	
	std::cout << std::hex << key2_r;
	std::cout << std::endl;
	std::cout << std::hex << key1_r;
	std::cout << std::endl;
	print_v(decrypt_v);

	std::cout << std::endl;
	system("pause");
	return 0;

}

