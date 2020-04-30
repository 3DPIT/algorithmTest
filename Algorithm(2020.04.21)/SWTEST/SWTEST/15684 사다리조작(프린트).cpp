#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
using namespace std;
#define NS 11
#define HS 101
int map[HS][NS];
int N, H, M,ret;
int Min = 0x7fffffff;
void init() {
	N = H = M = ret = 0;
	Min = 0x7fffffff;
	memset(map, 0, sizeof(map));
}
void copy(int cmap[HS][NS], int map[HS][NS]) {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			cmap[HS][NS] = map[HS][NS];
		}
	}
}
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i <= H; i++) {
			for (int j = 0; j <= N; j++) {
				printf("%3d", map[i][j]);
			}
			printf("\n");
		}
	}
}
bool downStart() {
	int y = 1;
	int j = 1;
	int cnt = 0;
	for (int j = 1; j < N + 1; j++) {
		y = 0;
		int yi = j;
		while (y!= H + 1) {
			if (map[y][j] == 1) {//->
				y++;
				j++;
			}
			else if (map[y][j - 1] == 1) {//<-
				y++;
				j--;
			}
			else {
				y++;
			}
			cout << y << j << endl;
		}
		if (yi == j)cnt++;
		cout << yi << j << endl;
	}
	if (cnt == N) return true;
	else return false;
}
void dfs(int y, int x, int cnt) {
	if (cnt > 3)return;
	if(cnt<=3){
	//	print("map다리건설", 0);
		if (downStart()) {
			if (Min > cnt)Min = cnt;
		}
	}
	int cmap[HS][NS] = { 0, };
	for (int i = y; i <=H; i++) {
		for (int j = x; j < N; j++) {
			copy(cmap, map);
			if (map[i][j - 1] == 0 && map[i][j + 1] == 0&&map[i][j]==0) {
				map[i][j] = 1;
				dfs(i, j+1, cnt+1);
				map[i][j] = 0;
			}
			copy(map, cmap);
		}
		x = 1;
	}
}
int main(void) {
	int T = 7;
	for (int ti = 1; ti <= T; ti++) {
		init();
		scanf("%d %d %d", &N, &M, &H);
		for (int i = 0; i < M; i++) {
			int y, x;
			scanf("%d %d", &y, &x);
			map[y][x] = 1;
		}
		dfs(1,1,0);
		//printf("#%d %d", ti, ret);
		printf("%d\n", Min);
	}
	return 0;
}