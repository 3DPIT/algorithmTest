#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
using namespace std;
char map[13][7];
int chk[13][7];
int flag = 0;
int cnt = 1;
int ret;
int C;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int deleteChk[75];
int lastDelete;
bool safe(int y, int x) {
	if (0 <= y && y < 12 && 0 <= x && x < 6)return true;
	else return false;
}
struct Data {
	int y, x, cnt;
};
void dfs(int y, int x, char color) {
	for (int dir = 0; dir < 4; dir++) {
		Data n;
		n.y = y + dy[dir]; n.x = x + dx[dir];
		if (safe(n.y,n.x)&&color == map[n.y][n.x] && 0 == chk[n.y][n.x]) {
			chk[n.y][n.x] = C;
			cnt++;
			dfs(n.y, n.x, color);
		}
	}
}
void down() {
	for (int x = 0; x < 6; x++) {
		vector<char>v;
		for (int y = 0; y < 12; y++) {
			if (map[y][x] != '.') {
				v.push_back(map[y][x]);
				map[y][x] = '.';
			}
		}
		int ny = 11;
		for (int i = v.size()-1; i>=0; i--) {
			map[ny--][x] =  v[i];
		}
	}
}
void deleteBlock() {
	ret++;
	for (int i = 0; i < 75; i++) {
		if (deleteChk[i] >= 4) {
			for (int y = 0; y < 12; y++) {
				for (int x = 0; x < 6; x++) {
					if (chk[y][x] == i) {
						map[y][x] = '.';
					}
				}
			}
		}
	}

	down();

}
void puyopuyoStart() {
	lastDelete = C = 0;
	memset(chk, 0, sizeof(chk));
	memset(deleteChk, 0, sizeof(deleteChk));
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if ('.' != map[i][j] && 0 == chk[i][j]) {
				C++;
				chk[i][j] = C;
				dfs(i, j, map[i][j]);
				if (cnt>=4) {
					flag = 0;
					lastDelete = 1;
					deleteChk[C] = cnt;
				}
				flag = 0;
				cnt = 1;
			}
		}
	}
}
void init() {
	for (int i = 0; i < 12; i++) {
		scanf("%s", &map[i]);
	}
	while (1) {
		puyopuyoStart();
		if (lastDelete == 0) {
			break;
		}
		deleteBlock();
	}
	cout << ret << endl;
}
int main(void) {
	init();
	return 0;
}