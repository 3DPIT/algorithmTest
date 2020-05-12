#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<queue>
using namespace std;
#define NS 100001
int N, K,ret;
int chk[NS];
int n[NS];
struct Data {
	int num, cnt;
};
void init() {
	memset(chk, 0, sizeof(chk));
	N = K = ret = 0;
	scanf("%d %d", &N, &K);

}
bool safe(int a) {
	return 0 <= a && a <= 100000;
}
void BFS() {
	queue<Data>q;
	Data a;
	a.num = N;
	a.cnt = 0;
	q.push(a);
	memset(chk, -1, sizeof(chk));
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.num == K) {
			cout << c.cnt << endl;
		
			int n = K;
			vector<int>a;
			while (1) {
				if (n == N)break;
				a.push_back(chk[n]);
				n = chk[n];
			}
			for (int i = a.size()-1; i >= 0; i--) {
				cout << a[i]<< " ";
			}
			cout << K << endl;
			break;
		}
		Data n;
		n.cnt = c.cnt + 1;
		n.num = c.num * 2;
		if (safe(n.num) && chk[n.num] == -1) {
			chk[n.num] = c.num;
			q.push(n);
		}
		n.num = c.num + 1;
		n.cnt = c.cnt + 1;
		if (safe(n.num)&&chk[n.num] == -1) {
			chk[n.num] = c.num;
			q.push(n);
		}
		n.num = c.num - 1;
		n.cnt = c.cnt + 1;
		if (safe(n.num) && chk[n.num] == -1) {
			chk[n.num] = c.num;
			q.push(n);
		}

	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		BFS();
		//printf("#%d %d\n", t, ret);
		//printf("%d\n", ret);
	}
	return 0;
}