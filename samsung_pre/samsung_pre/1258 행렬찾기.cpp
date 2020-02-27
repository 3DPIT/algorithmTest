#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 102
int map[NS][NS];
int chk[NS][NS];
int N;
int ret;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int size, y, x;
};
bool cmp(Data a, Data b) {
	if (a.size == b.size)return a.y < b.y;
	else return a.size < b.size;
}
vector<Data>v;

struct Matrix {
	Matrix() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			scanf("%d", &N);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					scanf("%d", &map[i][j]);
				}
			}
			research();

			printf("#%d %d ", t, ret);
			sort(v.begin(), v.end(), cmp);//배열 크기가 작고 같은경우에는 y가 작은순으로 정렬
			for (int i = 0; i < v.size(); i++) {
				printf("%d %d ", v[i].y, v[i].x);
			}
			printf("\n");
		}
	}
	void yxChk(int idx,int y,int x) {
		int y1 = 0;
		int x1 = 0;
		for (int i = y; i <= N; i++) {//y체크
			y1++;
			if (map[i][x] == 0||i==N) {
				y1--;
				v[idx].y = y1;
				break;
			}
		}
		for (int j = x; j <= N; j++) {
			x1++;
			if (map[y][j] == 0||j==N) {
				x1--;
				v[idx].x = x1;
				break;
			}
		}
		v[idx].size = v[idx].y*v[idx].x;
		return;
	}

	void research() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0 && chk[i][j] == 0) {
					v.push_back({ 0,i,j });
					ret++;
					chk[i][j] = ret;
					dfs(i, j, ret);
				}
			}
		}
		for (int i = 0; i < v.size(); i++) {
			yxChk(i,v[i].y,v[i].x);
		}
	}
	void init() {
		ret = 0;
		v.clear();//배열 초기화
		memset(chk, 0, sizeof(chk));
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < N;
	}
	void dfs(int y, int x, int cnt) {
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = y + dy[dir]; n.x = x + dx[dir];
			if (safe(n.y, n.x) && map[n.y][n.x] != 0 && chk[n.y][n.x] == 0) {
				chk[n.y][n.x] = cnt;
				dfs(n.y, n.x, cnt);
			}
		}
	}
}Matrix;
int main(void) {
	return 0;
}