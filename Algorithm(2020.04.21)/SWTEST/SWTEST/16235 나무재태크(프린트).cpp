
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
#define NS 11
int N, M, K, ret;
vector<int>map[NS][NS];
int input[NS][NS];
int cinput[NS][NS];
int road[NS][NS];
int dy[] = { -1,-1,-1,0,0,1,1,1 };
int dx[] = { -1,0,1,-1,1,-1,0,1 };
bool safe(int y, int x) {
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void init() {

	N = M = K = ret = 0;
	for (int i = 1; i <= NS; i++) {
		for (int j = 1; j <= NS; j++) {
			map[i][j].clear();
			input[i][j] = 0;
			cinput[i][j] = 0;
			road[i][j] = 0;
		}
	}
}
void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sort(map[i][j].begin(), map[i][j].end());
			if (map[i][j].size() != 0) {
				for (int k = 0; k < map[i][j].size(); k++) {

					if (input[i][j] - map[i][j][k] >= 0) {//¾çºĞ Èí¼ö
						input[i][j] -= map[i][j][k];
						map[i][j][k]++;
					}
					else {//¾çºĞ Èí¼ö ¸øÇÏ¹È
						cinput[i][j] = map[i][j][k] / 2;
						map[i][j].erase(map[i][j].begin() + k);
						k--;
					}
				}
			}
		}
	}
}
void summer() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			input[i][j] += cinput[i][j];
			cinput[i][j] = 0;
		}
	}
}
void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() != 0) {
				for (int k = 0; k < map[i][j].size(); k++) {
					if (map[i][j][k] % 5 == 0) {
						for (int dir = 0; dir < 8; dir++) {
							int ny = i + dy[dir];
							int nx = j + dx[dir];
							if (safe(ny, nx)) {
								map[ny][nx].push_back(1);
							}
						}
					}
				}
			}
		}
	}
}
void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			input[i][j] += road[i][j];
		}
	}
}
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << "  " << road[i][j];
			}
			cout << endl;
		}
	}
	if (idx == 1) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << "  " << input[i][j];
			}
			cout << endl;
		}
	}
}

void R2D2Start() {
	spring();
	print("¶¥»óÅÂ", 1);
	summer();
	print("¾çºĞ¼·ÃëÈÄ ¶¥»óÅÂ", 1);
	fall();
	winter();
}
void cntTree() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() != 0) {
				ret += map[i][j].size();
			}
		}
	}
}
int main(void) {
	int T = 8;
	for (int t = 1; t <= T; t++) {
		init();
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				input[i][j] = 5;
				scanf("%d", &road[i][j]);
			}
		}
		print("ÀÔ·ÂµÈ ¶¥", 0);
		print("¿ø·¡ ¶¥", 1);
		for (int i = 0; i < M; i++) {
			int y, x, age;
			scanf("%d %d %d", &y, &x, &age);
			map[y][x].push_back(age);
		}
		for (int i = 0; i < K; i++) R2D2Start();
		cntTree();
		printf("#%d %d\n", t, ret);
		//printf("%d\n", ret);
	}
	return 0;
}