#pragma once
#include <vector>
#include "..\third-party\src\cryptopp\sha.h"
#include "..\third-party\src\cryptopp\cryptlib.h"
#include "..\third-party\src\cryptopp\modes.h"
#include "..\third-party\src\cryptopp\osrng.h"
#include "..\third-party\src\cryptopp\filters.h"
#include "..\third-party\src\cryptopp\hex.h"
#include "..\third-party\src\cryptopp\cbcmac.h"
#include "..\third-party\src\cryptopp\des.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"..\\third-party\\lib\\cryptlib.lib")
typedef unsigned char byte;
class MyFile
{
public:
	MyFile()
		: _file(NULL)
	{

	}
	~MyFile()
	{
		Close(false);
	}

	bool Open(std::string &name, std::string type)

	{
		if (type != "wb" && type != "rb") return false;
		_type = type; 
		_file = fopen(name.c_str(), type.c_str());
		if (_file != NULL&& type == "rb")
		{
			_size = Size(_file);
			_data.resize(_size);
			fread(_data.data(), 1, _size, _file);
			return !_data.empty();
		}
		if (_file != NULL && type == "wb") return true;
		return false;
	}
	void Close(bool write_vector)
	{
		if (_type == "wb"&& write_vector) fwrite(_data.data(), _data.size(), 1, _file);
		fclose(_file);
		_data.clear();
	}
	int static Size(FILE* file)
	{

		int size = 0;
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
		return size;
	}

	std::vector<byte> &GetData() { return _data; }
	FILE*  &GetFile() { return _file; }
private:
	std::string _type;
	std::vector<byte> _data;
	FILE* _file;
	int _size = 1;
};


void KeyConvert(uint64_t  in, uint64_t &out)
{
	out = 0;
	uint64_t mask;
	mask = 0xFE;
	for (int i = 0; i < 7; i++)
	{
		out |= in&mask;
		mask = mask << 8;
	}

}
std::vector<byte> E(std::vector<byte> &plaintext, const uint64_t key_in)
{
	uint64_t key;
	KeyConvert(key_in, key);
	std::vector<byte> ciphertext;
	ciphertext.resize(plaintext.size() + CryptoPP::DES::BLOCKSIZE);
	CryptoPP::ArraySink cs(&ciphertext[0], ciphertext.size());
	CryptoPP::ArraySource(plaintext.data(), plaintext.size(), true,
		new CryptoPP::StreamTransformationFilter(CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption((byte *)&key, 8),
		new CryptoPP::Redirector(cs)));
	ciphertext.resize(cs.TotalPutLength());

	return ciphertext;
}
std::vector<byte> D(std::vector<byte> &ciphertext, uint64_t key_in)
{
	uint64_t key;
	KeyConvert(key_in, key);
	std::vector<byte> plaintext;
	plaintext.resize(ciphertext.size() + CryptoPP::DES::BLOCKSIZE);
	CryptoPP::ArraySink ds(&plaintext[0], plaintext.size());
	CryptoPP::ArraySource(ciphertext.data(), ciphertext.size(), true,
		new CryptoPP::StreamTransformationFilter(CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption((byte *)&key, 8),
		new CryptoPP::Redirector(ds)));
	plaintext.resize(ds.TotalPutLength());

	return plaintext;
}

	uint16_t MyHash(std::string &in)
	{
		unsigned int hash = 0;
		for (int i = 0; i<in.size(); i++)
		{
			hash += (unsigned __int32)in.at(i);
			hash -= (hash << 13) | (hash >> 19);
		}

		return (uint16_t)hash;
	}
	uint16_t SHA256(std::string &in)
	{
		std::vector<byte> out;
		out.resize(32);
		CryptoPP::SHA256 hash;
		CryptoPP::ArraySource((byte*)in.data(), in.size(), true, new CryptoPP::HashFilter(hash, new CryptoPP::ArraySink(&out[0], out.size())));
		uint16_t * tmp = (uint16_t *)out.data();
		return *tmp;
	}



