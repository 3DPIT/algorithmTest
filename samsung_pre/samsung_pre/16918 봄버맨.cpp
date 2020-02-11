#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define S 201
int N, M, T,Time;
char map[S][S];
int imap[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Bomb {
	struct Data {
		int y, x;
	};
	queue<Data>q;
	Bomb() {
		scanf("%d %d %d", &N, &M, &T);
		T--;
		for (int i = 0; i < N; i++) {
			scanf("%s", map[i]);
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 'O') {
					imap[i][j] = 3;
				}
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
	void bombAdd() {
		while (!q.empty())q.pop();
		T--;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (imap[i][j]==0) {
					imap[i][j] = 4;
				}
				else imap[i][j]--;
			}
		}
	}
	void bombFinish() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				imap[i][j]--;
				if (imap[i][j] == 1)q.push({ i,j });
			}
		}
		T--;
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			imap[c.y][c.x] = 0;
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				if (safe(n.y,n.x)){
					imap[n.y][n.x] = 0;
				}
			}
		}
	}
	void simulate() {
		while (T) {
			bombAdd();
			if (T == 0)break;
			bombFinish();
			if (T == 0)break;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (imap[i][j] != 0) {
					printf("O");
				}
				else printf(".");
			}
			printf("\n");
		}
	}
}Game;
int main(void) {
	Game.simulate();
	return 0;
}