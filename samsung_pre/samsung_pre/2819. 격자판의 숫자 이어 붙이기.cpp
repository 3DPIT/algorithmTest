#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<map>
using namespace std;
int map1[4][4];
map<string,int>m;
int ret;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
string a;
struct grid {;
	grid() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					scanf("%d", &map1[i][j]);
				}
			}
			search();
			printf("#%d %d\n", t, m.size());
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < 4 && 0 <= x && x < 4;
	}
	void dfs(int y, int x,int idx) {
		if (idx == 7) {
			if (m[a] == 1)return;
			m[a] = 1;
			return;
		}
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (safe(ny, nx)) {
				a.push_back(map1[ny][nx]+'0');
				dfs(ny, nx,idx+1);
				a.pop_back();
			}
		}
	}
	void search() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				dfs(i, j,0);
			}
		}
	}
	void init() {
		ret = 0;
		memset(map1, 0, sizeof(map1));
		m.clear();
		a.clear();
	}
}gird;
int main(void) {
	return 0;
}