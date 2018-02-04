#include<iostream>

#include "solve.h"
using namespace std;

int main() {
	for (int i = 4; i <= 20; i++) {
		solve::tester(i, "cut", solve::queue_cut);
		solve::tester(i, "bit", solve::quque_bit);
	}
	return 0;
}