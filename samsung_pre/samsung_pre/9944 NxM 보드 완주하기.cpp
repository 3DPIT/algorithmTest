#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define S 31
int N, M;
char map[S][S];
int zeroCnt;
int v[S][S];
int Min = 0x7fffffff;
struct Board {
	int dy[4] = { 0,1,0,-1 };
	int dx[4] = { 1,0,-1,0 };
	int c = 0;
	Board() {
		while (cin >> N >> M) {
			c++;
			init();
			for (int i = 0; i < N; i++) {
				scanf("%s", map[i]);
			}
			countPoint();// 점의 갯수 파악
			search();// 탐색 시작
			if (zeroCnt == 1) Min = 0;
			else if (Min == 0x7fffffff)Min = -1;
			cout <<"Case"<<" "<<c<<":"<<" "<< Min << endl;
		}
	}
	void init() {
		memset(v,0, sizeof(v));
		memset(map, 0, sizeof(map));
		Min = 0x7fffffff;
		zeroCnt = 0;
	}
	void countPoint() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == '.')zeroCnt++;
			}
		}
	}
	
	bool noSafe(int y, int x) {
		return y < 0 || y == N || x < 0 || x == M;
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
	void search() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == '.') {
					v[i][j] = 1;
					for (int dir = 0; dir < 4; dir++) {
						zeroCnt--;
						dfs(i, j, dir,1);
						zeroCnt++;
					}
					v[i][j] = 0;
				}
			}
		}
	}
	void dfs(int y, int x, int Mdir,int cnt) {
		if (zeroCnt == 0) {
			if (Min > cnt)Min = cnt;
			return;
		}
		int ny = y + dy[Mdir]; int nx = x + dx[Mdir];
		int ncnt = cnt + 1;
		if (noSafe(ny, nx) || map[ny][nx] == '*' || v[ny][nx] == 1) {// 방향 바꾸기
			for (int dir = 0; dir < 4; dir++) {
				if (Mdir == dir) continue;
				ny = y + dy[dir]; nx = x + dx[dir];
				if (v[ny][nx] == 0&&safe(ny,nx)&&map[ny][nx]=='.') {
					zeroCnt--;
					v[ny][nx] = 1;
					dfs(ny, nx, dir, ncnt);
					v[ny][nx] = 0;
					zeroCnt++;
				}

			}
		}
		else {// 방향그대로 탐색
			if (v[ny][nx] == 0) {
				v[ny][nx] = 1;
				zeroCnt--;
				dfs(ny, nx, Mdir, cnt);
				zeroCnt++;
				v[ny][nx] = 0;
			}
		}
	 }
}B;
int main(void) {

	return 0;
}