#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAP_SIZE 17
int N;//집의 크기
int map[MAP_SIZE][MAP_SIZE];
int ret;// 방법의 수 ;N,N까지 도달하는 방법
int dy[] = { 0,1,1 };//가로, 세로, 대각선
int dx[] = { 1,0,1};
bool safe(int y, int x) {
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void dfs(int y, int x,int dir) {
	if (y == N && x == N) {
		ret++;
		return;
	}
	for (int i = 0; i < 3; i++) {
		int ny = y + dy[i]; int nx = x + dx[i];
		if (i == 0&&dir!=1) {// 가로
			if (safe(ny, nx)&&map[ny][nx]==0) {
				dfs(ny, nx, i);
			}
		}
		else if (i == 1&&dir!=0) {//세로
			if (safe(ny, nx) && map[ny][nx] == 0) {
				dfs(ny, nx, i);
			}
		}
		else if(i==2) {//대각석
			if (safe(ny, nx) && map[ny][nx] == 0&&map[y+dy[0]][x+dx[0]]==0&&map[y+dy[1]][x+dx[1]]==0) {
				dfs(ny, nx, i);
			}
		}		
	}

}
void init() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	dfs(1, 2,0);//출발 y,x값 N,N에 도달하는 방법수 출력
	cout << ret;
}
int main(void)
{
	init();
	return 0;
}
