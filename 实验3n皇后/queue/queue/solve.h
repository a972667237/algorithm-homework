#include<iostream>
#include<vector>
#include<windows.h>
#include<time.h>
#include<string>
#include<fstream>
using namespace std;

namespace solve {
	vector<int*> suitableResult;
	long count = 0;
	long long countDo = 0;
	int upperlim; // ����λ������Ǹ������Ķ���
	void _queue_bit(int row, int l, int r) { // row ��ֱ����   l  ������    r ������
		int pos, p;
		if (row != upperlim)
		{
			pos = upperlim & (~(row | l | r));   // �жϲ���    ���к���һ��Ϊ���Էŵ�λ��   ��Ϊ�������¼����� ���ɵ�pos�ǻ����Էŵ�λ��
			while (pos)
			{
				p = pos & ( -pos);  // ��ʱ���ɵ�pΪ���Ҳ���Ǹ�1
				pos = pos - p;      // ��ȥ���������Ҳ���Ǹ�1 Ҳ���Ǵ����λ����
				_queue_bit(row | p, (l | p) << 1, (r | p) >> 1);
			}
		}
		else
			count++; // ��ʾ�����
	}
	void quque_bit(int n) {
		upperlim = (1 << n) - 1;  // ��ʼ�����Էŵ�λ�ã�Ҳ���Ǹ����Էŵ��и�ֵ1��
		count = 0;
		_queue_bit(0, 0, 0);
	}
	bool doIt(int *c, int len) {
		countDo++;
		/*cout << "now try: ";
		for (int i = 0; i < len; i++) {
			cout << c[i] << " ";
		}
		cout << endl;*/
		bool isFail = false;
		for (int i = 0; i < len-1; i++) {
			for (int j = i+1; j < len; j++) { // �ȼ����û�����������ͻ(��ֱ������
				if (c[i] == c[j])
					isFail = true;
				if (c[i] - c[j] == i-j || c[i] - c[j] == j-i) {
					isFail = true;
				}
			}
		}
		//cout << (isFail ? "fail" : "success") << endl;
		return !isFail;
		
	}
	bool doItCut(int *c, int len) {
		countDo++;
		bool isFail = false;
		int last, now;
		if (len > 1) {
			last = len - 1;
			now = c[last];
		}
		else {
			isFail = false;
		}
		for (int i = 0; (i < len - 1) && (!isFail); i++) {
			if (now - c[i] == last - i || now - c[i] == i - last || now == c[i])
				isFail = true;
		}
		return !isFail;
	}
	void queue_loop(int n) {
		countDo = 0;
		count = 0;
		int *each = new int[n];
		for (int i = 0; i < n; i++) {
			each[i] = 0;
		}
		int now = n - 1;
		int end = n - 1;
		bool isFinish = false;
		while (true) {
			if (now == end) {      
				if (doIt(each, n)) {
					/*int *save = new int[n];
					for (int i = 0; i < n; i++)
						save[i] = each[i];*/
					count++;
				}
			}
			while (each[now] == end) {
				each[now] = 0;
				now--;
				if (now == -1) {
					isFinish = true;
					break;
				}
			}
			if (isFinish)
				break;
			each[now]++;
			now = end;
		}
	}
	inline void queue_cut(int n) {
		countDo = 0;
		count = 0;
		int *each = new int[n];
		int now = 0;
		int end = n - 1;
		each[0] = 0;
		bool canContinue = true;
		while (canContinue) {
			if (!doItCut(each, now+1)) {  // ������¼���if��
				while (each[now] == end) {
					each[now] = 0;
					now--;
					if (now == -1) {
						canContinue = false;
						break;
					}
				}
				/*if (!canContinue)
					break;*/
				each[now]++;
			}
			else {
				if (now != end) {
					now++;
					each[now] = 0;
				}
				else {
					/*int *save = new int[n];
					for (int i = 0; i < n; i++)
					save[i] = each[i];
					suitableResult.push_back(save);*/
					count++;
					while (each[now] == end) {
						each[now] = 0;
						now--;
					}
					each[now]++;
				}
			}
		}
	}
	void _queue_recur(int *a, int n, int m) {   // β�ݹ顣����
		if (doItCut(a, n+1)) {
			if (n == m - 1) { // end
				count++;
				/*int *save = new int[n];
				for (int i = 0; i < n; i++)
					save[i] = a[i];
				suitableResult.push_back(save);
				if (suitableResult.size() > 10000) {
					ofstream f("./queue_recur_" + to_string(m) + ".record", ios::app);
					f << suitableResult.size() << endl;
					for (vector<int*>::iterator it = suitableResult.begin(); it != suitableResult.end(); it++) {
						for (int i = 0; i < m; i++) {
							f << (*it)[i] << " ";
						}
						f << endl;
						delete (*it);
					}
					f.close();
					suitableResult.clear();
				}*/
				
				return;
			}
			else {
				a[n+1] = 0;
				_queue_recur(a, n+1, m);
			}
		}
		if (a[n] == m - 1) {
			return;
		}
		else {
			a[n]++;
			_queue_recur(a, n, m);
		}
	}
	void queue_recur(int n) {
		countDo = 0;
		count = 0;
		int *each = new int[n];
		each[0] = 0;
		_queue_recur(each, 0, n);
		
		/*ofstream f("./queue_recur_" + to_string(n) + ".record", ios::app);
		f << suitableResult.size() << endl;
		for (vector<int*>::iterator it = suitableResult.begin(); it != suitableResult.end(); it++) {
			for (int i = 0; i < n; i++) {
				f << (*it)[i] << " ";
			}
			f << endl;
			delete (*it);
		}
		f.close();
		suitableResult.clear();*/
	}

	inline void tester(int n, string name, void (* queue)(int n)) {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		queue(n);
		QueryPerformanceCounter(&EndTime);
		ofstream f2("./time.record", ios::app);
		cout << "solve:" << name << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by size " << n << " with " << count << "jugde do :" << countDo << endl;
		f2 << "solve:" << name << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " by size " << n << " with " << count << "jugde do :" << countDo << endl;
		f2.close();
		ofstream f1("./time.noword.record", ios::app);
		f1 << n << " " << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << " " << countDo << endl;
		f1.close();
		/*ofstream f("./" + name + "_" + to_string(n) +".record");
		f << suitableResult.size() << endl;
		for (vector<int*>::iterator it = suitableResult.begin(); it != suitableResult.end(); it++) {
			for (int i = 0; i < n; i++) {
				f << (*it)[i] << " ";
			}
			f << endl;
			delete (*it);
		}
		f.close();*/
		suitableResult.clear();
	}
}