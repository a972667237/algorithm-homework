
#include<iostream>
#include<time.h>
using namespace std;

#include"softUtil.h"
#include"softTemplate.h"
#include"arrayMaker.h"

int main() {
	int len = 1000000;
	int *arr = maker::makeArray(len);
	
	/*int i = 5;
	while (i--) {
		util::testAllSoft(1000000);
		cout << endl;
	}*/

	/*int i = 5;
	while (i--) {
		util::testAllSoft(10000);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(100000);
		cout << endl;
	}*/

	/*i = 5;
	while (i--) {
		util::testAllSoft(10000);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(1000);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(100);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(20000);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(30000);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(40000);
		cout << endl;
	}
	i = 5;
	while (i--) {
		util::testAllSoft(50000);
		cout << endl;
	}*/
	system("pause");
}