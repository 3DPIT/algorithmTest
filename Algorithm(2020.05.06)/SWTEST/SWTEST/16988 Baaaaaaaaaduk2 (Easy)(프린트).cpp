#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define S 21
int ret = 0x80000000;
int N, M;
int board[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x;
};

vector<Data>vv;
vector<Data>a;
void print(string name, int idx,int board[S][S]) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout<<"  "<< board[i][j];
			}
			cout << endl;
		}
	}
	if (idx == 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << "  " << board[i][j];
			}
			cout << endl;
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
int c = 0;
void simul() {
	c = 0;
	int chk[S][S] = { 0, };
	int sum = 0;
	int flag = 0;
	for (int i = 0; i < a.size(); i++) {
		flag = 0;
		int cnt = 0;
		if (chk[a[i].y][a[i].x] == 0) {
			cnt = 0;
			queue<Data>q;
			chk[a[i].y][a[i].x] = 1;
			cnt++;
			q.push({ a[i].y ,a[i].x });
			while (!q.empty()) {
				Data c = q.front(); q.pop();
				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir];
					n.x = c.x + dx[dir];
					if (safe(n.y, n.x)) {
						if (board[n.y][n.x] == 0) {
							flag = 1;
						}
						if (board[n.y][n.x] == 2 && chk[n.y][n.x] == 0) {
							chk[n.y][n.x] = 1;
							cnt++;
							q.push(n);
						}
					}

				}
			}
		}
		if (flag != 1) {
			flag = 0;
			c += cnt;
		}
	}
}
int visit[S*S];
vector<int>aa;
void dfs(int idx,int d) {
	if (d == 2) {
		//print("╦й ╩Себ", 0,board);
		//for (int i = 0; i < aa.size(); i++) {
		//	cout << aa[i] << "  ";
		//}
		//cout << endl;
	 simul();
		if(c!=0)
		ret = ret < c ? c : ret;
		return;
	}
	for (int i = idx; i < vv.size(); i++) {
		aa.push_back(i);
			board[vv[i].y][vv[i].x] = 1;
			dfs(i+1, d + 1);
			board[vv[i].y][vv[i].x] = 0;
			aa.pop_back();
	}
}
void init() {
	ret = 0x80000000;
	memset(board, 0, sizeof(board));
	N = M;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j] == 2) {
				a.push_back({ i, j });

			}
		}
	}
	int chk1[S][S] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 2) {
				for (int dir = 0; dir < 4; dir++) {
					int ny = i + dy[dir];
					int nx = j + dx[dir];
					if (safe(ny, nx) && board[ny][nx] == 0&&chk1[ny][nx]==0) {
						chk1[ny][nx] = 1;
						vv.push_back({ ny,nx });
					}
				}

			}
		}
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
init();
	dfs(0, 0);
	if (ret == 0x80000000)ret = 0;
	printf("%d", ret);
	return 0;
}