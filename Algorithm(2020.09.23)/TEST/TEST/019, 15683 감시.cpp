#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define NMS 8//세로와 가로의 최대 크기
int N, M;//사무실의 세로와 가로 크기
int ret;//결과값 
int room[NMS][NMS];//사무실 정보
struct Data {
	int y, x, num;
}cctv[65];//전체가 cctv인 걸 고려하여 최대 64개
int cctvIdx;
int dy[] = { 0,1,0,-1 };//cctv 방향 선정
int dx[] = { 1,0,-1,0 };
int cctvCnt[6] = { 0,4,2,4,4,1 };//cctv넘버 별 방향 개수
void copy(int cr[NMS][NMS], int r[NMS][NMS]) {//배열 복사 함수
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cr[i][j] = r[i][j];
		}
	}
}
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M =cctvIdx= 0;
	ret = 0x7fffffff;//최소값
	memset(room, 0, sizeof(room));
	//초기 입력
	scanf("%d %d", &N, &M);//가로 세로 크기 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &room[i][j]);//초기 입력
			if (room[i][j] != 6 && room[i][j] != 0) {//cctv정보 찾기
				cctv[cctvIdx].y = i; cctv[cctvIdx].x = j; cctv[cctvIdx].num = room[i][j];
				//cctv의 좌표값과 번호
				cctvIdx++;
			}
		}
	}
}
bool isafe(int y, int x) {
	return y < 0 || y == N || x < 0 || x == M;
}
void paint(Data c, int dir) {//범위 칠하기
	dir = dir % 4;
	while (1) {
		Data n;
		n.y = c.y + dy[dir]; n.x = c.x + dx[dir];//다음 방향
		if (isafe(n.y, n.x) || room[n.y][n.x] == 6)break;
		room[n.y][n.x] = 9;//cctv 경로 입력
		c.y = n.y; c.x = n.x;
	}
}
int zeroCnt() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (room[i][j] == 0)cnt++;
		}
	}
	return cnt;
}
void dfs(int idx, int cnt) {
	if (cnt == cctvIdx) {
		ret=min(ret,zeroCnt());//최소값 산출
		return;
	}
	for (int i = idx; i < cctvIdx; i++) {
		int cctvNumber = cctv[i].num;//cctv 넘버
		int croom[NMS][NMS] = { 0, };//복사본
		for (int dir = 0; dir < cctvCnt[cctvNumber]; dir++) {//cctv 방향
			copy(croom, room);
			//페인트 칠하기
			if (cctvNumber == 1) {
				paint(cctv[i], dir);
			}
			else if (cctvNumber == 2) {
				paint(cctv[i], dir);
				paint(cctv[i], dir+2);
			}
			else if (cctvNumber == 3) {
				paint(cctv[i], dir);
				paint(cctv[i], dir + 1);

			}
			else if (cctvNumber == 4) {
				paint(cctv[i], dir);
				paint(cctv[i], dir + 1);
				paint(cctv[i], dir + 2);
			}
			else if (cctvNumber == 5) {
				paint(cctv[i], dir);
				paint(cctv[i], dir + 1);
				paint(cctv[i], dir + 2);
				paint(cctv[i], dir + 3);
			}
			dfs(i+1, cnt + 1);
			copy(room, croom);
		}
	}
}
int main(void) {
	int T = 1;//테스트 케이스 개수
//	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		dfs(0, 0);
		//출력
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);

	}
	return 0;
}