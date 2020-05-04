#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<queue>
using namespace std;
#define NS 11
int N, M;
char map[NS][NS];
int chk[NS][NS][NS][NS];
int ry, rx, by, bx, hy, hx;
int ret;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int ry, rx, by, bx, cnt;
};
void init() {
	N = M = 0;
	ret = ry = rx = by = bx = hy = hx = 0;
	memset(map, 0, sizeof(map));
	memset(chk, 0, sizeof(chk));
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &map[i][j]);
			if (map[i][j] == 'R') {
				ry = i;
				rx = j;
				map[i][j] = '.';
			}
			else if (map[i][j] == 'B') {
				by = i;
				bx = j;
				map[i][j] = '.';
			}
			else if (map[i][j] == 'O') {
				hy = i;
				hx = j;
				map[i][j] = '.';
			}
		}
	}
}
//bool safe(int y, int x) {
//	
//}
void BFS() {
	queue<Data>q;
	q.push({ ry,rx,by,bx,0 });
	while (!q.empty()) {
		
		Data c = q.front(); q.pop();
		if (c.cnt > 10) {
			printf("-1\n");
			break;
		}
		if (c.ry == hy && c.rx == hx) {
			printf("%d\n", c.cnt);
			break;
		}
		for (int dir = 0; dir < 4; dir++) {

			Data n;
			n.ry = c.ry + dy[dir];
			n.rx = c.rx + dx[dir];
			n.by = c.by + dy[dir];
			n.bx = c.bx + dx[dir];
			n.cnt = c.cnt + 1;

			int h1, h2;
			h1 = h2 = 0;
			while (1) {//레드
				if (n.ry == hy && n.rx == hx) {
					h1 = 1;
					break;
				}
				if (map[n.ry][n.rx] == '#')break;
				n.ry += dy[dir];
				n.rx += dx[dir];
			}
			while (2) {//블루
				if (n.by == hy && n.bx == hx) {
					h2 = 1;
					break;
				}
				if (map[n.by][n.bx] == '#')break;
				n.by += dy[dir];
				n.bx += dx[dir];
			}
			if (h1&&h2) {//둘다 빠진경우
				continue;
			}
			if (h1&&h2 == 0) {//빨강만 빠진경우
				if (n.ry == n.by&&n.rx == n.bx) {
					int dr = abs(n.ry - c.ry) + abs(n.rx - c.rx);
					int db = abs(n.by - c.by) + abs(n.bx - c.bx);
					if (dr > db) {//레드를 뒤로
						n.ry -= dy[dir];
						n.rx -= dx[dir];
					}
					else {//블루를 뒤로
						n.by -= dy[dir];
						n.bx -= dx[dir];
					}
			}
		}
			if (h1 == 0 && h2) {//파랑만 빠진경우
				continue;
			}
			if (chk[n.ry][n.rx][n.by][n.bx] == 0) {
				chk[n.ry][n.rx][n.by][n.bx] = 1;
				q.push(n);
			}
		}
	}
}
int main(void) {
	int T = 7;
	for (int t = 1; t <= T; t++) {
		init();
		//printf("%d %d %d %d %d %d\n", ry, rx, by, bx, hy, hx);
		
		BFS();
		printf("#%d %d\n", t, ret);
		printf("%d\n", ret);
	}
	return 0;
}