#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
#define NS 9
#define MS 9
int N, M;
int map[NS][MS];
int visit[NS][MS];
int ret;
int Max;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
void init() {
	N = M = ret = 0;
	Max = 0x80000000;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfsVirus(int y, int x) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (safe(ny,nx)&&map[ny][nx] == 0 && visit[ny][nx] == 0) {
			visit[ny][nx] = 1;
			dfsVirus(ny, nx);
		}
	}
}
void Virus() {
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 2) {
				visit[i][j] = 1;
				dfsVirus(i, j);
			}
		}
	}
}
int zeroCnt() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0&&visit[i][j]==0)cnt++;
		}
	}
	return cnt;
}
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout <<" "<<map[i][j];
			}
			cout << endl;
		}
	}
}
void copy(int cmap[NS][MS], int map[NS][MS])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cmap[i][j] = map[i][j];
		}
	}
}
void dfs(int y, int x, int cnt) {
	if (cnt == 3) {
	//	print("벽설치", 1);
		Virus();
		int cnt=zeroCnt();
	//	print("바이러스퍼진후", 1);
	//	cout << cnt << endl;
		Max = Max < cnt ? cnt : Max;
		return;
	}
	for (int i = y; i < N; i++) {
		for (int j = x; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 3;
				dfs(i, j + 1, cnt + 1);
				map[i][j] = 0;
			}
		}
		x = 0;
	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		dfs(0, 0, 0);
		//printf("#%d %d\n", t, Max);
		printf("%d\n", Max);
	}
	return 0;
}