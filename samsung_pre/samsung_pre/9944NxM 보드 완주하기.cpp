#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
using namespace std;
#define S 31
int N, M;
int ret = 0x7fffffff;
int zero;
char map[S][S];
int visit[S][S];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
struct Board {
	Board() {
		int t = 0;
		while (cin >> N >> M) {
			t++;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					scanf(" %1c", &map[i][j]);
					if (map[i][j] == '.') {
						zero++;
					}
				}
			}
			search();
			if (0x7fffffff == ret)ret = -1;//¸ø°¡¸é -1
			if (zero == 1)ret = 0;
			printf("Case %d: %d\n", t, ret);
			init();
		}
	}
	void search() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == '.') {
					for (int dir = 0; dir < 4; dir++) {
						reArr(visit);
						visit[i][j] = 1;
						dfs(i, j, 1, dir, 1);
						visit[i][j] = 0;
					}
				}
			}
		}
	}
	void dfs(int y, int x, int cnt, int dir, int mainC) {
		if (cnt == zero) {
			if (ret > mainC)ret = mainC;
			return;
		}
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (safe(ny, nx) && map[ny][nx] == '.'&&visit[ny][nx] == 0) {
			visit[ny][nx] = 1;
			dfs(ny, nx, cnt + 1, dir, mainC);
			visit[ny][nx] = 0;
		}
		else {
			for (int dir1 = 0; dir1 < 4; dir1++) {
				if (dir == dir1)continue;
				int ny1 = y + dy[dir1];
				int nx1 = x + dx[dir1];
				if (safe(ny1, nx1) && map[ny1][nx1] == '.'&&visit[ny1][nx1] == 0) {
					visit[ny1][nx1] = 1;
					dfs(ny1, nx1, cnt + 1, dir1, mainC + 1);
					visit[ny1][nx1] = 0;
				}
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
	void reArr(int map[S][S]) {
		memset(map, 0, sizeof(map));
	}
	void init() {
		N = M = zero = 0;
		ret = 0x7fffffff;
		memset(map, 0, sizeof(map));
		memset(visit, 0, sizeof(visit));
	}

}Board;
int main(void) {

	return 0;
}