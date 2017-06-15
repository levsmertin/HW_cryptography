#include "iostream"
#include <string>
#include "..\..\cryptopp\cryptlib.h"
#include "..\..\cryptopp\osrng.h"
#include <vector>
#pragma comment(lib,"..\\..\\cryptopp\\cryptlib.lib")
#pragma warning(disable : 4996)
#define _CRT_NO_WARNINGS


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




	unsigned __int32 hash(std::vector<byte> &in)
	{
		unsigned int hash = 0;

		for (int i = 0; i<in.size(); i++)
		{
			hash += (unsigned __int32)in.at(i);
			hash -= (hash << 13) | (hash >> 19);
		}

		return hash;
	}


	std::vector<byte> sha256(std::vector<byte> in)
	{
		std::vector<byte> out;
		out.resize(32);
		CryptoPP::SHA256 hash;
		CryptoPP::ArraySource(in.data(), in.size(), true, new CryptoPP::HashFilter(hash, new CryptoPP::ArraySink(&out[0], out.size())));
		return out;
	}







int main()
{
	std::string f_name_out_myhash =  "..\\out\\my_hash";
	std::string f_name_out_sha256 = "..\\out\\sha256";
	std::string f_name_in = "..\\..\\1.docx";
	std::vector<byte> buf;
	std::vector<byte> buf_rez;
	buf.resize(132);
	std::vector<byte>::iterator start;
	std::vector<byte>::iterator finish;
	unsigned __int32 rez;
	FILE* f_my_hash = fopen(f_name_out_myhash.c_str(), "wb");
	FILE* f_sha256 = fopen(f_name_out_sha256.c_str(), "wb");;
	std::cout << "default File = ..\\out\\1.docx \nChange ? (1 - yes, 0 - no)\n";
	int flag = 0;
	std::cin >> flag;
	if (flag == 1)
	{
		std::cout << "File =  \n";
		std::cin >> f_name_in;
	}
	MyFile f_in;
	if (!f_in.Open(f_name_in, "rb")) std::cout << "FILE_OPEN_ERROR";
	
	system("cls");
	std::cout << "my hash"<< std::endl;
	int i_max, hh;
	start = f_in.GetData().begin();
	finish = f_in.GetData().begin();
	finish += 128;
	i_max = (f_in.GetData().size() -128 )/4;
	hh = i_max / 20;
	int random; 
	for (int i=0; i < i_max; i++)
	{			
		if (i%hh == 0) std::cout << "$";
		std::copy(start, finish, buf.begin());

		random = rand();
		memcpy(&buf.at(128), &random, sizeof(unsigned __int32));
		rez = hash(buf);
		fwrite(&rez, sizeof(unsigned __int32), 1, f_my_hash);
		start += 4;
		finish += 4;		
	}
	std::cout << std::endl << "SHA" << std::endl;
	start = f_in.GetData().begin();
	finish = f_in.GetData().begin();
	finish += 32;
	buf.resize(36);
	i_max = (f_in.GetData().size() / 32-1);
	hh = i_max / 20;
	for (int i = 0; i < i_max; i++)
	{
		if (i%hh == 0) std::cout << "$";
		std::copy(start, finish, buf.begin());
		random = rand();
		memcpy(&buf.at(32), &random, 4);
		buf_rez = sha256(buf);
		fwrite(&buf_rez[0], buf_rez.size(), 1, f_sha256);
		start += 32;
		finish += 32;
	}

	std::cout << std::endl;

	f_in.Close(false);
	fclose(f_my_hash);
	fclose(f_sha256);
	system("pause");

	return 0;
	
}

