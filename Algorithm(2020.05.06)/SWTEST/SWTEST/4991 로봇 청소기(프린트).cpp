#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
using namespace std;
#define S 21
int inp[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, M;
int visit1[S][S];
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs1(int y, int x, int cnt) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (safe(ny, nx) && inp[ny][nx] != 'x'&& visit1[ny][nx] == 0) {
			visit1[ny][nx] = cnt;
			dfs1(ny, nx, cnt);
		}
	}
}
struct Data {
	int y, x, cnt;
};

int main(void) {
	while (1) {
		scanf("%d %d", &M, &N);
		if (N == 0 && M == 0)break;
		int sy = 0, sx = 0;
		vector<Data>v;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf(" %1c", &inp[i][j]);
				if (inp[i][j] == 'o') {
					sy = i; sx = j;
				}
				if (inp[i][j] == '*') {
					v.push_back({ i,j,0 });
				}
			}
		}
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visit1[i][j] == 0) {
					visit1[i][j] = 1;
					cnt++;
					visit1[i][j] = cnt;
					dfs1(i, j, cnt)
						;
				}
			}
		}
		int chka = visit1[sy][sx];
		int flag1 = 0;
		for (int i = 0; i < v.size(); i++) {
			int y = v[i].y;
			int x = v[i].x;
			if (visit1[y][x] != chka) {
				flag1 = 1;
			}
		}
		memset(visit1, 0, sizeof(visit1));
		if (flag1) {
			cout << -1 << endl;
		}
		else {
			int c1 = 0;
			int sum = 0;
			vector<int>v1;
			while (1) {
				queue<Data>q;
				q.push({ sy,sx,0 });
				int visit[S][S] = { 0, };
				while (!q.empty()) {
					Data c = q.front(); q.pop();

					if (inp[c.y][c.x] == '*') {
						sy = c.y; sx = c.x;
						inp[c.y][c.x] = '.';
						v1.push_back(c.cnt);
						sum += c.cnt;
						c1++;
						break;
					}
					for (int dir = 0; dir < 4; dir++) {
						Data n;
						n.y = c.y + dy[dir];
						n.x = c.x + dx[dir];
						n.cnt = c.cnt + 1;
						if (safe(n.y, n.x) && inp[n.y][n.x] != 'x'&&visit[n.y][n.x] == 0) {
							visit[n.y][n.x] = 1;
							q.push(n);
						}
					}
				}
				if (c1 == v.size())break;
			}

			cout << sum << endl;
		}
	}
	return 0;
}