#include<iostream>
#include<random>
#include<windows.h>
#include<time.h>
#include<queue>

//#include "solve.h"
using namespace std;



namespace solve {
	// 邻接表大法

	class Node {
	public:
		int value;
		Node* next;
		int weight;
		int max;
		int info;
	};
	class OutNode {
	public:
		OutNode *next;
		Node* p;
	};
	class HeadNode {
	public:
		int value;
		Node* next;
		OutNode* out;
	};
	class NearList {
	public:
		HeadNode *head;
		int headNum, edgeNum;
		void NearList_crease_by_random(int e, int n) {
			edgeNum = e;
			headNum = n;
			head = new HeadNode[headNum];
			for (int i = 0; i < headNum; i++) {
				head[i].value = i;
				head[i].next = NULL;
				head[i].out = NULL;
			}
			Node* p;
			Node* c;
			OutNode* d;
			default_random_engine re;
			re.seed((unsigned)time(NULL));
			for (int i = 0; i < edgeNum; i++) {
				int s, e, w, m;
				//cin >> s >> e >> w >> m;
				s = ((unsigned int)re()) % headNum;
				e = ((unsigned int)re()) % headNum;
				while (e == s) {
					e = ((unsigned int)re()) % headNum;
				}
				m = ((unsigned int)re()) % 100000;
				c = new Node();
				c->next = NULL;
				c->max = m;
				c->value = e;
				//c->weight = w;
				c->weight = 0;   // oj use
				c->info = 0;
				if (head[s].next) {  // 开头不为空可以进行后续查找
					p = head[s].next;
					while (p->next) { // 为空退出,为最后一个节点
						p = p->next;
					}
					p->next = c;
				}
				else {
					head[s].next = c;
				}
				d = new OutNode();
				d->next = head[e].out;
				d->p = c;
				head[e].out = d;
			}
		}
		void NearList_crease(int e, int n) {
			//cin >> headNum >> edgeNum;
			//cin >> edgeNum >> headNum; // oj use
			edgeNum = e;
			headNum = n;
			head = new HeadNode[headNum];  // 初始化顶点数组
			for (int i = 0; i < headNum; i++) {
				head[i].value = i;
				head[i].next = NULL;
				head[i].out = NULL;
			}
			Node* p;
			Node* c;
			OutNode *d;
			for (int i = 0; i < edgeNum; i++) {
				// 读取边数据
				int s, e, w, m;
				//cin >> s >> e >> w >> m;
				cin >> s >> e >> m; // oj use
				e = e - 1;
				s = s - 1;
				c = new Node();
				c->next = NULL;
				c->max = m;
				c->value = e;
				//c->weight = w;
				c->weight = 0;   // oj use
				c->info = 0;
				if (head[s].next) {  // 开头不为空可以进行后续查找
					p = head[s].next;
					while (p->next) { // 为空退出,为最后一个节点
						p = p->next;
					}
					p->next = c;
				}
				else {
					head[s].next = c;
				}
				d = new OutNode();
				d->next = head[e].out;
				d->p = c;
				head[e].out = d;
			}
		}
		void printList() {
			Node *p;
			for (int i = 0; i < headNum; i++) {
				p = head[i].next;
				while (p) {
					cout << "start with: " << i << " , end with " << p->value << " , the weight and max is that " << p->weight << " , " << p->max << endl;
					p = p->next;
				}
			}
		}
		void getFlow() {
			Node *p = head[0].next;
			int w = 0;
			while (p) {
				w += p->weight;
				p = p->next;
			}
			cout << w << endl;
		}
	};

	void reverse_list(NearList &b, NearList &r) {
		int hn = b.headNum;
		r.edgeNum = b.edgeNum;
		r.headNum = hn;
		r.head = new HeadNode[hn];
		for (int i = 0; i < hn; i++) {
			r.head[i].value = i;
			r.head[i].next = NULL;
		}
		// 用前插吧
		Node *p, *n, *q;
		for (int i = 0; i < hn; i++) {
			p = b.head[i].next;
			while (p) {
				q = r.head[p->value].next;
				n = new Node;
				n->info = 0;
				n->max = p->max;
				n->next = q;
				n->value = i;
				n->weight = p->weight;
				r.head[p->value].next = n;
				p = p->next;
			}
		}
	}
	void clear(std::queue<int> &q)
	{
		std::queue<int> empty;
		std::swap(q, empty);
	}
	void SAP(NearList &b) {
		queue<int> nq;
		//NearList r;
		int canContinue = 1;
		while (canContinue) {
			canContinue = 0;
			//reverse_list(b, r);
			nq.push(0); // init with the start node
			int *label = new int[b.headNum];
			int *plus = new int[b.headNum];
			int *dire = new int[b.headNum];
			int *last = new int[b.headNum];
			for (int i = 0; i < b.headNum; i++) {
				plus[i] = INT_MAX;
				dire[i] = 0;
				label[i] = 1;
				last[i] = -1;
			}
			label[0] = 0;
			int now;
			Node *p;
			while (!nq.empty()) {
				now = nq.front();
				nq.pop();
				p = b.head[now].next;
				while (p) { // 是时候遍历有没有点了
					if (label[p->value] == 1) { // unlabel
						p->info = p->max - p->weight;
						if (p->info > 0) {
							label[p->value] = 0;
							p->info = min(plus[now], p->info);
							plus[p->value] = p->info;
							last[p->value] = now;
							nq.push(p->value);
						}
					}
					p = p->next;
				}
				OutNode *d;
				d = b.head[now].out;
				while (d) {  // 遍历反向边
					if (label[(d->p)->value] == 1) {
						if ((d->p)->weight > 0) {
							label[(d->p)->value] = 0;
							plus[(d->p)->value] = min(plus[now], (d->p)->weight);
							dire[(d->p)->value] = 1;
							last[(d->p)->value] = now;
							nq.push((d->p)->value);
						}
					}
					d = d->next;
				}

				if (label[b.headNum - 1] == 0) { // 被标记
					canContinue = 1;
					now = b.headNum - 1;//开始回推
					int min = plus[now];
					while (now != 0) { // 到起点结束回推
						if (dire[now] == 0) { //正向
							p = b.head[last[now]].next;
							while (p->value != now) {
								p = p->next;
							}
							p->weight += min;
						}
						else {
							p = b.head[now].next;
							while (p->value != last[now]) {
								p = p->next;
							}
							p->weight -= min;
						}
						now = last[now];
					}
					while (!nq.empty()) nq.pop();
				}
			}
			delete[] label;
			delete[] plus;
			delete[] dire;
			delete[] last;
		}
		clear(nq);
	}


}




int main() {
	int e, n;
	while (cin >> e >> n) {
		solve::NearList a;
		a.NearList_crease_by_random(e, n);
		LARGE_INTEGER BegainTime;
		LARGE_INTEGER EndTime;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BegainTime);
		solve::SAP(a);
		QueryPerformanceCounter(&EndTime);
		cout << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl;
		for (int i = 0; i < a.headNum; i++) {
			// 遍历删除
			solve::Node *nsave, *lsave;
			if (a.head[i].next != NULL) {
				nsave = a.head[i].next;
				while (nsave) {
					lsave = nsave;
					nsave = nsave->next;
					delete lsave;
				}
			}
			solve::OutNode *nosave, *losave;
			if (a.head[i].out != NULL) {
				nosave = a.head[i].out;
				while (nosave) {
					losave = nosave;
					nosave = nosave->next;
					delete losave;
				}
			}
			a.head->next = NULL;
			a.head->out = NULL;
		}
		delete[] a.head;
		//a.getFlow();
	}
	int data[] = {10000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
	for (int i = 0; i < 11;i++) {
		e = data[i];
		n = 10000;
		cout << data[i] << ":::" << n << endl;
		for (int j = 0; j < 30; j++) {
			solve::NearList a;
			a.NearList_crease_by_random(e, n);
			LARGE_INTEGER BegainTime;
			LARGE_INTEGER EndTime;
			LARGE_INTEGER Frequency;
			QueryPerformanceFrequency(&Frequency);
			QueryPerformanceCounter(&BegainTime);
			solve::SAP(a);
			QueryPerformanceCounter(&EndTime);
			cout  << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl;
			for (int i = 0; i < a.headNum; i++) {
				// 遍历删除
				solve::Node *nsave,*lsave;
				if (a.head[i].next != NULL) {
					nsave = a.head[i].next;
					while (nsave) {
						lsave = nsave;
						nsave = nsave->next;
						delete lsave;
					}
				}
				solve::OutNode *nosave, *losave;
				if (a.head[i].out != NULL) {
					nosave = a.head[i].out;
					while (nosave) {
						losave = nosave;
						nosave = nosave->next;
						delete losave;
					}
				}
				a.head->next = NULL;
				a.head->out = NULL;
			}
			delete[] a.head;
			//a.getFlow();
		}
	}
	system("pause");

	return 0;
}

/*   s e w m
6 7
0 1 2 2
0 3 0 3
1 2 2 5
1 4 0 3
2 5 2 2
3 2 0 1
4 5 0 4
*/

/*
6 7
0 1 0 2
0 3 0 3
1 2 0 5
1 4 0 3
2 5 0 2
3 2 0 1
4 5 0 4
*/


/*
4       7
0       1       0       2
0       2       0       5
0       3       0       3
1       2       0       3
1       3       0       5
2       1       0       8
2       3       0       4
*/

/*
6 10
0 1 0 16
0 2 0 13
1 2 0 10
1 3 0 12
2 1 0 4
2 4 0 14
3 2 0 9
3 5 0 20
4 3 0 7
4 5 0 4
*/