// apan_lab3.cpp: определяет точку входа для консольного приложения.
//Приостановить выполнение первого потокa при достижении счетчиком второго потока значения 100 и возобновить 
//выполнение при достижении счетчиком третьего потока значения 300

#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;
HANDLE hTh01, hTh02, hTh03;
void thread01(DWORD n) // Первый поток
{
	while (true) {
		n++; Sleep(20);
	}
}
void thread02(DWORD n)// Второй поток
{;
	while (true)
	{
		n++; Sleep(40);
		if (n == 100)
		{
			cout << "Thread 1 is suspended" << endl;
			SuspendThread(hTh01);
		}
	}
}
void thread03(DWORD n)
{
	while (true) {
		n++; Sleep(60);
		if (n == 300)
		{
			ResumeThread(hTh01);
			cout << "Thread 1 is running" << endl;
		}
	}
}
int main()
{
	int n = 0; int k = 0; int p = 0;
	DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, (void *)n, 0, &IDTh01);
	if (hTh01 == NULL) return GetLastError();
	DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, (void *)k, 0, &IDTh02);
	if (hTh02 == NULL) return GetLastError();
	DWORD IDTh03;
	hTh03 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread03, (void *)p, 0, &IDTh03);
	if (hTh03 == NULL) return GetLastError();
	char c;
	do
	{
		cout << "Enter 'q' to exit" << endl;
		cin >> c;
	} while (c != 'q');
	TerminateThread(hTh01, 0);
	TerminateThread(hTh02, 0);
	TerminateThread(hTh03, 0);
	// Закрытие потоков
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	CloseHandle(hTh03);
}


