#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
#define S 51
int N, M;
int v[S][S][64];
char map[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int Min = 0x7fffffff;
struct Data {
	int y, x, cnt, key;
};
struct Moon {
public:
	queue<Data>q;
	Moon() {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf("%s", &map[i]);
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == '0') {
					q.push({ i,j,0,0 });
					v[i][j][0] = 1;
				}
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
	void miro() {
		while (q.size() != 0) {
			while (!q.empty()) {
				Data c = q.front(); q.pop();
				if (map[c.y][c.x] == '1') {
					Min = c.cnt;
					return;
				}
				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.cnt = c.cnt + 1; n.key = c.key;
					if (safe(n.y, n.x) && v[n.y][n.x][n.key] == 0) {// 이동가능한 위치에서
						v[n.y][n.x][n.key] = 1;
						if (map[n.y][n.x] != '#') {
							if ('A' <= map[n.y][n.x] && map[n.y][n.x] <= 'F') {//문이면
								if (n.key & 1 << map[n.y][n.x] - 'A') {
									q.push(n);
								}
							}
							else if ('a' <= map[n.y][n.x] && map[n.y][n.x] <= 'f') {//열쇠면
								n.key = n.key | 1 << map[n.y][n.x] - 'a';
								q.push(n);
							}
							else {
								q.push(n);
							}
						}
					}
				}
			}
		}
	}
}FullMoon;
int main(void) {
	FullMoon.miro();
	if (Min == 0x7fffffff)Min = -1;
	cout << Min << endl;
	return 0;
}