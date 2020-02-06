#include<stdio.h>
#include<queue>
using namespace std;
#define S 505
int N, M, A, B, K;
int map[S][S];
int chkMap[S][S];
int sy, sx, ey, ex;
int flag;
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
struct Data {
	int y, x, cnt;
};
struct StarGame {

	StarGame() {
		scanf("%d %d %d %d %d", &N, &M, &A, &B, &K);
		for (int ki = 0; ki < K; ki++) {
			int mapY, mapX;
			scanf("%d %d", &mapY, &mapX);
			map[mapY-1][mapX-1] = -1;// 장애물 표시
		}
			scanf("%d %d", &sy, &sx);
			scanf("%d %d", &ey, &ex);
		
	}
	bool safe(int y, int x) {//장애물 확인및 범위 확인 
		for (int i = 0; i <A; i++) {
			for (int j = 0; j <B; j++) {
				if (map[y+i][x+j] == -1)return false;
				if (0 > y+i || y+i >= N || 0 > x+j || x+j >= M)return false;
			}
		}
		return true;
	}
	void bfs() {
		queue<Data>q;
		q.push({ sy-1,sx-1,0 });
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			if (c.y == ey-1 && c.x == ex-1) {// 최소 도달
				printf("%d\n", c.cnt);
				flag = 1;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && map[n.y][n.x] == 0 && chkMap[n.y][n.x] == 0) {
					chkMap[n.y][n.x] = 1;
					q.push(n);
				}
			}

		}

	}
};

int main(void) {
	StarGame moveStart;
	moveStart.bfs();
	if (flag == 0) {
		printf("-1");
	}
	return 0;
}