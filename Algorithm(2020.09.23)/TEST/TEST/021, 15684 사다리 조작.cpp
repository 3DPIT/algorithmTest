#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define NS 11//세로선의 최대 개수
#define HS 31//가로선의 최대 개수
int N, M, H;//세로선의 수, 그어져있는 가로선, 놓을수 잇는 가로선의 수
int ret;//결과값 입력
int ladder[HS][NS];//사다리 배열
void init_input() {//초기화 및 초기 입력
	//초기화 
	N = M = H = 0; ret = 0x7fffffff;
	memset(ladder, 0, sizeof(ladder));
	//초기 입력
	scanf("%d %d %d", &N, &M, &H);//초기 입력
	for (int m = 0; m < M; m++) {//가로선 그어 놓기
		int y, x;
		scanf("%d %d", &y, &x);
		ladder[y][x] = 1;// 가로서 긋기
	}
}
bool chkLadder() {//사다리 조작 맞는지 확인
	for (int x = 1; x <= N; x++) {
		int cx = x;
		for (int y = 1; y <= H; y++) {
			if (ladder[y][cx] == 1) {
				cx++;
			}
			else if (ladder[y][cx - 1] == 1) {
				cx--;
			}
		}
		if (x != cx)return false;//조건에 맞지 않는 경우
	}
	return true;//조건에 부합하는 경우 
}
void dfs(int y, int x, int cnt) {
	if (ret < cnt)return;
	else if(0<=cnt&&cnt<=3){//0인 시점부터 확인하기 
		if (chkLadder()) {
			ret = min(ret, cnt);
		}
		if (cnt == 3)return;
	}
	for (int i = y; i <= H; i++) {
		for (int j = x; j <= N; j++) {
			if (ladder[i][j] == 0 && ladder[i][j - 1] == 0 && ladder[i][j + 1] == 0) {
				//현재 위치가 그어져 있지 않고 양쪽도 선이 없는 경우
				ladder[i][j] = 1;//선 긋기
				dfs(i, j + 1, cnt + 1);
				ladder[i][j] = 0;//다시 돌아와 제거하기
			}
		}
		x = 1;
	}
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		dfs(1, 1, 0);
		//출력
		if (0x7fffffff == ret)ret = -1;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}