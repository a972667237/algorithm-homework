#include<random>
#include<time.h>
#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
using namespace std;
namespace solve {
	/* save the price to out */
	void makeSaveToOut(int n, int m) {
		std::ofstream	f("./matrix"+ to_string(n)+ "_" + to_string(m) + ".dat", ios::trunc);
		std::default_random_engine e;
		e.seed((unsigned)time(NULL));
		int max = n*m * 1000;
		for (int i = 0; i <= m; i++) {
			f << 0 << " ";
		}
		f << std::endl;
		
		for (int i = 1; i <= n; i++) {
			f << 0 << " ";
			for (int j = 1; j <= m; j++) {
				f << abs((int)e() % max) << " ";
			}
			f << std::endl;
		}
		f.close();
	}
	void inputLine(std::ifstream &f, int *c, int m) {
		for (int i = 0; i <= m; i++) {
			f >> c[i];
		}

		return;
	}
	int see = 0;
	void inputLine(int *c, int m, int n) {
		std::default_random_engine e;
		e.seed((unsigned)time(NULL)*100*(see++));
		int max = n*m * 1000;
		c[0] = 0;
		for (int i = 1; i <= m; i++) {
			c[i] = abs((int)e() % max);
			//cout << c[i] << " ";
		}
		//cout << endl;
		return;
	}
	int computerIt(int *s, int **c, int m, int n) {
		int sum = 0;
		int count = 0;
		for (int i = 0; i <= n; i++) {
			if (s[i] == 0) {
				sum += 0;
			}
			else {
				count += s[i];
				if (count > n)
					return 0;
				sum += c[i][s[i]];
			}
		}
		return sum;
	}
	void findDynamic_price_inner(int m, int n) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		int max;
		int** table = new int*[m + 1];
		for (int i = 0; i <= m; i++) {
			table[i] = new int[n + 1];
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				table[i][j] = 0;
			}
		}
		int *save = new int[m + 1];
		for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			inputLine(save, m, n);
			for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				max = 0;
				for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
					if (table[i - 1][j - k] + save[k] > max)
						max = table[i - 1][j - k] + save[k];
					table[i][j] = max;
				}
			}
		}
		QueryPerformanceCounter(&EndTime);
		std::cout << "solve: " << "inner price" << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by size " << m << " product and " << n << " factor" << std::endl;
		//for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		std::cout << table[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		std::cout << table[n][m] << std::endl;
		for (int i = 0; i <= n; i++) {
			delete[]table[i];
		}
		delete[]table;
	}
	void findDynamic_price_inner_table_inner(int m, int n) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		int max;
		int *table = new int[m + 1];
		int *last_table = new int[m + 1];
		int** route = new int*[m + 1];
		for (int i = 0; i <= m; i++) {
			route[i] = new int[n + 1];
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				route[i][j] = 0;
			}
		}
		for (int i = 0; i <= m; i++) {
			table[i] = 0;
			last_table[i] = 0;
		}
		int *save = new int[m + 1];
		for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			inputLine(save, m, n);
			for (int j = m; j >= 1; j--) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				max = 0;
				for (int k = j; k >= 0; k--) { // can give j(max is n) (min is zero)   
					if (table[j] + save[j-k] > max) {
						max = table[j] + save[j-k];
						table[i] = max;
						route[i][j] = j - k;
					}
				}
			}
		}
		QueryPerformanceCounter(&EndTime);
		std::cout << "solve: " << "inner price" << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by size " << m << " product and " << n << " factor" << std::endl;
		//for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		std::cout << table[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		std::cout << table[m] << std::endl;
		/*int k = n;
		for (int j = m; j >= 1; j--) {
			cout << j << " << " << k - route[k][j] << endl;
			k = route[k][j];
		}*/
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cout << route[i][j] << " ";
			}
			cout << endl;
		}
		delete[]table;
		for (int i = 0; i <= n; i++) {
			delete[]route[i];
		}
		delete[]route;
	}
	void findDynamic_price(int m, int n) {
		std::ifstream fin;
		fin.open("./matrix" + to_string(n) + "_" + to_string(m) + ".dat");
		int max;
		int** table = new int*[m + 1];
		for (int i = 0; i <= m; i++) {
			table[i] = new int[n + 1];
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				table[i][j] = 0;
			}
		}
		int *save = new int[m + 1];
		inputLine(fin, save, m);
		for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			inputLine(fin, save, m);
			for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				max = 0;
				for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
					if (table[i - 1][j - k] + save[k] > max)
						max = table[i - 1][j - k] + save[k];
					table[i][j] = max;
				}
			}
		}
		for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				std::cout << table[i][j] << " ";
			}
			std::cout << std::endl;
		}
		fin.close();
		std::cout << table[n][m] << std::endl;
		for (int i = 0; i <= n; i++) {
			delete[]table[i];
		}
		delete[]table;


	}
	void saveAndClean(int **r, int m, int e, int cut_size) {
		int end = e % cut_size;
		std::ofstream	f("./route" + to_string(m) + ".dat", ios::app);
		for (int i = 0; i <= end; i++) {
			for (int j = 0; j <= m; j++) {
				f << r[i][m] << " ";
				r[i][m] = 0;
			}
			f << endl;
		}
		f.close();
	}
	void findDynamic_pro_out(int m, int n, int cut_size) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		int max;
		int* fro_table = new int[n + 1];
		int* now_table = new int[n + 1];
		int** route = new int*[cut_size];
		for (int i = 0; i <= cut_size; i++) {
			route[i] = new int[n + 1];
			for (int j = 0; j <= n; j++) {
				route[i][j] = 0;
			}
		}
		for (int i = 0; i <= n; i++) {
			fro_table[i] = 0;
			now_table[i] = 0;
			
		}
		int *save = new int[m + 1];
		for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			inputLine(save, m, n);
			for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
					if (fro_table[k] + save[j - k] > now_table[j]) {
						now_table[j] = fro_table[k] + save[j - k];
						route[i%cut_size][j] = j - k;
					}
				}
			}
			if (i % cut_size == cut_size-1)
				saveAndClean(route, m, i, cut_size);
			for (int k = 0; k <= n; k++) {
				fro_table[k] = now_table[k];
				now_table[k] = 0;
			}
		}
		saveAndClean(route, m, n, cut_size);
		//for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
		//			if (table[i - 1][k] + c[i][j - k] > table[i][j]) {
		//				table[i][j] = table[i - 1][k] + c[i][j - k];
		//				route[i][j] = j - k;
		//			}
		//		}
		//	}
		//}
		//for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		std::cout << table[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		int k = m;
		for (int i = n; i >= 1; i--) {
			cout << i << " << " << route[i][k] << endl;
			k = k - route[i][k];
		}
		for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				std::cout << route[i][j] << " ";
			}
			std::cout << std::endl;
		}
		QueryPerformanceCounter(&EndTime);
		std::cout << "solve: " << "inner price" << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by size " << m << " product and " << n << " factor" << std::endl;
		std::cout << fro_table[m] << std::endl;

		delete[]now_table;
		delete[]fro_table;
	}
	void findDynamic_pro(int m, int n, int **c) {
		int max;
		int* fro_table = new int[n + 1];
		int* now_table = new int[n + 1];
		int** route = new int*[m + 1];
		for (int i = 0; i <= m; i++) {
			route[i] = new int[n + 1];
		}
		for (int i = 0; i <= n; i++) {
			fro_table[i] = 0;
			now_table[i] = 0;
			for (int j = 0; j <= m; j++) {
				route[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
					if (fro_table[k] + c[i][j - k] > now_table[j]) {
						now_table[j] = fro_table[k] + c[i][j - k];
						route[i][j] = j - k;
					}
				}
			}
			for (int k = 0; k <= n; k++) {
				fro_table[k] = now_table[k];
				now_table[k] = 0;
			}
		}
		//for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
		//			if (table[i - 1][k] + c[i][j - k] > table[i][j]) {
		//				table[i][j] = table[i - 1][k] + c[i][j - k];
		//				route[i][j] = j - k;
		//			}
		//		}
		//	}
		//}
		//for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		std::cout << table[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		int k = m;
		for (int i = n; i >= 1; i--) {
			cout << i << " << " << route[i][k] << endl;
			k = k - route[i][k];
		}
		//for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		std::cout << route[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		std::cout << fro_table[m] << std::endl;
		
		delete[]now_table;
		delete[]fro_table;
	}
	void findDynamic(int m, int n, int **c) {
		int max;
		int** table = new int*[m+1];
		int** route = new int*[m + 1];
		for (int i = 0; i <= m; i++) {
			table[i] = new int[n+1];
			route[i] = new int[n + 1];
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				table[i][j] = 0;
				route[i][j] = 0;
			}
		}
		
		for (int i = 1; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
			for (int j = 1; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
				for (int k = 0; k <= j; k++) { // can give j(max is n) (min is zero)   
					if (table[i - 1][k] + c[i][j-k] > table[i][j]){
						table[i][j] = table[i - 1][k] + c[i][j - k];
						route[i][j] = j - k;
					}
				}
			}
		}
		//for (int i = 0; i <= n; i++) { // 对于所有的机器（至少一个） 不断增加
		//	for (int j = 0; j <= m; j++) { // 对于所有的设备，不断增加（最少给一台吧，最多n台）
		//		std::cout << table[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		/*int k = m;
		for (int i = n; i >= 1; i--) {
			cout << i << " << " << route[i][k] << endl;
			k = k - route[i][k];
		}
		std::cout << table[n][m] << std::endl;*/
		for (int i = 0; i <= n; i++) {
			delete[]table[i];
		}
		delete[]table;
	}
	void findViolence(int m, int n, int **c ) { // n 车间 m 个数
		
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				std::cout << c[i][j] << " ";
			}
			std::cout << std::endl;
		}


		int *s = new int[n+1];
		int *t = new int[n+1];
		for (int i = 0; i <= n; i++) {
			s[i] = 0;
			t[i] = 0;
		}
		int now = n;
		int earn = 0;
		int max = 0;
		bool isFinish = false;
		while (!isFinish) {
			if (now == n) {
				earn = computerIt(s, c, m, n);
				if (earn > max) {
					max = earn;
					for (int i = 0; i <= n; i++)
						t[i] = s[i];
				}
			}
			while (s[now] == m) {
				s[now] = 0;
				now--;
				if (now == -1) {
					isFinish = true;
					break;
				}
			}
			s[now]++;
			now = n;
		}
		std::cout << max << std::endl;
		for (int i = 0; i <= n; i++) {
			std::cout << t[i] << " ";
		}
		std::cout << std::endl;
		
		
		delete[]t;
		//delete[]s;
	}

	void tester(int m, int n, int **c, void(* find)(int m, int n, int **c), std::string findName) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		find(m, n, c);
		QueryPerformanceCounter(&EndTime);
		std::cout << "solve:" << findName << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by size " << m << " product and " << n << " factor" << std::endl;
	}
}

