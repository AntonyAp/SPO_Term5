#include "pch.h"
#include <iostream>
#include <windows.h>
using namespace std;
struct Data {
	char Name[30];
	int Number;
	int Discount;
};
bool FileRead()
{
	Data data;
	DWORD dwBytesRead;
	HANDLE file = CreateFile(L"E:\\University\\5 сем\\labs\\apan_lab2\\Visitors.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		cout << "Error" << endl;
		CloseHandle(file);
		return 0;
	}
	while (ReadFile(file, &data, sizeof(data), &dwBytesRead, NULL) && dwBytesRead != 0)
	{
		cout << data.Name << " " << data.Number << " " << data.Discount << endl;
	}
	FlushFileBuffers(file);
	CloseHandle(file);
	return 1;
}
int main()
{
	char number[4];
	cout << "Main process started" << endl;
	if(!FileRead()) return 0;
	cout << "Enter number of struct ";
	cin >> number;
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	PROCESS_INFORMATION processInformation;
	ZeroMemory(&processInformation,sizeof(processInformation));
	if (!CreateProcess(L"E:\\University\\5 сем\\labs\\apan_lab2\\Debug\\Daughter.exe",
		(LPWSTR)number,
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&startupInfo,
		&processInformation)
		) {
		cout << "error"; return 0;
	}
	WaitForSingleObject(processInformation.hProcess, INFINITE);
	if (!FileRead()) return 0;
	cout << "MainProcess finished" << endl;
	CloseHandle(processInformation.hProcess);
	CloseHandle(processInformation.hThread);
	return 0;
}
