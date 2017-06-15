#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <windows.h>
#include <conio.h>

bool Set_Process(HANDLE hStdOut, std::map <int, std::wstring> &map_proc)
{
	PROCESSENTRY32 peProcessEntry;
	HANDLE  hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) 	{ return false; }
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &peProcessEntry);
	do
	{
		map_proc.insert(std::pair<int, std::wstring>(peProcessEntry.th32ProcessID, peProcessEntry.szExeFile));
	} while (Process32Next(hSnapshot, &peProcessEntry));
	CloseHandle(hSnapshot);
	return true;
}

void main()
{
	HANDLE  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	std::map <int, std::wstring> map_before;
	std::map <int, std::wstring> map_now;
	std::map <int, std::wstring> map_buf;
	std::map <int, std::wstring>::iterator cur_buf;

	if (!Set_Process(hStdOut, map_before)) std::cout << "Error";
	bool flag_exit = true;
	while (flag_exit)
	{
		flag_exit = !_kbhit();
		if (!Set_Process(hStdOut, map_now)) std::cout << "Error";
		set_difference(map_before.begin(), map_before.end(), map_now.begin(),
			map_now.end(), std::inserter(map_buf, map_buf.begin()));
		for (cur_buf = map_buf.begin(); cur_buf != map_buf.end(); cur_buf++)
		{
			std::wcout << "closed    id " << (*cur_buf).first << "    Execute File   " << (*cur_buf).second << std::endl;
		}
		map_buf.clear();
		set_difference(map_now.begin(), map_now.end(), map_before.begin(),
			map_before.end(), std::inserter(map_buf, map_buf.begin()));
		for (cur_buf = map_buf.begin(); cur_buf != map_buf.end(); cur_buf++)
		{
			std::wcout << "started   id " << (*cur_buf).first << "    Execute File   " << (*cur_buf).second << std::endl;
		}
		map_before = map_now;
		map_now.clear();
		map_buf.clear();
		Sleep(100);
	}

}
