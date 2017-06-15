#pragma once
#include <vector>

#pragma warning(disable : 4996)
#define _CRT_NO_WARNINGS
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