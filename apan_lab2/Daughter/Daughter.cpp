#include "pch.h"
#include <iostream>
#include <windows.h>
using namespace std;

struct student
{
	char Name[30];
	int Number;
	int Discount;
};
int main( char *s[])
{
	cout << "Daughter process started" << endl;
	HANDLE file = CreateFile(L"E:\\University\\5 сем\\labs\\apan_lab2\\Visitors.txt",
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file == INVALID_HANDLE_VALUE) {
		cout << "Error" << endl;
		CloseHandle(file);
		return 0;
	}
	DWORD dwBytesWrite;
	student data;
	char name[30];
	SetFilePointer(file, (atoi(s[0]) - 1) * sizeof(data), NULL, FILE_BEGIN);
	cout << "New name: ";
	cin >> name;
	cout << "New number: ";
	cin >> data.Number;
	cout << "New Discount: ";
	cin >> data.Discount;
	cout << "\n";
	strcpy_s(data.Name, sizeof(data.Name), name);
	WriteFile(file, &data, sizeof(data), &dwBytesWrite, NULL);
	cout << "Daughter process finished" << endl;
	CloseHandle(file);
	return 0;
}