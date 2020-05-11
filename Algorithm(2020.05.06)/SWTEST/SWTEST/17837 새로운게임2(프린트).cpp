#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<queue>
#include<vector>
using namespace std;
#define NS 13
int ret;
int N, K;
int map[NS][NS];
int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };
struct Data {
	int num, dir;
};
struct Data2 {
	int x, y;
};
vector<Data>v1[NS][NS];
Data2 pos[11];
void init() {
	for (int i = 0; i < NS; i++) {
		for (int j = 0; j < NS; j++) {
			v1[i][j].clear();
		}
	}
	memset(pos, 0, sizeof(pos));
	ret = N=K=0;
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 1; i <= K; i++) {
		int y, x, dir;
		scanf("%d %d %d", &y, &x,&dir);
		v1[y][x].push_back({ i,dir });
		pos[i].y = y; pos[i].x=x;
	}
}
bool safe(int y, int x) {
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void play() {
	while (1) {
		if (ret == 1001) break;
		int flag = 0;
		for (int i = 1; i <= K; i++) {
			flag = 0;
			Data2 n;
			int y = pos[i].y;
			int x = pos[i].x;
			n.y = y; n.x = x;
			for (int j = 0; j < v1[y][x].size(); j++) {
				if (i == v1[y][x][j].num) {
					n.y += dy[v1[y][x][j].dir];					n.x += dx[v1[y][x][j].dir];
					
					if (safe(n.y, n.x) && map[n.y][n.x] == 0) {//Èò»ö
						for (int k = j; k < v1[y][x].size(); k++) {
							Data a =v1[y][x][k];
							v1[n.y][n.x].push_back(a);
							pos[v1[y][x][k].num].y = n.y;
							pos[v1[y][x][k].num].x = n.x;
							v1[y][x].erase(v1[y][x].begin() + k);
							k--;
						
						}
					}
					if (safe(n.y, n.x) && map[n.y][n.x] == 1) {//»¡°£
						for (int k = v1[y][x].size()-1; k >=j; k--) {
							Data a = v1[y][x][k];
							v1[n.y][n.x].push_back(a);
							pos[v1[y][x][k].num].y = n.y;
							pos[v1[y][x][k].num].x = n.x;
							v1[y][x].erase(v1[y][x].begin()+k);
						}
					}
					if (!safe(n.y, n.x) || map[n.y][n.x] == 2) {//ÆÄ¶õ
						n.y -= dy[v1[y][x][j].dir];
						n.x -= dx[v1[y][x][j].dir];
						if (v1[y][x][j].dir == 1) {
							v1[y][x][j].dir = 2;
						}
						else if (v1[y][x][j].dir == 2) {
							v1[y][x][j].dir = 1;
						}
						else if (v1[y][x][j].dir == 3) {
							v1[y][x][j].dir = 4;
						}
						else if (v1[y][x][j].dir == 4) {
							v1[y][x][j].dir = 3;
						}
						n.y += dy[v1[y][x][j].dir];
						n.x += dx[v1[y][x][j].dir];
					
						if (map[n.y][n.x] == 2 || !safe(n.y, n.x)) {
							break;
						}
						else {
							if (safe(n.y, n.x) && map[n.y][n.x] == 0) {//Èò»ö
								for (int k = j; k < v1[y][x].size(); k++) {
									Data a = v1[y][x][k];
									v1[n.y][n.x].push_back(a);
									pos[v1[y][x][k].num].y = n.y;
									pos[v1[y][x][k].num].x = n.x;
									v1[y][x].erase(v1[y][x].begin() + k);
									k--;

								}
							}
							if (safe(n.y, n.x) && map[n.y][n.x] == 1) {//»¡°£
								for (int k = v1[y][x].size() - 1; k >= j; k--) {
									Data a = v1[y][x][k];
									v1[n.y][n.x].push_back(a);
									pos[v1[y][x][k].num].y = n.y;
									pos[v1[y][x][k].num].x = n.x;
									v1[y][x].erase(v1[y][x].begin()+k);
								}
							}
						}
					}
				}
			}
			for (int i = 1; i <= K; i++) {
				//cout <<i<<"  "<< pos[i].y << "  "<<pos[i].x << endl;
				if (v1[pos[i].y][pos[i].x].size() >= 4) {
					flag = 1;
					break;
				}
			}
			if (flag == 1)break;
		}
		ret++;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				printf("%2d",v1[i][j].size());

			}
			printf("\n");
		}
		for (int i = 1; i <= K; i++) {
			//cout <<i<<"  "<< pos[i].y << "  "<<pos[i].x << endl;
			if (v1[pos[i].y][pos[i].x].size() >= 4) {
				flag = 1;
				break;
			}
		}
		if (flag == 1)break;
	}
}
int main(void) {
	int T;
	T = 5;
	for (int t = 1; t <= T; t++) {
		init();

		play();
		if (ret == 1001)ret = -1;
		printf("#%d %d\n", t,ret);
		printf("%d\n", ret);
	}
	return 0;
}