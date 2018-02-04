#include<iostream>
#include<time.h>
#include<string>
#include<windows.h>

#include"arrayMaker.h"
#include"softTemplate.h"
using namespace std;

namespace util {
	/*
	  У�������Ƿ�����
	  ����: ���� �Լ� ���鳤��
	  ����: 1 Ϊ���� 0 Ϊ����
	*/
	template<typename T>
	int softChecker(T *arr, int len) {
		for (int i = 0; i < len-1; i++) {
			if (arr[i] > arr[i + 1]) {
				return 0;
			}
		}
		return 1;
	}
	/*
	ͨ������ʱ���⺯��
	����: ���鳤�� ���� ��������� ����ĺ���
	���: У���� �Լ� ����ʱ��
	*/
	template<typename T>
	void timeTester(int len, T *arr,string softName, void (*soft)(T*, int)) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		soft(arr, len);
		QueryPerformanceCounter(&EndTime);
		if (!softChecker(arr, len)) {
			cout << "soft error name:" << softName << " with len " << len << endl;
		}
		cout << "soft:" << softName << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by len " << len << endl;
	}

	/*
	����㷨������ʱ�����
	����: ����
	*/
	void testAllSoft(int len) {
		int *arr = maker::makeArray(len);
		int *arr2 = maker::copyArray(arr, len);
		// arr, arr2����
		util::timeTester(len, arr, "buddle_soft", soft::bubble_soft);
		// arr����
		delete[] arr;
		int *arr3 = maker::copyArray(arr2, len);
		// arr2, arr3 ����
		util::timeTester(len, arr2, "selection_soft", soft::selection_soft);
		// arr2 ����
		delete[] arr2;
		int *arr4 = maker::copyArray(arr3, len);
		// arr3, arr4 ����
		util::timeTester(len, arr3, "merge_soft", soft::merge_soft);
		// arr3 ����
		delete[] arr3;
		int *arr5 = maker::copyArray(arr4, len);
		// arr4, arr5 ����
		util::timeTester(len, arr4, "quick_soft", soft::quick_soft);
		// arr4 ����
		delete[] arr4;
		util::timeTester(len, arr5, "insert_soft", soft::insert_soft);
		// arr5 ����
		delete[] arr5;
	}
}