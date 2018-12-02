// apan_lab5.cpp: определяет точку входа для консольного приложения.
// Написать программу, запускающую два дочерних потока. 
//Первый поток с помощью датчика случайных чисел заполняет элементы массива, состоящего из 10 чисел. 
//После заполнения всех элементов, второй поток изменяет элемен-ты массива в соответствии с заданием, 
//указанным в соответствующем варианте. Вывести на экран исходный и результирующий массивы. 
//Задание выполнить для трех различных массивов. Потоки синхронизировать с помощью мьютекса.
//Поместить в нулевую позицию среднее арифметическое всех остальных элементов массива.

#include "stdafx.h"
#include "iostream"
#include "windows.h"
using namespace std;
const int n = 10;
double a[n]; double b;
int thread01()
{
	HANDLE mutex = OpenMutex(SYNCHRONIZE, false, L"MyMutex");
	for (int k = 0; k<3; k++)
	{
		WaitForSingleObject(mutex, INFINITE);
		for (int i = 0; i < n; i++) {
			a[i] = -10 + rand() % 20;
		}
		ReleaseMutex(mutex);
		Sleep(200);
	}

	CloseHandle(mutex);
	return 0;
}
int thread02()
{
	HANDLE mutex = OpenMutex(SYNCHRONIZE, false, L"MyMutex");
	for (int k = 0; k < 3; k++)
	{
		b = 0;
		WaitForSingleObject(mutex, INFINITE);
		cout << "Original array:" << endl;
		for (int i = 0; i < n; i++) cout << a[i] << " ";
		cout << endl;
		for (int i = 1; i<n; i++)
			b += a[i];
		b /= n - 1;
		int tmp = a[0];
		a[0] = b;
		b = tmp;
		cout << "Resulting array:" << endl;
		for (int i = 0; i < n; i++) cout << a[i] << " ";
		cout << endl;
		ReleaseMutex(mutex);
		Sleep(200);
		cout << endl;
	}

	CloseHandle(mutex);
	return 0;
}
int main()
{
	HANDLE hMutex, hTh01, hTh02;
	if ((hMutex = CreateMutex(NULL, false, L"MyMutex")) == NULL) GetLastError();
	if ((hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL)) == NULL) return 0;
	if ((hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL)) == NULL) return 0;
	cin.get();
	CloseHandle(hMutex);
	CloseHandle(&hTh01);
	CloseHandle(&hTh02);
	return 0;
}
