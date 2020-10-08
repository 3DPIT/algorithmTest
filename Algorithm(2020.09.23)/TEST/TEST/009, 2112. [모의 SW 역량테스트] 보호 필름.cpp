#include<stdio.h>
#include<vector>
#include<iostream>
#include<string.h>
using namespace std;
#define DSIZE 13
#define WSIZE 20
int D, W, K;//두께, 가로크기, 합격기준
int T;//테스트 케이스 개수
int film[DSIZE][WSIZE];//입력으로 주어지는 필름
int ret;//결과값 저장
int d[DSIZE];
void init() {//초기화
	D = W = K = 0;
	ret = 0x7fffffff;
	memset(film, 0, sizeof(film));
}
void copy(int idx, int copyFilm[WSIZE], int flag) {// 현재 위치 복사
	if (flag == 0) {//백업
		for (int i = 0; i < W; i++)
			copyFilm[i] = film[idx][i];
	}
	else {//복원
		for (int i = 0; i < W; i++)
			film[idx][i] = copyFilm[i];
	}
}
void changeType(int idx, int type, int copyFilm[WSIZE]) {//타입 변경
	if (type != 2) {
		for (int i = 0; i < W; i++)
			film[idx][i] = type;
	}
}
bool kTest() {//합격 기준 판별
	int Test = 0;//W까지 합격 이면 true 아니면 false
	for (int j = 0; j < W; j++) {
		for (int i = 0; i < D - 1; i++) {
			int cnt = 1;
			for (int ci = i + 1; ci < D; ci++) {
				if (film[i][j] == film[ci][j]) {//필름이 같으면 
					cnt++;
				}
				else {
					break;
				}
			}
			if (cnt >= K) {
				Test++;
				break;
			}
		}
		if (Test != j + 1)return false;
	}
	return true;
}
void dfs(int idx, int type, int cnt) {
	if (ret <= cnt)return;//혹여 현재 최소값보다 커지는 값이면 리턴
	if (idx == D + 1)return;
	else {//합격 기준 판별
		//판별기준
		if (kTest()) {
			ret = ret > cnt ? cnt : ret;//최소값 갱신
		}
	}
	int copyFilm[WSIZE] = { 0, };//현재 필름 복사
	dfs(idx + 1, 0, cnt);//그대로
	copy(idx, copyFilm, 0);//미리 복사
	changeType(idx, 0, copyFilm);
	dfs(idx + 1, 0, cnt + 1);//A타입으로
	changeType(idx, 1, copyFilm);
	dfs(idx + 1, 1, cnt + 1);//B타입으로
	copy(idx, copyFilm, 1);//백업
}
int main(void) {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		//입력하기
		scanf("%d %d %d", &D, &W, &K);
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &film[i][j]);
			}
		}
		//알고리즘 시작
		dfs(0, 0, 0);
		//출력
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}