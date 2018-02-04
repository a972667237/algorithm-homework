#pragma once
#include<iostream>
#include<vector>
#include<windows.h>
#include<string>
#include"pair.h"
#include"pointMaker.h"
using namespace std;

namespace testPair {
	void timeTester(vector<pair<double, double>> vec, string solve_name, void (* solve_pair)(vector<pair<double, double>>)) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		solve_pair(vec);
		QueryPerformanceCounter(&EndTime);
		cout << "solve:" << solve_name << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by len " << vec.size() << endl;
	}

	void testAll(int len) {
		vector<pair<double, double>> a;
		a = maker::randomPoint(len, (double)-len, (double)len);
		vector<pair<double, double>> b = a;
		testPair::timeTester(a, "traversal_pair", solve::traversal_pair);
		a.clear();
		vector<pair<double, double>> c = b;
		testPair::timeTester(b, "dichotomy_pair", solve::dichotomy_pair_2);
		b.clear();
		vector<pair<double, double>> d = c;
		testPair::timeTester(c, "traversal_pair", solve::traversal_pair);
		c.clear();
		testPair::timeTester(d, "dichotomy_pair", solve::dichotomy_pair_2);
		d.clear();
	}
}