#include<iostream>
#include "solve.h"
using namespace std;

int main() { // n 车间 m 个数
	bool makeByArray = true;
	int m, n;
	//cin >> n >> m;
	int list[] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
	for (int t = 0; t < 10; t++) {
		m = n = list[t];
		if (makeByArray) {
			int** c = new int*[n + 1]; // 前面一个代表第几个车间
			std::default_random_engine e;
			e.seed((unsigned)time(NULL));
			int max = n*m * 1000;
			for (int i = 0; i <= n; i++) {
				c[i] = new int[m + 1];
				for (int j = 0; j <= m; j++) {
					c[i][j] = abs((int)e() % max);
				}
			}
			for (int i = 0; i <= n; i++) {
				c[i][0] = 0;  // 第i行有0台机器都是0
			}
			for (int i = 0; i <= m; i++) {
				c[0][i] = 0;  // 没有公司即使有设备也都是0
			}



			//solve::tester(m, n, c, solve::findViolence, "violence");
			//solve::tester(m, n, c, solve::findDynamic_pro, "dynamic_pro");
			solve::tester(m, n, c, solve::findDynamic, "dynamic");

			for (int i = 0; i <= n; i++) {
				delete[]c[i];
			}
			delete[]c;
		}
		else {
			//solve::makeSaveToOut(m, n);
			solve::findDynamic_pro_out(20000, 20000, 100);
			solve::findDynamic_pro_out(30000, 30000, 100);
			solve::findDynamic_pro_out(40000, 40000, 100);
			//solve::findDynamic_price_inner_table_inner(m, n);
		}
	}
	
	
	system("pause");
	return 0;
}