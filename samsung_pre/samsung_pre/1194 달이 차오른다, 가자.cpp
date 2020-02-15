#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
#define S 51
int N, M;
int v[S][S];
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
	queue<Data>q1;
	Moon() {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf("%s", &map[i]);
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == '0') {
					q.push({ i,j,0,0 });
					v[i][j] = 1;
				}
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y & y < N && 0 <= x && x < M;
	}
	void miro() {
		while (q.size()!=0) {
			while (!q.empty()) {
				Data c = q.front(); q.pop();
				if (map[c.y][c.x] == '1') {
					if (Min > c.cnt)Min = c.cnt;
				}
				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.cnt = c.cnt + 1; n.key = c.key;
					if (map[n.y][n.x] != '#'&&safe(n.y,n.x)) {// 이동가능한 위치에서
						if (map[n.y][n.x] == '.' || map[n.y][n.x] == '0' || map[n.y][n.x] == '1'&&v[n.y][n.x]!=n.cnt) {
							v[n.y][n.x] = n.cnt;
							q.push(n);
						}
						else if ('A' <= map[n.y][n.x] && map[n.y][n.x] <= 'F') {//문이면
							if (n.key&map[n.y][n.x]&&v[n.y][n.x]!=n.cnt) {
								v[n.y][n.x] = n.cnt;
								q.push(n);
							}
						}
						else if ('a' <= map[n.y][n.x] && map[n.y][n.x] <= 'f'&&v[n.y][n.x]!=n.cnt) {//열쇠면
							v[n.y][n.x] = n.cnt;
							n.key |= map[n.y][n.x];
							q1.push(n);
						}
					}
				}
			}
			while (!q1.empty()) {// 현재 열쇠 위치 다시 넣기
				Data c = q.front(); q1.pop();
				q.push(c);
			}
			memset(v, 0, sizeof(v));
		}
	}
}FullMoon;
int main(void) {
	FullMoon.miro();
	if (Min = 0x7fffffff)Min = -1;
	cout << Min << endl;
	return 0;
}