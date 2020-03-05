#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
using namespace std;
#define S 51
int input[S][S];
int visit[S][S];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int ret;
int N, M, L, y, x;
struct Data {
	int y, x, cnt;
};
struct ExitHoll {
	ExitHoll() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			scanf("%d %d %d %d %d", &N, &M, &y, &x, &L);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					scanf("%d", &input[i][j]);
				}
			}
			search();
			if(ret==0)				chkOne();
			printf("#%d %d\n", t, ret);
		}
	}
	void chkOne() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visit[i][j] == 1)ret++;
			}
		}
	}
	void search() {
		queue<Data>q;
		q.push({ y,x,1 });
		visit[y][x] = 1;
		while (!q.empty()) {
			Data c = q.front(); q.pop();

			if (c.cnt == L) {
				chkOne();
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x)) {
					if (input[c.y][c.x] == 1 && visit[n.y][n.x] == 0) {
						if (dir == 0) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 5 || input[n.y][n.x] == 6) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
						if (dir == 1) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 6 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
						if (dir == 2) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 4 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
						if (dir == 3) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 4 || input[n.y][n.x] == 5) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
					}

					if (input[c.y][c.x] == 2 && visit[n.y][n.x] == 0) {
						if (dir == 0) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 5 || input[n.y][n.x] == 6) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}

						if (dir == 2) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 4 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}

					}

					if (input[c.y][c.x] == 3 && visit[n.y][n.x] == 0) {

						if (dir == 1) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 6 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
									q.push(n);
							}
						}
						if (dir == 3) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 4 || input[n.y][n.x] == 5) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}

					}

					if (input[c.y][c.x] == 4 && visit[n.y][n.x] == 0) {
						if (dir == 0) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 ||  input[n.y][n.x] == 5 || input[n.y][n.x] == 6) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
						if (dir == 1) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 6 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}

					}

					if (input[c.y][c.x] == 5 && visit[n.y][n.x] == 0) {

						if (dir == 1) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 6 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
						if (dir == 2) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 4 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}

					}

					if (input[c.y][c.x] == 6 && visit[n.y][n.x] == 0) {

						if (dir == 2) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 4 || input[n.y][n.x] == 7) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
						if (dir == 3) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 4 || input[n.y][n.x] == 5) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
					}

					if (input[c.y][c.x] == 7 && visit[n.y][n.x] == 0) {
						if (dir == 0) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 2 || input[n.y][n.x] == 5 || input[n.y][n.x] == 6) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}


						if (dir == 3) {
							if (input[n.y][n.x] == 1 || input[n.y][n.x] == 3 || input[n.y][n.x] == 4 || input[n.y][n.x] == 5) {
								visit[n.y][n.x] = 1;
								q.push(n);
							}
						}
					}

				}
			}
		}
	}
	void init() {
		ret = 0;
		memset(input, 0, sizeof(input));
		memset(visit, 0, sizeof(visit));
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
}ExitHoll;
int main(void) {
	return 0;
}