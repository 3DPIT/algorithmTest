#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
#define NS 502
#define MS 502
int map[NS][MS];
int N, M,ret;
int Max = 0x80000000;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int visit[NS][MS];
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << "  " << visit[i][j];
			}
			cout << endl;
		}
	}

}
void init() {
	N = M = 0;
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
void dfs(int y, int x, int cnt,int sum) {
	if (cnt == 3) {
		//print("dfs결과", 0);
	//	cout << sum << endl;
		Max = Max < sum ? sum : Max;
		return;
	}
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (safe(ny, nx)&&visit[ny][nx]==0) {
			visit[ny][nx] = 1;
			dfs(ny, nx, cnt + 1, sum + map[ny][nx]);
			visit[ny][nx] = 0;
		}
	}
}
int A[4][3][3] = {
	{
{0,1,0},
{1,1,1},
{0,0,0}
	},
	{
{1,0,0},
{1,1,0},
{1,0,0}
	},
	{
{1,1,1},
{0,1,0},
{0,0,0}
	},
	{
{0,1,0},
{1,1,0},
{0,1,0}
	}
};
void lastMax() {

		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= M; j++) {
				for (int k = 0; k < 4; k++) {
					int sum = 0;
					for (int ci = 0; ci < 3; ci++) {
						for (int cj = 0; cj < 3; cj++) {
							//print("아 그리기", 1);
							cout << A[k][ci][cj];
							if (A[k][ci][cj] == 1) {
								
								sum += map[i+ci][j+cj];
							}
						}
						cout << endl;
					}
					//cout <<"아"<< sum << endl;
					cout << endl;
					Max = Max < sum ? sum : Max;
			}
		}

	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();

		for (int i = 0; i <N; i++) {
			for (int j = 0; j < M; j++) {
				visit[i][j] = 1;
				dfs(i, j, 0, map[i][j]);
				visit[i][j] = 0;
			}
		}
		//ㅗ ㅏ ㅜ ㅓ 에대해서 맥스만
		lastMax();
		printf("#%d %d\n", t,Max);
		printf("%d\n", Max);
	}
	return 0;
}