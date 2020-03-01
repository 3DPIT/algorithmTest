#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define NS 11
int map[NS][NS];
int D[NS][NS];
int N, M, C;
int ret;
int ret1[3];
struct Data {
	int y; int x;
};
vector<Data>v[3];
struct Honey {
	Honey() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			scanf("%d %d %d", &N, &M, &C);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					scanf("%d", &map[i][j]);
				}
			}
			dfs(0, 0,1);
			printf("#%d %d\n", t, ret);
		}
	}
	void init() {
		memset(map, 0, sizeof(map));
		memset(D, 0, sizeof(D));
		for (int i = 1; i < 3; i++) {
			ret1[i] = 0x80000000;
		}		for (int i = 0; i <= 2; i++) {
			v[i].clear();
		}
		ret = 0x80000000;
	}
	void copy(int map[NS][NS], int cmap[NS][NS]) {
		for (int i = 0; i < NS; i++) {
			for (int j = 0; j < NS; j++) {
				cmap[i][j] = map[i][j];
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < N;
	}
	bool able(int y,int x,int idx) {
		for (int i = 0; i < M; i++) {
			if (safe(y, x)&&D[y][x]==0) {
				D[y][x++] = idx;
			}
			else return 0;
		}
		return 1;
	}
	void gainHoney() {
		for (int i = 0; i < 3; i++) {
			v[i].clear();
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (D[i][j] != 0) {
					v[D[i][j]].push_back({ i, j });
				}
			}
		}

		for (int i = 1; i < 3; i++) {
		ret1[i]=0x80000000;
		}
		dfs(0,0,0,1);//ÀÏ¹ø ¹ú²Ü
		dfs(0,0,0,2);//ÀÌ¹ø ¹ú²Ü
		if (ret < ret1[1] + ret1[2])ret = ret1[1] + ret1[2];
	}
	void dfs(int idx,int sum,int finalSum, int num) {//idx 1¿¡ ´ëÇØ¼­ 
		if (idx == M) {
			if (sum <= C) {
				if (ret1[num] < finalSum)ret1[num] = finalSum;
			}
			return;
		}
		dfs(idx + 1, sum + map[v[num][idx].y][v[num][idx].x],finalSum+((map[v[num][idx].y][v[num][idx].x])*(map[v[num][idx].y][v[num][idx].x])),num);
		dfs(idx + 1, sum,finalSum,num);
	}
	void dfs(int y, int x, int idx) {
		if (idx == 3) {
			gainHoney();
			return;
		}
		int cmap[NS][NS] = { 0, };
		for (int i = y; i < N; i++) {
			for (int j = x; j < N; j++) {
				copy(D,cmap);
				if (able(i,j,idx)) {
					dfs(y , x + 1, idx + 1);
				}
				copy(cmap, D);
			}
			x = 0;
		}
	}
}Honey;
int main(void) {
	return 0;
}