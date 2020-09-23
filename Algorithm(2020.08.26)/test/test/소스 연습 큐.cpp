#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define NSIZE 50
int N;
int arr[NSIZE][NSIZE];
void init() {
	scanf("%d", &N);
	//배열 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
void BFS() {
	struct Data {
		int y, x, num;
	};
	int dy[] = { 0,1,0,-1 };
	int dx[] = { 1,0,-1,0 };
	queue<Data>q;
	int visit[NSIZE][NSIZE] = { 0, };
	q.push({ 0,0,arr[0][0] });
	arr[0][0] = 0;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		for (int dir = 0; dir < 4; dir++) {
			for (int i = 1; i < c.num; i++) {
				Data n;
				n.y = c.y + (dy[dir] * i);
				n.x = c.x + (dx[dir] * i);
				n.num = arr[n.y][n.x];
				if (visit[n.y][n.x] == 0 && safe(n.y, n.x) && arr[n.y][n.x] != 0) {
					visit[n.y][n.x] = 1;
					arr[n.y][n.x] = 0;
					q.push(n);
				}
			}
		}
	}
	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%2d", arr[i][j]);
		}
		printf("\n");
	}

}
int main(void) {
	init();
	BFS();
	return 0;
}