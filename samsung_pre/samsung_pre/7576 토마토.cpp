#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define NS 1000
#define MS 1000
int map[NS][MS];
int chk[NS][MS];
int zeroNum;
int N, M;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, cnt;
};
queue<Data>q;
bool safe(int y, int x) {
	if (y < 0 || y >= N||x < 0 || x >= M) return false;
	else return true;
}
void tomatoLevelUp() {
	int NCNT = 0;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = c.y + dy[dir];
			n.x = c.x + dx[dir];
			n.cnt = c.cnt + 1;
			if (safe(n.y, n.x) && map[n.y][n.x] == 0 && chk[n.y][n.x] == 0) {
				chk[n.y][n.x] = n.cnt;
				NCNT = n.cnt;
				zeroNum--;
				q.push({ n.y,n.x,n.cnt });
			}
		}
	}

	if (zeroNum == 0) {
		cout << NCNT << endl;
		return;
	}
	else {
		cout << -1 << endl;
		return;
	}
}
void init() {
	cin >>M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)zeroNum++;
			if (map[i][j] == 1)q.push({ i, j, 0 });
		}
	}
	if (zeroNum == 0) {
		cout << 0 << endl;
		return ;
	}
	tomatoLevelUp();

}
int main(void) {
	init();
	return 0;
}