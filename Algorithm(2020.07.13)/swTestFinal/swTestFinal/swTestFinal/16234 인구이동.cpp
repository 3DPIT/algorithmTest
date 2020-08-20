#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define N_SIZE 51
int N, L, R;// 배열의 크기, 최소, 최대 수
int ret;//결과값 저장
int humanMap[N_SIZE][N_SIZE];// 인구수 저장 배열
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int flag = 0;//구역 열린지 체크
int visit[N_SIZE][N_SIZE] = { 0, };
struct Data {
	int sum, num;
};
Data a[2501];// 구역의 값 계산하기
void init() {
	// 초기화 시키기
	N = L = R = ret = 0;
	memset(humanMap, 0, sizeof(humanMap));
	//
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {	// 인구 데이터 입력
		for (int j = 0; j < N; j++) {
			scanf("%d", &humanMap[i][j]);
		}
	}
	//
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
void dfs(int y, int x, int cnt) {

	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (safe(y,x)) {
			int num = abs(humanMap[y][x] - humanMap[ny][nx]);// 인구수의 차 계산
			if (L <= num && num <= R && visit[ny][nx] == 0) {
				flag = 1;
				a[cnt].sum += humanMap[ny][nx];//1의 구역의 데이터값 저장하기
				a[cnt].num++;//구역의 수 증가시키기
				visit[ny][nx] = cnt;
				dfs(ny, nx, cnt);
			}
		}
	}
}
int openLine() {
	int cnt = 0;
	memset(visit, 0, sizeof(visit));
	memset(a, 0, sizeof(a));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == 0) {
				++cnt;
				a[cnt].sum = humanMap[i][j];
				a[cnt].num = 1;
				visit[i][j] = cnt;
				dfs(i, j, cnt);
				a[visit[i][j]].sum /= a[visit[i][j]].num;
			}
		}
	}

	for (int i = 0; i < N; i++) {// 인구 분배하기
		for (int j = 0; j < N; j++) {
			if (visit[i][j] >= 1) {
				int num = a[visit[i][j]].sum;
				// 나눠진 인구수
				humanMap[i][j] = num;
			}
		}
	}
	return flag;
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		while (1) {
			int cnt = openLine();
			if (cnt == 0)break;
			flag = 0;
			++ret;
		}
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}