#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
#define NS 101
int N, x, y, d, g,ret;
int dy[] = { 0,-1,0,1 };//0 1 2 3
int dx[] = { 1,0,-1,0 };
vector<int>dragonLoad;
int map[NS][NS];
void init() {
	N = x = y = d = g = ret = 0;
	dragonLoad.clear();
	memset(map, 0, sizeof(map));
}
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < dragonLoad.size(); i++) {
			cout << dragonLoad[i] << " ";
		}
		cout << endl;
	}
	if (idx == 1) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << "  " << map[i][j];
			}
			cout << endl;
		}
	}
}
void squreCnt() {
	for (int i = 0; i < NS-1; i++) {
		for (int j = 0; j < NS-1; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1
				&& map[i + 1][j] == 1 && map[i + 1][j + 1] == 1) {
				ret++;
			}
		}
	}
}
void dragonWrite() {
	while (dragonLoad.size()) {
		map[y][x] = 1;
		int dir = dragonLoad.front();
		y += dy[dir]; x += dx[dir];
		dragonLoad.erase(dragonLoad.begin());
	}
	map[y][x] = 1;
}
void DragonLife() {
	scanf("%d", &N);
	for (int i = 0; i <N; i++) {
		scanf("%d %d %d %d", &x, &y, &d, &g);
		dragonLoad.push_back(d);
		for (int gi = 0; gi < g; gi++) {
			for (int j = dragonLoad.size() - 1; j >= 0; j--) {
				int dir = dragonLoad[j] +1;
				if (dir == 4)dir = 0;
				dragonLoad.push_back(dir);
			}
		}
		print("µÂ∑°∞Ô¿Ãµø",0);
		dragonWrite();
		print("µÂ∑°∞Ô∞Ê∑Œ", 1);
		dragonLoad.clear();
	}
	squreCnt();
}
int main(void) {
	int T = 4;
	for (int t = 1; t <= T; t++) {
		init();
		DragonLife();
		printf("#%d %d\n", t, ret);
		//printf("%d\n", ret);
	}
	return 0;
}