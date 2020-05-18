#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define S 21
int N, M,sy,sx;
int ret = 0x7fffffff;
char input[S][S];
struct Data {
	int y, x, cnt;
};
vector<Data>garbage;
void init() {
	N = M=sy=sx=0;
	ret = 0x7fffffff;
	garbage.clear();
	memset(input, 0, sizeof(input));
}

void init_input() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &input[i][j]);
			if (input[i][j] == 'o') {//청소기 위치
				sy = i; sx = j;
				input[i][j] = '.';
			}
			if (input[i][j] == '*') {//쓰레기 위치
				garbage.push_back({ i,j });
				input[i][j] = '.';
			}
		}
	}
}
int G[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };

bool safe(int y, int x){
return 0 <= y && y < N && 0 <= x && x < M;
}
int BFS(){
	int cchk = 0;
	vector<Data>v;
	v.push_back({ sy, sx,0 });
	for (int i = 0; i < garbage.size(); i++) {
		v.push_back({garbage[i].y, garbage[i].x, 0});
	}
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = i + 1; j < v.size(); j++) {
		//	cout << i << j << endl;
			queue<Data>q;
			int visit[S][S] = { 0, };
			q.push(v[i]);
			cchk = 0;
			while (!q.empty()) {
				Data c = q.front(); q.pop();
				if (c.y == v[j].y&&c.x == v[j].x) {
					G[i][j] = G[j][i] = c.cnt;
					cchk = 1;
					break;
				}
				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir];
					n.x = c.x + dx[dir];
					n.cnt = c.cnt + 1;
					if (safe(n.y, n.x) &&input[n.y][n.x]=='.'&&visit[n.y][n.x]==0 ) {
						visit[n.y][n.x] = 1;
						q.push(n);

					}

				}

			}
			if (cchk == 0)return - 1;
		}
	}
	//for (int i = 0; i < v.size(); i++) {
	//	for (int j = 0; j < v.size(); j++) {
	//		cout << G[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	return 1;
}
int dfs_chk[S];
vector<int>d1;
void DFS(int idx, int d) {
	if (d == garbage.size()) {
		//for (int i = 0; i < d1.size()	; i++) {
		//	cout << d1[i] << " ";
		//}
		//cout << endl;
		int sum = 0;
		sum += G[0][d1[0]];
		for (int i = 0; i <d1.size()-1; i++) {
			sum += G[d1[i]][d1[i + 1]];
		}
		ret = ret > sum ? sum : ret;
		return;
	}
	for (int i = 1; i <= garbage.size(); i++) {
		if (dfs_chk[i] == 0) {
			dfs_chk[i] = 1;
			d1.push_back(i);
			DFS(i, d + 1);
			d1.pop_back();
			dfs_chk[i] = 0;
		}
	}

}
int main(void) {
	while (cin >> M>> N) {
		if (N == 0 && M == 0) break;
		init_input();
		if (BFS() == 1) {
			DFS(0, 0);
		}
		else {
			ret = -1;
		}
		cout << ret << endl;
		init();

	}

	return 0;
}