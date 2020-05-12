#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
#define NS 12
int N, M,K;
int map[NS][NS];
int ret, Max;
void init() {
	N = M = ret = 0;
	Max = 0x80000000;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
int cmap[NS][NS] = { 0, };
void dfs(int y, int x, int d,int sum) {
	if (d == K) {
		//to do
		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= M; j++) {
		//		cout<<" "<< cmap[i][j];
		//	}
		//	cout << endl;
		//}
		//cout << endl;
		if (Max < sum)Max = sum;
		return;
	}
	for (int i = y; i <= N; i++) {
		for (int j = x; j <= M; j++) {
			if (cmap[i][j] == 0 &&
				cmap[i - 1][j] == 0 && cmap[i + 1][j] == 0
				&& cmap[i][j - 1] == 0 && cmap[i][j + 1] == 0) {
				cmap[i][j] = 1;
				dfs(i, j, d + 1, sum + map[i][j]);
				cmap[i][j] = 0;
			}

		}
		x = 1;
	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		dfs(1, 1, 0, 0);
		//printf("#%d %d\n", t, Max);
		printf("%d\n", Max);
	}
	return 0;
}