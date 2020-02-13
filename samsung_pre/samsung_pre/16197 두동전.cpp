#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
#define S 21
int N, M;
char map[S][S];
bool visit[S][S][S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int ret = 0x7fffffff;
struct Data {
	int y1; int x1; int y2; int x2; int cnt;
};
struct Coin {
	Coin() {
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf(" %1c", &map[i][j]);
			}
		}
	}
	bool safe(int y, int x) {// 범위 포함하는 경우
		return 1 <= y && y <= N && 1 <= x && x <= M;
	}
	bool safe(int y, int x, int num) {//범위 벗어난경우
		return y <=0 || y >= N+1 || x<=0 || x >= M+1;
	}
	void bfs() {
		queue<Data>q;
		int y1, y2, x1, x2;
		int flag = 1;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (map[i][j] == 'o'&&flag) {
					y1 = i;
					x1 = j;
					flag = 0;
				}
				else if (map[i][j] == 'o'&&flag == 0) {
					y2 = i;
					x2 = j;
				}
			}
		}
		q.push({ y1,x1,y2,x2 });
		while (!q.empty()) {
			Data c = q.front(); q.pop(); 
				int cnt = 0;
			if (c.cnt == 11) {
				return;
			}
			if (safe(c.y1, c.x1, 1)) {// 사라진것 확인
				cnt++;
			}
			if (safe(c.y2, c.x2, 2)) {
				cnt++;
			}
			if (cnt == 1) {
				ret = c.cnt;
				return;
			}
			if (cnt == 2) {
				continue;
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y1 = c.y1 + dy[dir]; n.x1 = c.x1 + dx[dir];
				n.y2 = c.y2 + dy[dir]; n.x2 = c.x2 + dx[dir];
				n.cnt = c.cnt + 1;
				int flag1 = 0;
				int flag2 = 0;
				if (safe(n.y1,n.x1)&&map[n.y1][n.x1] == '.' || map[n.y1][n.x1] == 'o') {
					flag1 = 1;
			
				}
				else {
					if (safe(n.y1, n.x1, 1)) {
						
					}
					else {
						n.y1 = c.y1;
						n.x1 = c.x1;
					}
				}
				if (safe(n.y2,n.x2)&&map[n.y2][n.x2] == '.' || map[n.y2][n.x2] == 'o') {
					flag2 = 1;
				}
				else {
					if (safe(n.y2, n.x2, 2)) {

					}
					else {
						n.y2 = c.y2;
						n.x2 = c.x2;
					}
				}
				if (visit[n.y1][n.x1][n.y2][n.x2] == 0) {
					visit[n.y1][n.x1][n.y2][n.x2] = 1;
					q.push(n);
				}
				
			}
		}
	}
}C;
int main(void) {
	C.bfs();
	if (ret == 0x7fffffff)ret = -1;

	printf("%d\n", ret);
 	return 0;
}