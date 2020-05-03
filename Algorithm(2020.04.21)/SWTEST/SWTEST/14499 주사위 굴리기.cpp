#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using namespace std;
#define NS 21
int map[NS][NS];
int N, M, K;
int y, x;
int d[7];
int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };
void init() {
	memset(d, 0, sizeof(d));
	N = M = K;
	memset(map, 0, sizeof(map));
	scanf("%d %d %d %d %d",
		&N, &M, &y, &x, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
void copy(int d[7], int cd[7]) {
	for (int i = 0; i < 7; i++) {
		d[i] = cd[i];
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void print(string name, int idx) {
	cout << name << idx << endl;
	for (int i = 1; i < 7; i++) {
		cout << "  " << d[i];
	}
	cout << endl;
}
void dise() {
	int ny = y; int nx = x;
	for (int k = 0; k < K; k++) {
		int dir = 0;
		scanf("%d", &dir);
		int cd[7] = { 0, };
		ny = y + dy[dir];
		nx = x + dx[dir];
		//print("주사위 현황", dir);
		if (dir == 1 && safe(ny, nx)) {
			y = ny;
			x = nx;
			if (map[y][x] != 0) {
				d[3] = map[y][x];
				map[y][x] = 0;
			}
			else {
				map[y][x] = d[3];
			}
			cd[6] = d[3];
			cd[3] = d[1];
			cd[1] = d[4];
			cd[4] = d[6];
			cd[2] = d[2];
			cd[5] = d[5];
			copy(d, cd);

			printf("%d\n", d[1]);
		}
		if (dir == 2 && safe(ny, nx)) {
			y = ny;
			x = nx;
			if (map[y][x] != 0) {
				d[4] = map[y][x];
				map[y][x] = 0;
			}
			else {
				map[y][x] = d[4];
			}
			cd[6] = d[4];
			cd[4] = d[1];
			cd[1] = d[3];
			cd[3] = d[6];
			cd[2] = d[2];
			cd[5] = d[5];
			copy(d, cd);

			printf("%d\n", d[1]);
		}
		if (dir == 3 && safe(ny, nx)) {
			y = ny;
			x = nx;
			if (map[y][x] != 0) {
				d[2] = map[y][x];
				map[y][x] = 0;
			}
			else {
				map[y][x] = d[2];
			}
			cd[2] = d[1];
			cd[1] = d[5];
			cd[5] = d[6];
			cd[6] = d[2];
			cd[3] = d[3];
			cd[4] = d[4];
			copy(d, cd);

			printf("%d\n", d[1]);
		}
		if (dir == 4 && safe(ny, nx)) {
			y = ny;
			x = nx;
			if (map[y][x] != 0) {
				d[5] = map[y][x];
				map[y][x] = 0;
			}
			else {
				map[y][x] = d[5];
			}
			cd[6] = d[5];
			cd[5] = d[1];
			cd[1] = d[2];
			cd[2] = d[6];
			cd[3] = d[3];
			cd[4] = d[4];
			copy(d, cd);

			printf("%d\n", d[1]);
		}
	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		dise();


	}
	return 0;
}