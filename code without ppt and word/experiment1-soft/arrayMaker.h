#pragma once
#include<iostream>
#include<time.h>
#include<random>
using namespace std;

namespace maker {
	/*
	�������1 - len �����Σ�����len���ȵ�����
	*/
	int* makeArray(int len) {
		default_random_engine e;
		e.seed((unsigned)time(NULL));
		int *arr = new int[len];
		for (int i = 0; i < len; i++) {
			arr[i] = (int)e();
		}
		return arr;
	}
	/*
	������������
	*/
	int* copyArray(int* arr, int len) {
		int* arr2 = new int[len];
		for (int i = 0; i < len; i++)
			arr2[i] = arr[i];
		return arr2;
	}
}