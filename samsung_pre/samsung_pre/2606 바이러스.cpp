#include<stdio.h>
#include<vector>
#include<iostream>
#include<string.h>
using namespace std;
#define S 101
int N, n;
int ret;
vector<int>G[S];
int V[S];
struct Virus {
	Virus(){
		init();
		scanf("%d", &N);
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
		V[1] = 1;
		firstDfs(1,0);
		
		printf("%d\n", ret);
	}
	void init() {
		N = n = ret = 0;
		memset(V, 0, sizeof(V));
		for (int i = 0; i <= 100; i++) G[i].clear();
	}
	void firstDfs(int idx, int cnt) {
		for (int i = 0; i < G[idx].size(); i++) {
			if (V[G[idx][i]] == 0) {
				V[G[idx][i]] = 1;
				ret++;
				firstDfs(G[idx][i], cnt + 1);
			}
		}
	}
}Virus;
int main(void) {
	return 0;
}