#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 15
#define MS 22
int ret;
int N, M, K;
int input[NS][MS];
int Min = 0x7fffffff;//
bool chkFilm() {
	int C = 0;
	for (int x = 0; x < M; x++) {
		if (x != C)return false;
		for (int y = 0; y < N-1; y++) {
			int cnt = 1;
			for (int cy = y + 1; cy < N; cy++) {
				if (input[y][x] == input[cy][x])cnt++;
				else {
					break;
				}
				if (cnt == K)break;
			}
			if (cnt >= K) {
				C++;
				break;
			}
		}
	}
	if (C == M)return true;
	else return false;
}
void pushFill(int idx,int type) {
	for (int i = 0; i < M; i++) {
		input[idx][i] = type;
	}
}
void copy(int idx,int cinput[MS]) {
		for (int j = 0; j < M; j++) {
			cinput[j] = input[idx][j];
		}
}
void recopy(int idx, int cinput[MS]) {
	for (int j = 0; j < M; j++) {
		input[idx][j] = cinput[j];
	}
}
void dfs(int idx, int cnt) {
	if (cnt > Min)return;
	if (idx == N) {

		if (chkFilm()) {//성능을 통과하면
			Min = Min > cnt ? cnt : Min;
		}
		return;
	}
	int cinput[MS];
	copy(idx,cinput);//복사해놓기
	dfs(idx + 1, cnt);
	pushFill(idx,0);
	dfs(idx + 1, cnt+1);//A약품 투입
	pushFill(idx, 1);
	dfs(idx + 1, cnt+1);//B약품 투입
	recopy(idx, cinput);// 복원시키기
}
void init() {
	memset(input, 0, sizeof(input));
	Min = 0x7fffffff;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	dfs(0, 0);
}
int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		printf("#%d %d\n", t, Min);
	}
	return 0;
}