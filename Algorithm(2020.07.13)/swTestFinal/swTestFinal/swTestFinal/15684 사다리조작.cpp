#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
using namespace std;
#define N_SIZE 11
#define H_SIZE 31
int N, M, H;//세로선, 놓여진 가로선, 가로선
int rail[H_SIZE][N_SIZE];//사다리 놓는 배열
int ret=0x7fffffff;//최종값

void init() {
	memset(rail, 0, sizeof(rail));
	N = M = H = 0;
	ret =0x7fffffff;
	scanf("%d %d %d", &N, &M, &H);
	for (int mi = 0; mi < M; mi++) {
		int y, x;
		scanf("%d %d", &y, &x);
		rail[y][x] = 1;// 가로선 미리 설정
	}
}
bool chkRail() {
	for (int i = 1; i <= N; i++) {//사다리 타기 시작
		int y = 0, x = i;
		while (1) {
			if (y == H + 1)break;
			if (rail[y + 1][x] == 1) {//오른쪽으로
				y++; x++;
			}
			else if (rail[y + 1][x - 1] == 1) {//왼쪽으로
				y++; x--;
			}
			else {
				y++;
			}
		}
		if (i != x) return false;
	}
	return true;//성공한 경우 
}
void dfs(int y, int x, int cnt) {
	if (ret < cnt)return;
	if(0<=cnt&&cnt<=3) {// 일단 검사 시작
		if (chkRail()) {
			ret = ret > cnt ? cnt : ret;
		}
		if (cnt == 3) return;
	}
	for (int i = y; i <= H; i++) {// 주어진 범위
		for (int j = x; j <= N; j++) {
			if (rail[i][j] == 0&&rail[i][j-1]==0&&rail[i][j+1]==0) {
				// 현재 양옆에 다리가 없고 비어있는 경우에 다리 놓기
				rail[i][j] = 1;
				cnt++;
				dfs(i, j+1,cnt);
				cnt--;
				rail[i][j] = 0;
			}
		}
		x = 1;
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(1,1,0);// 각각 다리를 놓아 보기
		if (ret == 0x7fffffff)ret = -1;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}