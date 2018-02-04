#include<iostream>
#include<vector>
#include<random>
#include "pointMaker.h"
#include "pair.h"
#include "testPair.h"
using namespace std;

int main() {
	testPair::testAll(100000);
	system("pause");
	return 0;
}