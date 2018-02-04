#include<iostream>
#include<time.h>
#include<string>
#include<windows.h>

#include"arrayMaker.h"
#include"softTemplate.h"
using namespace std;

namespace util {
	/*
	  校验数组是否有序
	  传入: 数组 以及 数组长度
	  返回: 1 为有序 0 为无序
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
	通用排序时间检测函数
	传入: 数组长度 数组 排序的名字 排序的函数
	输出: 校验结果 以及 排序时间
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
	五个算法的运行时间测试
	传入: 长度
	*/
	void testAllSoft(int len) {
		int *arr = maker::makeArray(len);
		int *arr2 = maker::copyArray(arr, len);
		// arr, arr2无序
		util::timeTester(len, arr, "buddle_soft", soft::bubble_soft);
		// arr有序
		delete[] arr;
		int *arr3 = maker::copyArray(arr2, len);
		// arr2, arr3 无序
		util::timeTester(len, arr2, "selection_soft", soft::selection_soft);
		// arr2 有序
		delete[] arr2;
		int *arr4 = maker::copyArray(arr3, len);
		// arr3, arr4 无序
		util::timeTester(len, arr3, "merge_soft", soft::merge_soft);
		// arr3 有序
		delete[] arr3;
		int *arr5 = maker::copyArray(arr4, len);
		// arr4, arr5 无序
		util::timeTester(len, arr4, "quick_soft", soft::quick_soft);
		// arr4 有序
		delete[] arr4;
		util::timeTester(len, arr5, "insert_soft", soft::insert_soft);
		// arr5 有序
		delete[] arr5;
	}
}