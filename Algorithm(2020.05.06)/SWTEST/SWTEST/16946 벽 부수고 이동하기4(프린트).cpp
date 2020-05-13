#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define NS 1001
int N, M;
char inp[NS][NS];
int v[(NS*NS / 2 )+2];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int cinp[NS][NS];
int chk[NS][NS];
int c = 0;
void init() {
	memset(inp, 0, sizeof(inp));
	memset(cinp, 0, sizeof(cinp));
	memset(chk, 0, sizeof(chk));
	memset(v, 0, sizeof(v));

	N = M;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &inp[i][j]);
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x,int cnt) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (safe(ny, nx) && inp[ny][nx] == '0'&&chk[ny][nx] == 0) {
			chk[ny][nx] = cnt;
			v[cnt]++;
			dfs(ny, nx,cnt);
		}
	}
}
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << chk[i][j];
			}
			cout << endl;
		}

		}
	if (idx != 0) {
	for (int i = 1; i <= idx; i++) {
		cout<<i<<"  "<< v[i] << endl;
		}
	}
}
void DFS() {
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (inp[i][j] == '0'&&chk[i][j]==0) {
				v[cnt]++;
				chk[i][j] = cnt;
				dfs(i, j,cnt);
				cnt++;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (inp[i][j] == '1') {
				for (int dir = 0; dir < 4; dir++) {
					int ny = i + dy[dir];
					int nx = j + dx[dir];
					if (safe(ny, nx) &&inp[ny][nx]=='0'&& chk[ny][nx] != 0) {
						cinp[i][j] += v[chk[ny][nx]];
					}
				}
				cinp[i][j] += 1;
			}
		}
	}
	print("플러드필", 0);
	print("0의수", cnt);

}
int main(void) {
	int T = 1;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		DFS();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cinp[i][j] %= 10;
				cout << cinp[i][j];
			}
			cout << endl;
		}
	}

	return 0;
}