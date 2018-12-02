// apan_lab4.cpp: определяет точку входа для консольного приложения.
//Поместить в нулевую позицию среднее арифметическое всех остальных элементов массива.

#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;
int n;
long * a, b;
void Output()
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}
void thread01()
{
	while (true)
	{
		Sleep(1000);
		for (int i = 0; i < n; i++)
		{
			a[i] = -150 + rand() % 300;
		}

	}
}
void thread02()
{
	while (true)
	{
		Sleep(1000);
		b = 0;
		cout << "Original array: ";
		Output();
		for(int i = 1; i<n;i++)
			b += a[i];
		b /= n-1;
		InterlockedExchange(&a[0], b);
		cout << "Changed array: ";
		Output();
		cout << endl;
	}
}
int main()
{
	cout << "Enter the number of elements: ";
	cin >> n;
	a = new long[n];
	HANDLE hTh01; DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)thread01, NULL, 0, &IDTh01);
	if (hTh01 == NULL) return GetLastError();
	HANDLE hTh02; DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)thread02, NULL, 0, &IDTh02);
	if (hTh02 == NULL) return GetLastError();
	char c;
	do
	{
		cout << "Enter 'q' to exit" << endl;
		cin >> c;
	} while (c != 'q');
	TerminateThread(hTh01, 0);
	TerminateThread(hTh02, 0);
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	delete a;
	return 0;
}
