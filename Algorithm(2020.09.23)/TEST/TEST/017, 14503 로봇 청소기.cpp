#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NMSIZE 50 //세로와 가로의 최대 크기
int N, M;//세로크기, 가로크기
int ret;//최종값 결과값
int rY, rX, rDir;//로봇의 현재 위치와 방향
int square[NMSIZE][NMSIZE];//초기 입력배열
int dy[] = { -1,0,1,0 };//북, 동 ,남, 서
int dx[] = { 0,1,0,-1 };
void init_input() {//초기화 및 초기 입력
	//초기화 
	ret = 1;//벽이 1이기 때문에 구분하기 위해서
	N = M = 0;
	rY = rX = rDir = 0;
	memset(square, 0, sizeof(square));
	//초기 입력
	scanf("%d %d", &N, &M);//가로 세로 크기 입력
	scanf("%d %d %d", &rY, &rX, &rDir);//로봇의 현재 좌표와 방향
	for (int y = 0; y < N; y++) {//초기 입력값 배열 저장
		for (int x = 0; x < M; x++) {
			scanf("%d", &square[y][x]);
		}
	}
}
void cleanRoom() {
	//0은 빈칸 1은 벽 2이상은 청소한구역 
	while (1) {
		//현재 위치를 청소한다.
		if (square[rY][rX] == 0) {
			square[rY][rX] = ++ret;
		}
		//현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
		int num = 0;
		int dir = rDir;
		for (num = 0; num < 4; num++) {//네방향 검사
			dir=(4+(--dir))%4;
			int ny = rY + dy[dir]; int nx = rX + dx[dir];//왼쪽 방향 검사
			//왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
			if (square[ny][nx] == 0) {
				rY = ny; rX = nx;//한칸 이동 시키고
				rDir = dir;//방향 맞춰주고
				break;
			}
			//왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
			
		}
		if (num == 4) {//네방향 모두 청소가 되어있는 경우
			//네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
			int ny = rY - dy[rDir]; int nx = rX - dx[rDir];//뒤방향 
			if (square[ny][nx] !=1) {//빈공간이라면
				rY = ny; rX = nx;//이동한걸로 최신화
			}
			//네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
			else if (square[ny][nx] != 0) {//벽인경우나 청소한 공간이라면
				return;//청소 종료
			}
		}
	}
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//초기화 및 초기 입력
		init_input();
		cleanRoom();//로봇 청소기 청소 시작
		//결과값 출력
		printf("%d\n", ret-1);
		//printf("#%d %d\n", tc, ret-1);
	}
	return 0;
}