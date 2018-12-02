// apan_lab6.cpp: ���������� ����� ����� ��� ����������� ����������.
//�������� ���������, ����������� ��� �������� ������, ���������� � ������ ���������. 
//������ ����� � ������� ������� ��������� ����� ��������� �������� ����������� �������, ���������� �� n ���������,
//������� �� ��������� 0..500. ������ ����� �������� ��������� �������� ������� � ������������ � ��������, 
//��������� � ��������������� ��������. ������ ���������������� � ������� ��������.
//����� ������������ ������ (�� ��������) ��������� �������.

#include "stdafx.h"
#include <iostream> 
#include <windows.h> 
using namespace std;
HANDLE hSemaphore;
long a[10];
unsigned long b = 1;
int thread01()
{
	for (int i = 0; i < 10; i++)
	{
		a[i] = 0 + rand() % 50;
		cout << a[i] << "  ";
		Sleep(100);
	}
	Sleep(500);
	cout << endl;
	ReleaseSemaphore(hSemaphore, 10, NULL);
	return 0;
}
int thread02()
{
	for (int i = 0; i < 10; i++)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		if (a[i] % 2 == 0 && a[i]!=0) b*= a[i];
		cout << b << endl;
	}
	return 0;
}
int main()
{
	hSemaphore = CreateSemaphore(NULL, 0, 10, L"MySemaphore");
	if (hSemaphore == NULL)
		cout << "Create semaphore failed" << GetLastError() << endl;
	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
	if (hTh01 == NULL) return GetLastError();
	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
	if (hTh02 == NULL) return GetLastError();
	cin.get();
	CloseHandle(hSemaphore);
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	return 0;
}

