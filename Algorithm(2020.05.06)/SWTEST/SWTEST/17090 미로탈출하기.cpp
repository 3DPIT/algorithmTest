#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
#define S 501
int N, M, ret;
int D[S][S];
bool visit[S][S];
char input[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int dirToIdx(char dir) {
	if (dir == 'U')return 3;
	else if (dir == 'R')return 0;
	else if (dir == 'D')return 1;
	else if (dir == 'L')return 2;
}
void init() {
	N = M = 0;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &input[i][j]);
			D[i][j] = -1;
		}
	}
}
bool isafe(int y, int x) {
	return y < 0 || y >= N || x < 0 || x >= M;
}
int dfs(int y, int x) {
	if (isafe(y,x)) return 1;// ∏Ò«• ∞Ò¿Œ
	if (D[y][x] != -1)return D[y][x];
	D[y][x] = 0;
	int dir = dirToIdx(input[y][x]);
	D[y][x] = dfs(y + dy[dir], x + dx[dir]);
	return D[y][x];
}
int main(void) {
	init();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret += dfs(i, j);
		}
	}
	cout << ret << endl;
	return 0;
}