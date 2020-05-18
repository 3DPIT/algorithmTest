#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
using namespace std;
#define S 501
int N, M;
int board[S][S];
int ret[S*S];
int D[S][S];
int dy[] = { -1,-1,-1,0,0,1,1,1 };
int dx[] = { -1,0,1,-1,1,-1,0,1 };
int chk[S][S];
int p[S*S];
int find(int num) {
	if (num == p[num])return num;
	return p[num] = find(p[num]);
}

bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void init() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
			D[i][j] = -1;
		}
	}
}
int dfs(int y, int x) {

	int cnt = 0;
	int cy = y;
	int cx = x;
	int ny = y;
	int nx = x;
	int nMin = 0x7fffffff;
	int nny = 0x7fffffff;
	int nnx = 0x7fffffff;
	for (int dir = 0; dir < 8; dir++) {
		ny = cy+dy[dir];
		nx =cx + dx[dir];
		if (safe(ny, nx) && board[ny][nx] < board[y][x]) {
			if (nMin > board[ny][nx]) {
				nMin = board[ny][nx];
				nny = ny;
				nnx = nx;
			}

		}
		else {
			cnt++;
		}
	}
	if (cnt == 8||nMin==0x7fffffff) {
		chk[y][x]++;
		return 0;
	}
	if (D[nny][nnx] != -1)return D[nny][nnx];
	D[nny][nnx] = dfs(nny, nnx);
	return D[nny][nnx];
}
int main(void) {
	init();
	for (int i = 0; i < N; i++) {
		for (int j= 0; j < M; j++) {
			int nMin = 0x7fffffff;
			int y=i, x=j;
			for (int dir = 0; dir < 8; dir++) {
				int ny = i + dy[dir];
				int nx = j + dx[dir];
				if (safe(ny, nx) && board[ny][nx] < board[i][j]) {
					if (nMin > board[ny][nx]) {
						nMin = board[ny][nx];
						y = ny;
						x = nx;
					}
				}
			}
			p[(i*M) + j] =(y*M) + x;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret[find((i*M) + j)]++;
		}
		//cout << endl;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << ret[(i*M)+j] << " ";
		}
		cout << endl;
	}
	return 0;
}