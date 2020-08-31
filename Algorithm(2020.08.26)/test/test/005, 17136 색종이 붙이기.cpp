#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define N_SIZE 11
int board[N_SIZE][N_SIZE];//10 * 10 배열
int ret = 0x7fffffff;//최소값
int paper[6] = { 0,5,5,5,5,5 };//종이의 갯수 체크 위한 배열
bool safe(int y, int x) {//배열 범위 체크
	return 0 <= y && y < 10 && 0<=x&& x < 10;
}
int init() {//초기화 작업
	ret = 0x7fffffff;
	memset(board, 0, sizeof(board));//입력 배열 0으로 초기화
	int zeroCnt = 0;
	for (int y = 0; y < 10; y++) {//맵 입력
		for (int x = 0; x < 10; x++) {
			scanf("%d", &board[y][x]);
			if (board[y][x] == 0)zeroCnt++;
		}
	}
	if (zeroCnt == 100)return 0;//모든 값이 0이면 0출력하기 위함
	return 1;//아니면 조건문 동작시키기 위함
}
void copy(int cboard[N_SIZE][N_SIZE], int board[N_SIZE][N_SIZE]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cboard[i][j] = board[i][j];
		}
	}
}
bool chk(int cy, int cx, int size) {
		for (int y = cy; y < cy + size; y++) {
			for (int x = cx; x < cx + size; x++) {
				if (safe(y, x)) {
					if(board[y][x] == 0)return false;
				}
				else return false;
			}
		}
		return true;
}
void copypaint(int y, int x, int idx, int num) {
	for (int i = y; i < y + idx; i++) {
		for (int j = x; j < x + idx; j++) {
			board[i][j] = num;
		}
	}
}
void dfs(int cnt) {
	if (cnt > ret)return;
	int flag = 0;//초기화 변수
	int cy = -1, cx = -1;
		for (int y = 0; y < 10; y++) {//좌표 찾기
			for (int x = 0; x < 10; x++) {
				if (board[y][x] == 1) {
					cy = y; cx = x;//1의 위치 y,x 좌표 
					flag = 1;//1의 위치 선정 표시
					break;
				}
			}
			if (flag)break;
	   }

	if (flag==0) {//전부 덮힌 상태
		ret = ret > cnt ? cnt : ret;//최소값 저장
		return;
	}
	int cboard[N_SIZE][N_SIZE] = { 0, };//카피할 배열
	for (int i = 1; i <= 5; i++) {
		if (paper[i] == 0)continue;
		if (chk(cy,cx,i)) {
			copypaint(cy, cx, i, 0);
			paper[i]--;//종이 사용
			dfs(cnt + 1);//사용할 종이크기, 갯수
			paper[i]++;//종이 복구
			copypaint(cy, cx, i, 1);
		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		if (init()) {
			dfs(0);
		}
		else {//0으로 바로 출력시
			ret = 0;
		}
		if (ret == 0x7fffffff)ret = -1;
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}

	return 0;
}