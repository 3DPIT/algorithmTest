#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 11
int N, M;
int map[NS][NS];
int islandRoadChk[7][NS][NS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int v[NS][NS];
int Min = 0x7ffffff;
int Road;
int mainNum;
vector<int>G[8];
void ccopy(vector<int>G[8], vector<int>CG[8]) {


}
bool safe(int y, int x) {
	if (0 <= y&&y < N && 0 <= x&&x < M)return true;
	else return false;
}
void copy(int map[NS][NS], int cmap[NS][NS]) {
	for (int i = 0; i < N; i++) {
		for(int j=0;j<M;j++){
			cmap[i][j] = map[i][j];
		}
	}
}
bool structRoad(int y, int x,int dir) {
	int chkMap[NS][NS] = { 0, };
	int NN = map[y][x];
	int ny = y + dy[dir]; int nx = x + dx[dir];
	int cnt = 0;
	int flag = 0;
	mainNum++;
	while (1) {
		if (map[ny][nx] !=0&&map[ny][nx]!=9)break;
		if (safe(ny, nx)) {
			islandRoadChk[1][ny][nx]=mainNum;
			map[ny][nx] = 9;
			Road++;
			cnt++;
		}
		else if (!safe(ny, nx)) {
			flag = 1;
			break;
		}
		ny += dy[dir]; nx += dx[dir];
	}

	if (cnt >= 2 && flag == 0) {
		G[NN].push_back(map[ny][nx]);
		return true;// 다리는 2 이상 섬과 연결되어있어야함 
	}
	else return false;// 그게 아니라면 다리 연결 못함
}
int fff;
int NNN;
int num[8];
struct SumDfs {
	void dfs(int idx) {
		for (int i = 0; i < G[idx].size(); i++) {
			if (num[G[idx][i]] == 0) {
				num[G[idx][i]] = 1;
			}
		}
	}
	void dfs1(int y, int x,int cnt) {
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir]; int nx = x + dx[dir];
			if (safe(ny, nx) && 1== map[ny][nx] && 0 == v[ny][nx]) {
				map[ny][nx] = cnt;
				v[ny][nx] =1;
				dfs1(ny, nx,cnt);
			}
		}
	}
	void dfs(int y, int x, int idx) {
		if (y == N || x == M) {// 탈출 조건
			return;
		}
		else {
			if (islandCombinChk()) {
				if (Road < Min) Min = Road;
			}
		}
		for (int i = y; i < N; i++) {
			for (int j = x; j < M; j++) {
				if (0!= map[i][j]&&9!=map[i][j]) {// 섬 찾기
					for (int dir = 0; dir < 4; dir++) {
						int ny = i + dy[dir];
						int nx = j + dx[dir];
						int cmap[NS][NS] = { 0, };
						int cchk[NS][NS] = { 0, };
						vector<int>CG[8];
						for (int i = 0; i < 8; i++) {
							CG[i].clear();
						}
						int copyRoad = 0;
						if (safe(ny, nx) && 0!= map[ny][nx]) {
							for (int i = 0; i < 8; i++) {
								if (CG[i].size() == 0) continue;
								for (int j = 0; j < CG[i].size(); i++) {
									CG[i][j] = G[i][j];
								}
							}
							copy(map, cmap);//맵 카피
							copy(islandRoadChk[1], cchk);
							copyRoad = Road;
							if (structRoad(ny, nx, dir)) {
								dfs(i, j + 1, idx++);
							}
							copy(cmap, map);// 맵 복구
							copy(cchk, islandRoadChk[1]);
							G->clear();
							for (int i = 0; i < 8; i++) {
								if (G[i].size() == 0) continue;
								for (int j = 0; j < G[i].size(); i++) {
									G[i][j] = CG[i][j];//
								}
							}
							Road = copyRoad;
						}
					}
				}
			}
		}
	}
	bool islandCombinChk() {
		int num[9999] = { 0, };

		memset(v, 0, sizeof(v));
		int cnt = 0;
		int cnt1 = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (islandRoadChk[1][i][j]!=0&&num[islandRoadChk[1][i][j]] == 0) {
					num[islandRoadChk[1][i][j]] = 1;
					cnt1++;
				}
			}
		}
		for (int i = 2; i <= NNN; i++) {
			if (num[i] == 0) {
				num[i] = 1;
				cnt++;
				dfs(i);
			}
		}

		if (cnt == 1)return true;
		else return false;
	}
	void islandSearch() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (0!=map[i][j]) {
					D.dfs(i, j, 0);
				}
			}
		}
	}
}D,S;



void init() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	int chk[NS][NS] = { 0, };
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1&&v[i][j]==0) {
				cnt++;
				v[i][j] = 1;
				map[i][j] = cnt;
				D.dfs1(i, j,cnt);
			}
		}
	}
	memset(v, 0, sizeof(v));
	NNN = cnt;
	D.islandSearch();
}
int main(void) {
	init(); 
	cout<<Min<< endl;
	return 0;
}