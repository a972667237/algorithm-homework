#pragma once
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<fstream>
#include<string>
#include<stack>
#include<map>
#include<vector>
using namespace std;
namespace tree {
	class Node {
	public:
		char key;
		int value;
		int left;
		int right;
		int father;
	};
	class Haffman {
	public:
		int root;
	};

	class WNode {
	public:
		string key;
		int value;
		int left;
		int right;
		int father;
	};
}
namespace solve {
	/* 你就傻傻的读取吧。。*/
	string in_file = "./cacm.txt";
	string out_file = "./cacm.h";
	string uz_file = "./ccacm.txt";
	void resolve_file_i(int *info) {
		ifstream in(in_file);
		char c;
		while (!in.eof()) {
			in.get(c);
			info[(int)c]++;
		}
		in.close();
	}
	map<char, int> resolve_file_c() {
		ifstream in(in_file, ios::binary);
		char c;
		map<char, int> m;
		while (!in.eof()) {
			in.get(c);
			if (m.find(c) != m.end()) {
				m[c]++;
			}
			else {
				m[c] = 1;
			}
		}
		return m;
	}
	map<string, int> resolve_file_m() {
		ifstream in(in_file);
		map<string, int> info;
		map<string, int> info_word;
		char c;
		string word = "";
		while (!in.eof()) {
			in.get(c);
			if (((int)c >= 48 && (int)c <= 57) || ((int)c >= 65 && (int)c <= 90) || ((int)c >= 97 && (int)c <= 122)) { // 就是是数字，是英文 且连续才能被搞一块当作单词
				word += c;
			}
			else { // 此时要么间断了，要么没了
				if (word.length() > 0) {
					if (info_word.find(word) != info_word.end()) {
						info_word[word] ++;
					}
					else {
						info_word[word] = 1;
					}
				}
				word = c;
				if (info.find(word) != info.end()) {
					info[word] ++;
				}
				else {
					info[word] = 1;
				}
				word = "";
			}
		}

		for (map<string, int>::reverse_iterator iter = info_word.rbegin(); iter != info_word.rend(); iter++) {
			if (iter->second > 3) { // 大于100就认为你频繁吧
				info[iter->first] = iter->second;
			}
			else { // 不频繁就分解吧
				for (int i = 0; i < iter->first.length(); i++) {
					char c = iter->first[i];
					string s = "";
					s += c;
					if (info.find(s) != info.end()) {
						info[s] = info[s] + iter->second;
					}
					else {
						info[s] = iter->second;
					}
				}

			}
		}
		cout << info.size() << endl;
		/*for (map<string, int>::reverse_iterator iter = info.rbegin(); iter != info.rend(); iter++) {
			cout << iter->first << " " << iter->second << endl;
		}*/
		
		return info;
	}
	//void resolve_file(int* info) {
	//	ifstream inf;
	//	int entcount = 0;
	//	
	//	inf.open(in_file);  //,ios::in|ios::out,0
	//	string s;
	//	
	//	while (getline(inf, s)) {
	//		int len = s.length();
	//		for (int i = 0; i < len; i++) {
	//			info[(int)s[i]]++;
	//		}
	//		entcount++;
	//	}
	//	info[9] = entcount;
	//	inf.close();
	//}

	int nodeComp(const void *a, const void *b) {
		return ((*(tree::Node*)a).value - (*(tree::Node*)b).value);
	}
	int wnodeComp(const void *a, const void *b) {
		return ((*(tree::WNode*)a).value - (*(tree::WNode*)b).value);
	}
	
	void preOrder(int t, tree::Node n[]) {
		tree::Node *r = &n[t];
		cout << (int)r->key << "::" << r->value << endl;
		if(r->left != -1)
			preOrder(r->left, n);
		if(r->right != -1)
			preOrder(r->right, n);
	}
	void nodeSwap_w(int ai, int bi, tree::WNode *n) {
		int tl;
		int tr;
		int tf;
		string tk;
		int tv;

		tree::WNode *a = &n[ai];
		tree::WNode *b = &n[bi];

		// 先对孩子动手
		if (a->left != -1)
			n[a->left].father = bi;
		if (a->right != -1)
			n[a->right].father = bi;
		if (b->left != -1)
			n[b->left].father = ai;
		if (b->right != -1)
			n[b->right].father = ai;

		tl = a->left;
		tr = a->right;
		tk = a->key;
		tv = a->value;
		tf = a->father;

		a->left = b->left;
		a->right = b->right;
		a->key = b->key;
		a->value = b->value;
		a->father = b->father;

		b->left = tl;
		b->right = tr;
		b->key = tk;
		b->value = tv;
		b->father = tf;
	}
	void nodeSwap(int ai, int bi, tree::Node *n) {
		int tl;
		int tr;
		int tf;
		char tk;
		int tv;

		tree::Node *a = &n[ai];
		tree::Node *b = &n[bi];

		// 先对孩子动手
		if (a->left != -1)
			n[a->left].father = bi;
		if (a->right != -1)
			n[a->right].father = bi;
		if (b->left != -1)
			n[b->left].father = ai;
		if (b->right != -1)
			n[b->right].father = ai;

		tl = a->left;
		tr = a->right;
		tk = a->key;
		tv = a->value;
		tf = a->father;

		a->left = b->left;
		a->right = b->right;
		a->key = b->key;
		a->value = b->value;
		a->father = b->father;

		b->left = tl;
		b->right = tr;
		b->key = tk;
		b->value = tv;
		b->father = tf;

	}
	map<string, string> getWCode(tree::WNode *n, int count) {
		stack<char> backStack;
		const int len = 2 * count - 1;
		tree::WNode *f;
		tree::WNode *s;
		map <string, string> codeMap;
		int sindex;
		for (int i = 0; i < len; i++) {
			if (n[i].left == -1 && n[i].right == -1) { // 叶子节点才需要遍历
				s = &n[i];
				sindex = i;
				while (s->father != -1) {
					f = &n[s->father];
					if (f->left == sindex) {
						backStack.push('0');
					}
					else {
						backStack.push('1');
					}
					sindex = s->father;
					s = f;
				}

				string em = "";
				while (!backStack.empty()) {
					em += backStack.top();
					backStack.pop();
				}
				//em += "\0";
				codeMap[n[i].key] = em;
			}
		}
		return codeMap;
	}
	map<char, string> getCode(tree::Node *n, int count) { // n是传进来的数组啊喂
		stack<char> backStack;
		const int len = 2 * count - 1;
		tree::Node *f;
		tree::Node *s;
		map<char, string> codeMap;
		int sindex;
		for (int i = 0; i < len; i++) {
			if (n[i].left == -1 && n[i].right == -1) { // 叶子节点才需要遍历
				s = &n[i];
				sindex = i;
				while (s->father != -1) {
					f = &n[s->father];
					if (f->left == sindex) {
						backStack.push('0');
					}
					else {
						backStack.push('1');
					}
					sindex = s->father;
					s = f;
				}

				string em = "";
				while (!backStack.empty()) {
					em += backStack.top();
					backStack.pop();
				}
				//em += "\0";
				codeMap[n[i].key] = em;
			}
		}
		return codeMap;
	}
	/* 生成树 */
	void becomeTree_m(map<string, int> &m, tree::WNode *n) {
		// 生成node
		int count = m.size();
		const int end = 2 * count - 2;
		int zcount = 0;
		for (map<string, int>::reverse_iterator iter = m.rbegin(); iter != m.rend(); iter++) {
			n[zcount].key = iter->first;
			n[zcount].value = iter->second;
			n[zcount].left = -1;
			n[zcount].right = -1;
			n[zcount].father = -1;
			zcount++;
		}
		cout << zcount << endl;
		qsort(n, count, sizeof(tree::WNode), wnodeComp); // 快排一波先
		for (int i = 0; i < count-1; i++) {
			int now = count + i;
			n[now].left = 2 * i;
			n[now].right = 2 * i + 1;
			n[now].key = '\0';
			n[now].value = n[2*i].value + n[2*i+1].value;
			n[2 * i].father = now;
			n[2 * i + 1].father = now;
			for (int j = now-1; j > 2*i + 1; j--) {  // 这里走的是插排
				if (n[j+1].value < n[j].value) {
					nodeSwap_w(j+1, j, n);
				}
				else { // 因为是已经有序的数组，如果不符合就可以停下了
					break;
				}
			}
		}
	}
	void becomeTree(map<char, int> m, tree::Node *n, int count) {
		// 生成node
		int zcount = 0;
		for (map<char, int>::reverse_iterator iter = m.rbegin(); iter != m.rend(); iter++) {
			n[zcount].key = iter->first;
			n[zcount].value = iter->second;
			n[zcount].left = -1;
			n[zcount].right = -1;
			n[zcount].father = -1;
			zcount++;
		}
		qsort(n, count, sizeof(tree::Node), nodeComp); // 快排一波先
		for (int i = 0; i < count - 1; i++) {
			int now = count + i;
			n[now].left = 2 * i;
			n[now].right = 2 * i + 1;
			n[now].key = '\0';
			n[now].value = n[2 * i].value + n[2 * i + 1].value;
			n[2 * i].father = now;
			n[2 * i + 1].father = now;
			for (int j = now - 1; j > 2 * i + 1; j--) {  // 这里走的是插排
				if (n[j + 1].value < n[j].value) {
					nodeSwap(j + 1, j, n);
				}
				else { // 因为是已经有序的数组，如果不符合就可以停下了
					break;
				}
			}
		}
	}
	void printChar(string s, tree::Node *g, int count) {
		int now = 2 * count - 2;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '1') {
				now = g[now].right;
			}
			else {
				now = g[now].left;
			}
			if (g[now].left == -1 && g[now].right == -1) { // 到根了
				cout << (int)g[now].key << endl;
				now = 2 * count - 2;
			}
		}
	}
	void output_uc(unsigned char b) {
		for (int i = 0; i < 8; i++) {
			if (b & 0x80) { // 最高位是1
				cout << "1";
			}
			else { // 不是1
				cout << "0";
			}
			b <<= 1;
		}
		cout << endl;
	}
	void zipIt_w(map<string, string> m, tree::WNode *n, int count) {
		ifstream in(in_file, ios::binary);
		ofstream out(out_file, ios::binary);
		char buffer[256] = { 0 };
		string emp = "";
		unsigned char b;
		char t = '1';
		out.write((char *)&t, sizeof(char)); // a pos to cover by len of stop   反正不会大于8，用char来表示应该o鸡腿k

		out.write((char *)&count, sizeof(int)); // 写入count

		const int end = 2 * count - 1;
		t = 0;
		for (int i = 0; i < end; i++) {
			if (n[i].key[0] != 0) {
				out.write((char *)&n[i].key, sizeof(char)*n[i].key.length());
				out.write((char *)&t, sizeof(char));
			}
		}
		short w;
		for (int i = 0; i < end; i++) {
			w = (short)n[i].left;
			out.write((char *)&w, sizeof(short));
			w = (short)n[i].right;
			out.write((char *)&w, sizeof(short));
		}
		char c;
		string word;
		string ew;
		while (!in.eof()) {
			in.get(c);
			if (((int)c >= 48 && (int)c <= 57) || ((int)c >= 65 && (int)c <= 90) || ((int)c >= 97 && (int)c <= 122)) { // 就是是数字，是英文 且连续才能被搞一块当作单词
				word += c;
			}
			else { // 此时要么间断了，要么没了
				if (word.length() > 0) {
					// 直接查找并怼 
					if(m.find(word) != m.end())
						emp += m[word];
					else {
						for (int i = 0; i < word.length(); i++) {
							ew = word[i];
							emp += m[ew];
						}
					}
					
				}
				word = c;
				emp += m[word];
				word = "";
			}

			while (emp.length() >= 8) {
				b = '\0';
				for (int j = 0; j < 8; j++) {
					b <<= 1;
					if (emp[j] == '1')
						b |= 1;
				}

				out.write((char *)&b, sizeof(unsigned char));
				emp = emp.substr(8, emp.length());
			}
		}
		if (emp.length() > 0) {
			b = '\0';
			for (int i = 0; i < emp.length(); i++) {
				b <<= 1;
				if (emp[i] == '1')
					b |= 1;
			}
			for (int i = 0; i < 8 - emp.length(); i++) {
				b <<= 1;
			}
			out.write((char *)&b, sizeof(unsigned char));
		}
		int stopcount = (8 - emp.length()) % 8;
		t = stopcount;
		out.seekp(0, ios::beg);
		out.write((char *)&t, sizeof(char));
		in.close();
		out.close();
	}
	void zipIt(map<char, string> m, tree::Node *n, int count) {
		ifstream in(in_file, ios::binary);
		ofstream out(out_file, ios::binary);
		char buffer[256] = {0};
		string emp = "";
		unsigned char b;
		char t = '1';
		out.write((char *)&t, sizeof(char)); // a pos to cover by len of stop   反正不会大于8，用char来表示应该o鸡腿k
		
		out.write((char *)&count, sizeof(int)); // 写入count

		const int end = 2 * count - 1;
		for (int i = 0; i < end; i++) {
			if (n[i].left == -1 && n[i].right == -1)
				out.write((char *)&n[i].key, sizeof(char));
		}
		short w;
		for (int i = 0; i < end; i++) {
			w = (short)n[i].left;
			out.write((char *)&w, sizeof(short));
			w = (short)n[i].right;
			out.write((char *)&w, sizeof(short));
		}
		//out << "1" << endl;  // 这里写头会被覆盖
		//out << count << endl;
		//const int end = 2 * count - 1;
		//for (int i = 0; i < end; i++) {
		//	if (n[i].key != '\0') {
		//		out.write((char *)&n[i].key, sizeof(char));
		//	}
		//}
		//out << endl;
		//for (int i = 0; i < end; i++) {
		//	out << n[i].left << " " << n[i].right << " " << n[i].father << " " << n[i].value << endl;
		//}
		char c;
		while (!in.eof()) {
			for (int i = 0; i < 20; i++) {
				if (in.peek() == EOF){
					break;
				}
				in.get(c);
				emp += m[c];
			}
			while (emp.length() >= 8) {
				b = 0;
				for (int j = 0; j < 8; j++) {
					b <<= 1;
					if (emp[j] == '1')
						b |= 1;
					else if (emp[j] == '0')
						b |= 0;
					else {
						j--;
						b >>= 1;
						continue;
					}
				}

				out.write((char *)&b, sizeof(unsigned char));
				emp = emp.substr(8, emp.length()-8);
			}
		}
		if (emp.length() > 0) {
			b = 0;
			for (int i = 0; i < emp.length(); i++) {
				b <<= 1;
				if (emp[i] == '1')
					b |= 1;
			}
			for (int i = 0; i < 8 - emp.length(); i++) {
				b <<= 1;
			}
			out.write((char *)&b, sizeof(unsigned char));
		}
		int stopcount = (8 - emp.length())%8;
		t = stopcount;
		out.seekp(0, ios::beg);
		out.write((char *)&t, sizeof(char));
		in.close();
		out.close();
	}
	void unzipIt_w() {
		ifstream in(out_file, ios::binary);
		ofstream out(uz_file, ios::binary);
		int count;
		int stop;
		char t;
		in.read((char *)&t, sizeof(char));
		stop = t;
		in.read((char *)&count, sizeof(int));

		unsigned char b;
		const int arr_end = 2 * count - 2;
		int now = arr_end;
		const int end = 2 * count - 1;
		tree::WNode *g = new tree::WNode[end];
		string *e = new string[count];
		for (int i = 0; i < count; i++) {
			while (true) {
				in.read((char *)&t, sizeof(char));
				if (t == 0)
					break;
				e[i] += t;
			}
		}
		int j = 0;
		short w;
		for (int i = 0; i < end; i++) {
			in.read((char *)&w, sizeof(short));
			g[i].left = w;
			in.read((char *)&w, sizeof(short));
			g[i].right = w;
			if (g[i].left == -1 && g[i].right == -1)
				g[i].key = e[j++];
			else
				g[i].key = "\0";
		}
		delete[] e;

		while (!in.eof()) {
			b = 0;
			in.read((char *)&b, sizeof(unsigned char));
			if (in.peek() == EOF) {
				break;
			}
			for (int i = 0; i < 8; i++) {
				if (b & 128) { // 最高位是1
					now = g[now].right;
				}
				else { // 不是1
					now = g[now].left;
				}

				if (g[now].left == -1 && g[now].right == -1) { // 到根了
					out.write((char *)&g[now].key, sizeof(char)*g[now].key.length());
					/*if (g[now].key == '?') {
					output_uc(b);
					cout << "now ii is:" << i << endl;
					}*/
					now = arr_end;
				}
				b <<= 1;
			}
		}
		delete[] g;
		//for (int i = 0; i < 8 - stop; i++) {
		//	if (b & 0x80) { // 最高位是1
		//		now = g[now].right;
		//	}
		//	else { // 不是1
		//		now = g[now].left;
		//	}

		//	if (g[now].key[0] != '\0') { // 到根了
		//		out.write((char *)&g[now].key, sizeof(char)*g[now].key.length());
		//		now = arr_end;
		//	}
		//	b <<= 1;
		//}
		in.close();
		out.close();
	}
	void unzipIt() {
		ifstream in(out_file, ios::binary);
		ofstream out(uz_file, ios::binary);
		/*int count;
		int stop;
		in >> stop;
		in >> count;*/
		int stop;
		char t;
		in.read((char *)&t, sizeof(char));
		stop = t;
		int count;
		in.read((char *)&count, sizeof(int));

		unsigned char b;
		const int arr_end = 2 * count - 2;
		int now = arr_end;
		const int end = 2 * count - 1;
		tree::Node *g = new tree::Node[end];
		char *e = new char[count];
		for (int i = 0; i < count; i++) {
			in.read((char *)&e[i], sizeof(char));
		}
		int j = 0;
		short w;
		for (int i = 0; i < end; i++) {
			in.read((char *)&w, sizeof(short));
			g[i].left = w;
			in.read((char *)&w, sizeof(short));
			g[i].right = w;
			if (g[i].left == -1 && g[i].right == -1)
				g[i].key = e[j++];
			else
				g[i].key = 0;
		}
		delete[] e;
		/*tree::Node *g = new tree::Node[end];
		char *e = new char[count];
		char tmp;
		in.get(tmp);
		in.get(tmp);
		for (int i = 0; i < count; i++) {
			in.get(e[i]); 
			if ((int)e[i] == 13) {
				i--;
				continue;
			}
		}

		int j = 0;
		for (int i = 0; i < end; i++) {
			in >> g[i].left >> g[i].right >> g[i].father >> g[i].value;
			if (g[i].left == -1 && g[i].right == -1){
				g[i].key = e[j++];
			}
			else {
				g[i].key = '\0';
			}
		}
		delete[]e;*/
		//preOrder(2*count - 2, g);
		/*in.get(tmp);
		in.get(tmp);*/
		while (!in.eof()) {
			b = 0;
			in.read((char *)&b, sizeof(unsigned char));
			if (in.peek() == EOF) {
				break;
			}
			for (int i = 0; i < 8; i++) {
				if (b & 128) { // 最高位是1
					now = g[now].right;
				}
				else { // 不是1
					now = g[now].left;
				}
				
				if (g[now].left == -1 && g[now].right == -1) { // 到根了
 					out.write((char *)&g[now].key, sizeof(char));
					/*if (g[now].key == '?') {
						output_uc(b);
						cout << "now ii is:" << i << endl;
					}*/
					now = arr_end;
				}
				b <<= 1;
			}
		}

		for (int i = 0; i < 8 - stop; i++) {
			if (b & 0x80) { // 最高位是1
				now = g[now].right;
			}
			else { // 不是1
				now = g[now].left;
			}

			if (g[now].left == -1 && g[now].right == -1 ) { // 到根了
				out.write((char *)&g[now].key, sizeof(char));
				now = arr_end;
			}
			b <<= 1;
		}
		delete[] g;
		in.close();
		out.close();
	}
	void huffmanWSolve() {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		map<string, int> w_m = solve::resolve_file_m();
		tree::Haffman a;
		int count = w_m.size();
		tree::WNode *n = new tree::WNode[2 * count - 1];
		solve::becomeTree_m(w_m, n);

		a.root = 2 * count - 2;
		n[2 * count - 2].father = -1;
		cout << 2 * count - 2 << endl;
		map<string, string> m = getWCode(n, count);
		/*for (map<string, string>::reverse_iterator iter = m.rbegin(); iter != m.rend(); iter++) {
			cout << iter->first << " " << iter->second << endl;
		}*/
		zipIt_w(m, n, count);
		QueryPerformanceCounter(&EndTime);
		cout << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl;
		//unzipIt_w();
		delete[] n;
	}
	void huffmanSolve() {
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		tree::Haffman a;

		
		map<char, int> t = solve::resolve_file_c();
		/*for (map<char, int>::reverse_iterator iter = t.rbegin(); iter != t.rend(); iter++) {
			cout << (int)iter->first << " " << iter->second << endl;
		}*/
		tree::Node *n;
		int count = t.size();
		n = new tree::Node[2 * count - 1];
		solve::becomeTree(t, n, count);
		a.root = 2 * count - 2;
		n[2 * count - 2].father = -1;
		//cout << 2 * count - 2 << endl;
		//preOrder(2 * count - 2, n);
		map<char, string> m = getCode(n, count);
		for (map<char, string>::reverse_iterator iter = m.rbegin(); iter != m.rend(); iter++) {
			cout << (int)iter->first << "  " << iter->second << endl;
		}

		
		zipIt(m, n, count);
		QueryPerformanceCounter(&EndTime);
		cout << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart  << endl;
		//solve::preOrder(2*count-2, n);
			QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		unzipIt();
		QueryPerformanceCounter(&EndTime);
		cout << " spend:" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl; 
		delete[]n;

	}
}

//001110011000001   0010
//001110011000001   010
// 010   1010001010
// 0101 