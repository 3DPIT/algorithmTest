#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define NS 11
char map[NS][NS];
int chk[NS][NS][NS][NS];
int ret;
int N, M;
int hy, hx,ry,rx,by,bx;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int ry, rx, by, bx, cnt;
};
void init() {
	memset(map, 0, sizeof(map));
	memset(chk, 0, sizeof(chk));
	N = M = hy=hx=ry=rx=by=bx=0;
	ret = -1;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &map[i][j]);
			if (map[i][j] == 'O') {
				hy = i; hx = j;
				map[i][j] = '.';
			}
			if (map[i][j] == 'R') {
				ry = i; rx = j;
				map[i][j] = '.';
			}
			if (map[i][j] == 'B') {
				by = i; bx = j;
				map[i][j] = '.';
			}
		}
	}
}

void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (ry == i && rx == j) {
					cout << "R";
				}
				else if (by == i && bx == j) {
					cout << "B";
				}
				else
				cout << map[i][j];
			}
			cout << endl;
		}
	}
}
void BFS() {
	queue<Data>q;
	q.push({ ry,rx,by,bx,0 });
	chk[ry][rx][by][bx] = 1;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.ry == hy && c.rx == hx) {
			ret = c.cnt;
			break;
		}
		for (int dir = 0; dir < 4; dir++) {
			Data n=c;
			n.cnt = c.cnt + 1;
			bool hr=false, hb=false;
			ry = c.ry; rx = c.rx;
			by = c.by; bx = c.bx;

			while (1) {
				n.ry = ry + dy[dir];
				n.rx = rx + dx[dir];
				if (n.ry == hy && n.rx == hx) {
					hr = true;
					break;
				}
				if (map[n.ry][n.rx] == '#') {
					n.ry = n.ry- dy[dir];
					n.rx = n.rx - dx[dir];
					break;
				}
				ry = n.ry;
				rx = n.rx;
			}
			while (1) {
				n.by = by + dy[dir];
				n.bx = bx + dx[dir];
				if (n.by == hy && n.bx == hx) {
					hb = true;
					break;
				}
				if (map[n.by][n.bx] == '#') {
					n.by = n.by - dy[dir];
					n.bx = n.bx - dx[dir];
					break;
				}
				by = n.by;
				bx = n.bx;
			}
			if ((hr&&hb)||(!hr&&hb))continue;//µÎ°³´Ù È¦ÀÌ°Å³ª ÆÄ¶û¸¸ È¦
			else {
				if (n.ry == n.by&&n.rx == n.bx) {//°°Àº À§Ä¡¿¡ ÀÖ´Â°æ¿ì
					int dr = abs(n.ry - c.ry) + abs(n.rx - c.rx);
					int db = abs(n.by - c.by) + abs(n.bx - c.bx);
					if (dr < db)//»¡°­ÀÌ ¸ÕÀú¿È
						{
						n.by = n.by - dy[dir];
						n.bx = n.bx - dx[dir];

						}
					else {
						n.ry = n.ry - dy[dir];
						n.rx = n.rx - dx[dir];
						}
					}
				ry = n.ry; rx = n.rx; by = n.by; bx = n.bx;
				print("¸ÊÀÇ »óÅÂ", 0);
					if (chk[n.ry][n.rx][n.by][n.bx] == 0) {
						chk[n.ry][n.rx][n.by][n.bx] = 1;
						q.push(n);
					}
			}
		}
	}
}

int main(void) {
	int T=1;
	//scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		BFS();
		//printf("#%d %d\n", t, ret);
		printf("%d\n", ret);

	}
	return 0;
}