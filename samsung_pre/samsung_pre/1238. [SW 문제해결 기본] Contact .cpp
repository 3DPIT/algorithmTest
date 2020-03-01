#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string.h>
using namespace std;
struct Data {
	int n, cnt;
};
struct contact {
	int T = 0;
	int N = 0;
	int startNum = 0;
	int ret = 0;
	vector<int>v[101];
	int cnt = 0;
	vector<int>G[101];
	int V[101];
	int t = 1;
	contact() {
		while (cin>>N>>startNum) {
			
			for (int i = 0; i < N; i += 2) {
				int from, to;
				scanf("%d %d", &from, &to);
				G[from].push_back(to);
			}
			bfs();
			ret = 0x80000000;
			for (int i = 1; i <= 100; i++) {
				if (V[i] == cnt) {
					if (ret < i)ret = i;
				}
			}
			//cout << cnt << endl;
			printf("#%d %d\n", t++, ret);
			init();

		}
	}
	void bfs() {
		queue<Data>q;
		q.push({ startNum,0 });
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			for (int idx = 0; idx < G[c.n].size(); idx++) {
				if (V[G[c.n][idx]] == 0) {
					V[G[c.n][idx]] = c.cnt+1;
					cnt = c.cnt + 1;
					q.push({ G[c.n][idx], c.cnt + 1 });
				}
			}
		}
	}
	void init() {
		
		cnt=T = N = ret = startNum = 0;
		for (int i = 0; i < 101; i++) {
			G[i].clear();
			v[i].clear();
		}
		memset(V, 0, sizeof(V));
	}
}contact;
int main(void) {

	return 0;
}