#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
#define S 100
int map[S][S];
int visit[S][S];
int N;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int Min = 0x7fffffff;
struct Data {
	int y, x,cnt;
};
typedef struct B{
	B() {// 초기 시작
		memset(visit, 0, sizeof(visit));
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		int cnt = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 1) {
					cnt++;
					map[i][j] = cnt;
					dfs(i, j, cnt);
				}
			}
		}
	}
	bool safe(int y, int x) {//범위 확인
		return 0 <= y && y < N && 0 <= x && x < N;
	}
	void dfs(int y, int x, int cnt) {//섬 번호 매기기
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = y + dy[dir]; n.x = x + dx[dir];
			if (safe(n.y, n.x) && map[n.y][n.x] == 1) {
				map[n.y][n.x] = cnt;
				dfs(n.y, n.x,cnt);
			}
		}
	}
	void bfs(int y, int x,int cnt) {
		queue<Data>q;
		memset(visit, 0, sizeof(visit));
		q.push({ y,x,cnt});
		visit[y][x] = 1;
		int num = map[y][x];
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			if (map[c.y][c.x] != 0 && map[c.y][c.x] != num) {
				if (Min > c.cnt)Min = c.cnt;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y,n.x)&&map[n.y][n.x] != num && visit[n.y][n.x] == 0) {
					visit[n.y][n.x] = 1;
					q.push(n);
				}
			}
		}
	}
	void searchIsland() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0) {
					bfs(i, j,0);
				}
			}
		}
	}
	void print() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d", map[i][j]);
			}
			printf("\n");
		}
	}
}B;
int main(void) {
	B brig;
	//brig.print();
	brig.searchIsland();
	printf("%d", Min-1);
	return 0;
}