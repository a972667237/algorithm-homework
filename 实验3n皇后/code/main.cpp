#include<iostream>

#include "solve.h"
using namespace std;

int main() {
	for (int i = 18; i <= 20; i++) {
		//solve::tester(i, "recur", solve::queue_recur);
		//solve::tester(i, "cut", solve::queue_cut);
		solve::tester(i, "bit", solve::quque_bit);
		//solve::tester(i, "loop", solve::queue_loop);
	}
	system("pause");
	return 0;
}