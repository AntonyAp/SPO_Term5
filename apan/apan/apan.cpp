// apan.cpp: определяет точку входа для консольного приложения.
//В магазине составлен список людей, которым выдана карта постоянного покупателя. 
//Каждая запись этого списка содержит номер карточки, ФИО, предоставляемую скидку. 
//Вывести информацию о покупателях, имеющих 10 %-ную скидку в магазине

#include "stdafx.h"
#include "iostream"
#include "windows.h"
using namespace std;
struct Customers
{
	char CardNumber[10];
	char CustomerName[15];
	char Discount[3];
};
void Creating(LPCTSTR);
void Addition(HANDLE);
void Output(LPCTSTR);
int main()
{
	LPCTSTR file = L"NewFile.txt";
	Creating(file);
	Output(file);
	return 0;
}
void Creating(LPCTSTR file)
{
	HANDLE fl = CreateFile(
		file,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (fl == INVALID_HANDLE_VALUE)
		cout << "ERROR" << endl;
	else
	{
		cout << "File is created" << endl;
		SetFilePointer(fl, 0, NULL, FILE_END);
		Addition(fl);
		CloseHandle(fl);
	}
}
void Addition(HANDLE fl)
{
	Customers d; char c;
	DWORD BytesWritten;
	do
	{
		cout << "Enter the card number: ";  cin >> d.CardNumber;
		cout << "Enter the name of customer: "; cin >> d.CustomerName;
		cout << "Enter the discount(%): "; cin >> d.Discount;
		WriteFile(fl, &d.CardNumber, strlen(d.CardNumber), &BytesWritten, NULL);
		WriteFile(fl, "\t", 1, NULL, NULL);
		WriteFile(fl, &d.CustomerName, strlen(d.CustomerName), &BytesWritten, NULL);
		WriteFile(fl, "\t", 1, NULL, NULL);
		WriteFile(fl, &d.Discount, strlen(d.Discount), &BytesWritten, NULL);
		WriteFile(fl, "\r\n", 2, &BytesWritten, NULL);
		cout << "Will you enter more? (y/n) "; cin >> c;
		cout << endl;
	} while (c == 'y');
}
void Output(LPCTSTR file)
{
	HANDLE fl = CreateFile
	(file, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == fl)
		cerr << "Error of opening" << endl;
	int i = 0;
	DWORD dwBytesRead;
	char d[256];
	HANDLE fl1 = CreateFile(
		L"NewFile1.txt",
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int j = 0;
	while (ReadFile(fl, &d[i], sizeof(d[i]), &dwBytesRead, (LPOVERLAPPED)NULL) == TRUE && dwBytesRead != 0)
	{
		if (d[i] == '\r')
		{
			if (d[i - 1] == '0' && d[i-2] == '1')
			{
				for (int k = j; k < i+1; k++)
				{
 					cout << d[k];
					WriteFile(fl1, &d[k], sizeof(d[k]), NULL, NULL);
 				}
				cout << endl;
				WriteFile(fl1, "\r\n", 2, NULL, NULL);
				j = i + 2;
			}
			else j = i + 2;
		}
		i++;
	}
	CloseHandle(fl);
	CloseHandle(fl1);
}

