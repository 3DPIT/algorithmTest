#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
using namespace std;
#define S 51
int N, M;
int ret = 0x7fffffff;
int cnt = 0;
char map[S][S];
int visit[S][S][5];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, key, cnt;
};
vector<Data>v;
vector<int>D;
int num[S];
int sy;
int sx;
int ey;
int ex;
struct Umbrella {
	Umbrella() {
		scanf("%d %d", &M, &N);
		int num = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf(" %1c", &map[i][j]);
				if (map[i][j] == 'X') {
					//map[i][j] = (num++) + '0';
					v.push_back({ i,j });
				}
				if (map[i][j] == 'S') {
					sy = i;
					sx = j;
				}
				if (map[i][j] == 'E') {
					ey = i;
					ex = j;
				}

			}
		}//

		bfs();
		printf("%d\n", ret);
	}
	void bfs() {
		queue<Data>q;
		q.push({ sy,sx,0,0 });
		visit[sy][sx][0]=1;
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			if (map[c.y][c.x]=='E'&&c.key == v.size()) {
				//break;
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				n.key = c.key;
				
				if (safe(n.y,n.x)&&map[n.y][n.x] != '#'&&visit[n.y][n.x][n.key] == 0) {
					visit[n.y][n.x][n.key] = n.cnt;
					if (map[n.y][n.x] == 'X'){
						n.key++;
						q.push(n);
					}
					else {
						q.push(n);
					}
				}

			}
		}
	}
	void init() {
		memset(map, 0, sizeof(map));
		N = M = 0;
		memset(num, 0, sizeof(num));
	}
	bool chk() {
		int y = sy;
		int x = sx;
		char C;
		queue<Data>q;
		int ccnt = 0;
		int flag = 0;
		for (int i = 0; i <= D.size(); i++) {
			if (i == D.size())C = 'E';
			else C = map[v[D[i]].y][v[D[i]].x];
			while (!q.empty())q.pop();
			q.push({ y,x,0 });
			int visit[S][S] = { 0, };
			visit[y][x] = 1;
			while (!q.empty()) {
				Data c = q.front(); q.pop();
				if (map[c.y][c.x] == C) {
					++flag;
					y = c.y;
					x = c.x;
					ccnt += c.cnt;
					break;
				}
				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir];
					n.x = c.x + dx[dir];
					n.cnt = c.cnt + 1;
					if (safe(n.y, n.x) && map[n.y][n.x] != '#'&&visit[n.y][n.x] == 0) {
						visit[n.y][n.x] = 1;
						q.push(n);
					}
				}

			}//	
		}


		if (flag == D.size() + 1) {
			cnt = ccnt;
			return true;// 다가지고 나갔으면
		}
		else false;
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}


}Umbrella;
int main(void) {
	return 0;
}


//
//#include<stdio.h>
//#include<iostream>
//#include<queue>
//#include<vector>
//#include<string.h>
//using namespace std;
//#define S 51
//int N, M;
//int ret = 0x7fffffff;
//int cnt = 0;
//char map[S][S];
//int dy[] = { 0,1,0,-1 };
//int dx[] = { 1,0,-1,0 };
//struct Data {
//	int y, x, cnt;
//};
//vector<Data>v;
//vector<int>D;
//int num[S];
//int sy;
//int sx;
//int ey;
//int ex;
//struct Umbrella {
//	Umbrella() {
//		scanf("%d %d", &M, &N);
//		int num = 0;
//		for (int i = 0; i < N; i++) {
//			for (int j = 0; j < M; j++) {
//				scanf(" %1c", &map[i][j]);
//				if (map[i][j] == 'X') {
//					map[i][j] = (num++) + '0';
//					v.push_back({ i,j });
//				}
//				if (map[i][j] == 'S') {
//					sy = i;
//					sx = j;
//				}
//				if (map[i][j] == 'E') {
//					ey = i;
//					ex = j;
//				}
//
//			}
//		}//
//		dfs(0, 0);
//		printf("%d\n", ret);
//	}
//	void init() {
//		memset(map, 0, sizeof(map));
//		N = M = 0;
//		memset(num, 0, sizeof(num));
//	}
//	bool chk() {
//		int y = sy;
//		int x = sx;
//		char C;
//		queue<Data>q;
//		int ccnt = 0;
//		int flag = 0;
//		for (int i = 0; i <= D.size(); i++) {
//			if (i == D.size())C = 'E';
//			else C = map[v[D[i]].y][v[D[i]].x];
//			while (!q.empty())q.pop();
//			q.push({ y,x,0 });
//			int visit[S][S] = { 0, };
//			visit[y][x] = 1;
//			while (!q.empty()) {
//				Data c = q.front(); q.pop();
//				if (map[c.y][c.x] == C) {
//					++flag;
//					y = c.y;
//					x = c.x;
//					ccnt += c.cnt;
//					break;
//				}
//				for (int dir = 0; dir < 4; dir++) {
//					Data n;
//					n.y = c.y + dy[dir];
//					n.x = c.x + dx[dir];
//					n.cnt = c.cnt + 1;
//					if (safe(n.y, n.x) && map[n.y][n.x] != '#'&&visit[n.y][n.x] == 0) {
//						visit[n.y][n.x] = 1;
//						q.push(n);
//					}
//				}
//
//			}//	
//		}
//
//
//		if (flag == D.size() + 1) {
//			cnt = ccnt;
//			return true;// 다가지고 나갔으면
//		}
//		else false;
//	}
//	bool safe(int y, int x) {
//		return 0 <= y && y < N && 0 <= x && x < M;
//	}
//	void dfs(int idx, int d) {
//		if (idx == v.size()) {
//			cnt = 0;
//			if (chk()) {
//				ret = ret > cnt ? cnt : ret;
//			}
//			return;
//		}
//		for (int i = 0; i < v.size(); i++) {
//			if (num[i] == 0) {
//				num[i] = 1;
//				D.push_back(i);
//				dfs(idx + 1, d);
//				D.pop_back();
//				num[i] = 0;
//			}
//		}
//	}
//
//}Umbrella;
//int main(void) {
//	return 0;
//}
