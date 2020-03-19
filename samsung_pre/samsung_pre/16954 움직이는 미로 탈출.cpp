#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
#define S 9
char chessMap[S][S];
int V[S][S];
int dy[] = { -1,-1,-1,0,1,1,1,0,0 };
int dx[] = { -1,0,1,1,1,0,-1,-1,0 };
int ret;
struct Data {
	int y, x,cnt;
};
struct chessExit {
	chessExit() {
		for (int i = 0; i < 8; i++)
			scanf("%s", chessMap[i]);
		playExit();
		if (ret) cout << 1 << endl;
		else cout << 0 << endl;
	}
	void init() {
		ret = 0;
		memset(chessMap, 0, sizeof(chessMap));
		memset(V, 0, sizeof(V));
	}
	void playExit() {
		int c1 = 0;
		queue<Data>q;
		q.push({ 7,0 });
		int flag = 0;
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			if (c1 != c.cnt) {
				c1++;
				moveMap();
				memset(V, 0, sizeof(V));
			}
			if (c.y == 0 && c.x == 7) {
				ret = 1;
				return;
			}
			for (int dir = 0; dir < 9; dir++) {
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (chessMap[c.y][c.x] == '.'&&chessMap[n.y][n.x] == '.'&&safe(n.y, n.x) && V[n.y][n.x] == 0) {
					V[n.y][n.x] = 1;
					q.push(n);
				}
			}
		
		}
	}
	void moveMap() {
		for (int i = 6; i >=0; i--) {
			for (int j = 0; j < 8; j++) {
				chessMap[i+1][j] = chessMap[i][j];
			}
		}
		for (int j = 0; j < 8; j++) {
			chessMap[0][j] = '.';
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < 8 && 0 <= x & x < 8;
	}
}chessExit;
int main(void) {
	return 0;
}