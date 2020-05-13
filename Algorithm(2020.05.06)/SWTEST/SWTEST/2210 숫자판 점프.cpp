#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include<string>
#include<map>
using namespace std;
//c++!4 컴파일로 돌려야함
int map1[5][5];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int ret = 0;
map<string, int>m;
string v;
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		cout << v << " " << endl;
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < 5 && 0 <= x && x < 5;
}
void dfs(int y, int x, int d) {
	if (d == 6) {
		//print("벡터상태", 0);
		if (m[v] == 0) {
			m[v] = 1;
			ret++;
		}
		//todo
		return;
	}
	for (int dir = 0; dir < 4; dir++) {
		v += to_string(map1[y][x]);
		if (safe(y + dy[dir], x + dx[dir])) {
			dfs(y + dy[dir], x + dx[dir], d + 1);
		}
		v.pop_back();
	}

}

void init() {
	ret = 0;
	memset(map1, 0, sizeof(map1));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d", &map1[i][j]);
		}
	}
}
int main(void) {
	init();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			dfs(i, j, 0);
		}
	}
	cout << ret << endl;
	return 0;
}