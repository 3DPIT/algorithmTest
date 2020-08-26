#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define MAP_SIZE 51
int N, M;//행 열
int map[MAP_SIZE][MAP_SIZE];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int y, x, dir;
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void init() {
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &y, &x, &dir);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
void play() {
	int clean_room = 1;
	while (1) {// 무한 반복
		if (map[y][x] == 0) {//현재 위치를 청소한다.
			map[y][x] = ++clean_room;
		}
		//현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
		int i = 0;
		int cdir = dir;
		for (i = 0; i < 4; i++) {
			cdir--;
			if (cdir == -1)cdir = 3;
			if (safe(y + dy[cdir], x + dx[cdir]));
			//왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
			if (map[y + dy[cdir]][x + dx[cdir]]==0) {
				y = y + dy[cdir]; x = x + dx[cdir];
				dir = cdir;
				break;
			}
		}
		//왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
		if (i == 4) {
			//네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
			if (map[y - dy[dir]][x - dx[dir]] !=1) {
				y -= dy[dir]; x -= dx[dir];
			}
			else {
				break;
			}
			//네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
		}
		//로봇 청소기는 이미 청소되어있는 칸을 또 청소하지 않으며, 벽을 통과할 수 없다.
	}
	cout << clean_room - 1<endl;
}
int main(void) {
	init();
	play();
	return 0;
}


