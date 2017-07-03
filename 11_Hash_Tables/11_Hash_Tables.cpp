#include "iostream"
#include <windows.h>
#include <string>
#include <conio.h>
#include <map>   
#include <stdint.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include "sha.h"
#include "cryptlib.h"
#include "modes.h"
#include "osrng.h"
#include "filters.h"
#include "hex.h"
#include "cbcmac.h"
#include "MyFile.h"

class FileA
{
private:
	std::string _path;
	std::string _altername;
	std::string _creationTime;
	std::string _lastAccessTime;
	std::string _size;
	bool _isdirectory;
	bool _ishidden;
	bool _issystem;
	bool _isarchive;
	bool _iscompressed;


public:
	std::shared_ptr<FileA> _next;
	FileA()
	{

	}
	~FileA()
	{

	}
	std::string GetPath()
	{
		return _path;
	}
	FileA(std::string path, std::string altername, std::string creationTime, std::string lastAccessTime, std::string size, bool isdirectory, bool ishidden, bool issystem, bool isarchive, bool iscompressed)
	{
		this->_path = path;
		this->_altername = altername;
		this->_creationTime = creationTime;
		this->_lastAccessTime = lastAccessTime;
		this->_size = size;
		this->_isdirectory = isdirectory;
		this->_ishidden = ishidden;
		this->_issystem = issystem;
		this->_isarchive = isarchive;
		this->_iscompressed = iscompressed;
	}


	static void end_add(std::shared_ptr<FileA> next, std::shared_ptr<FileA> start)
	{
		std::shared_ptr<FileA> tmp = start;
		while (!(tmp->_next == NULL))
		{
			tmp = tmp->_next;
		}
		tmp->_next = next;
		return;
	}

};

void MakeTable(std::vector<std::shared_ptr<FileA>> &hashTable, bool &flag, std::string dir, int type, int &i, int &j, float &a)
{
	WIN32_FIND_DATAA findData;
	HANDLE hf;

	hf = FindFirstFileA((dir + "*").c_str(), &findData);
	std::string path;
	std::string altername;
	std::stringstream creationTime;
	std::stringstream lastAccessTime;
	bool isdirectory = false;
	bool ishidden = false;
	bool issystem = false;
	bool isarchive = false;
	bool iscompressed = false;
	std::string size;
	if (hf == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		bool isdirectory = false;
		bool ishidden = false;
		bool issystem = false;
		bool isarchive = false;
		bool iscompressed = false;
		char buff[sizeof(findData.cFileName)];
		sprintf(buff, "%s", findData.cFileName);
		std::string path = std::string(buff);
		if (findData.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
		{
			if (path != "." && path != "..") {
				MakeTable(hashTable, flag, dir + path + "\\", 0, i, j, a);
			}
			isdirectory = true;
		}
		if (findData.dwFileAttributes && FILE_ATTRIBUTE_HIDDEN)	{ ishidden = true; }
		if (findData.dwFileAttributes && FILE_ATTRIBUTE_SYSTEM) { issystem = true; }
		if (findData.dwFileAttributes && FILE_ATTRIBUTE_ARCHIVE){ isarchive = true; }
		if (findData.dwFileAttributes && FILE_ATTRIBUTE_COMPRESSED){ iscompressed = true; }
		sprintf(buff, "%s", findData.cAlternateFileName);
		std::string altername = std::string(buff);
		SYSTEMTIME LcreationTime;
		FileTimeToSystemTime(&findData.ftCreationTime, &LcreationTime);
		creationTime << LcreationTime.wHour << ":" << LcreationTime.wMinute << " " << LcreationTime.wDay << "." << LcreationTime.wMonth << "." << LcreationTime.wYear;
		SYSTEMTIME LlastaccessTime;
		FileTimeToSystemTime(&findData.ftLastAccessTime, &LlastaccessTime);
		lastAccessTime << LlastaccessTime.wHour << ":" << LlastaccessTime.wMinute << " " << LlastaccessTime.wDay << "." << LlastaccessTime.wMonth << "." << LlastaccessTime.wYear;
		sprintf(buff, "%x", findData.nFileSizeLow);
		std::string size = std::string(buff);

		std::shared_ptr<FileA> file(new FileA(dir + path, altername, creationTime.str(), lastAccessTime.str(), size, isdirectory, ishidden, issystem, isarchive, iscompressed));
		i++;
		uint16_t index;
		if (flag)
		{
			index = MyHash(dir + path);
		}
		else
		{
			index = SHA256(dir + path);
		}
		if (!hashTable[index])
		{
			hashTable[index] = file;
			j++;

		}
		else
		{
			FileA::end_add(file, hashTable[index]);
		}

		if (i % 50 == 0)
		{
			system("cls");
			std::cout << "Files:" << i << ". A=" << (float)i / j;
		}
	} while (FindNextFileA(hf, &findData) && (((float)i / j) < a));
	FindClose(hf);

}

void SaveTable(std::vector<std::shared_ptr<FileA>> &hashTable, std::string &FileName)
{
	std::ofstream out;
	out.open("..\\..\\" + FileName);
	for (int i = 0; i < hashTable.size(); i++)
	{
		if (hashTable[i] != NULL)
		{
			out << i << " ";
			std::shared_ptr<FileA> tmp = hashTable[i];
			while (tmp != NULL)
			{
				out << tmp->GetPath() << " ";
				tmp = tmp->_next;
			}
			out << "\n\n";
		}
	}
	out.close();
}

void main()
{
	uint32_t start_time = clock();
	std::vector<std::shared_ptr<FileA>>  hashTable;
	hashTable.resize(65536);
	std::string path_dir = "C:\\Program Files (x86)\\";
	path_dir = "C:\\Program Files\\";
	std::cout << "directory = " << std::endl;
	std::cin >> path_dir;
	system("cls");
	bool flag = 0;
	int i = 0;
	int j = 0;
	float a = 1.3;
	std::cout << "SHA(0)\nMyHash(1)\n";
	std::cin >> (bool)flag;
	system("cls");
	std::cout << "A_max =\n";
	std::cin >> a;
	system("cls");

	MakeTable(hashTable, flag, path_dir, 0, i, j, a);
	std::cout << std::endl << clock() - start_time << "  ms" << std::endl;
	if (((double)i / j) > a)
	{
		std::cout << "A_max > A" << std::endl;
		system("pause");

		hashTable.clear();
		hashTable.resize(65536);
		flag = !flag;
		i = 0;
		j = 0;
		start_time = clock();
		MakeTable(hashTable, flag, path_dir, 0, i, j, a);
		std::cout << std::endl << clock() - start_time << "  ms" << std::endl;
	}
	if (((float)i / j) > a)
	{
		std::cout << std::endl << "A_SIZE_ERROR" << std::endl;
	}
	else
	{
		std::string path_save = "";
		std::cout << std::endl << "Save:";
		std::cin >> path_save;
		system("cls");
		start_time = clock();
		SaveTable(hashTable, path_save);
		std::cout << std::endl << clock() - start_time << "  ms" << std::endl;
	}
	system("pause");
	return;
}