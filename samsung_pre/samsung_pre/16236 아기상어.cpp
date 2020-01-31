#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define NS 21
int map[NS][NS];
int chk[NS][NS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N;
int ret;
bool safeZone(int y, int x) {
	if (0 <= y && y< N && 0 <= x && x< N)return true;
	else return false;
}
struct Shark {
	int sharkMinY;
	int sharkMinX;
	int sharkCnt;
	int sharkFlag;
	Shark () {
		 sharkMinY = 0x7fffffff;
		 sharkMinX = 0x7fffffff;
		 sharkCnt = 0x7fffffff;
		 sharkFlag = 0;
	}
};
struct queueData {
	int y, x, cnt;
};
void sharkEatPlay() {
	queue<queueData>q;
	int forFlag = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 9) {
				map[i][j] = 0;
				q.push({ i,j,0 });
				forFlag = 1;
				chk[i][j] = 1;
				break;
			}
			if (forFlag)break;
		}
	}// 상어 위치 찾아 넣기
	int sharkEat = 0;
	int sharkSize = 2;
	int sharkTime = 0;
	while (1) {
		Shark S;
		while (!q.empty()) {
			queueData c = q.front(); q.pop();
			if (c.cnt > S.sharkCnt)break;
			if (map[c.y][c.x]!=0&&map[c.y][c.x] < sharkSize &&c.cnt <= S.sharkCnt) {
				S.sharkFlag = 1;
				S.sharkCnt = c.cnt;
				if (c.y < S.sharkMinY || ((c.y == S.sharkMinY && (c.x < S.sharkMinX)))) {
				 S.sharkMinY = c.y;
					S.sharkMinX=c.x;
				}
			}
			for (int dir = 0; dir < 4; dir++) {
				queueData n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safeZone(n.y,n.x)&&0 == chk[n.y][n.x] &&sharkSize>= map[n.y][n.x]) {
					chk[n.y][n.x] = 1;
					q.push(n);
				}
			}
		}
		if (S.sharkFlag == 1) {// 먹을 놈이있으며
			sharkEat++;
			sharkTime += S.sharkCnt;
			if (sharkEat == sharkSize) {
				sharkSize++;
				sharkEat = 0;
			}
			while (!q.empty())q.pop();
			memset(chk, 0, sizeof(chk));
			q.push({ S.sharkMinY,S.sharkMinX,0 });
			map[S.sharkMinY][S.sharkMinX] = 0;
			chk[S.sharkMinY][S.sharkMinX] = 1;
		}
		else {
			break;
		}
	}
	ret = sharkTime;
}
void init() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	sharkEatPlay();
	cout << ret << endl;
}
int main(void) {
	init();

	return 0;
}