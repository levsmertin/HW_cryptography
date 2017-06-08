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

	




int _tmain(int argc, _TCHAR* argv[])
{
	std::string f_name;
	std::vector<byte> buf;
	buf.resize(513);
	std::vector<byte>::iterator start;
	std::vector<byte>::iterator finish;
	unsigned __int32 rez;
	FILE* f_out;
	f_out = fopen("out", "wb");
	std::cout << "File =  \n";
	std::cin >> f_name;
	MyFile f_in;
	if (!f_in.Open(f_name, "rb")) std::cout << "FILE_OPEN_ERROR";
	start = f_in.GetData().begin();
	finish = f_in.GetData().begin();
	finish += 5;
	int i_max = f_in.GetData().size() / 512;
	for (int i=0; i < i_max; i++)
	{
		std::copy(start, finish, buf.begin());
		rez = hash(buf);
		fwrite(&rez, sizeof(unsigned __int32), 1, f_out);
		start += 512;
		finish += 512;
		//buf.clear();
		
	}
	f_in.Close(false);
	fclose(f_out);
	
	system("pause");
	
}

