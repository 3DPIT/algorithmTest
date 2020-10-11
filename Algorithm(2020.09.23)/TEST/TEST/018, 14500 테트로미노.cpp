#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
#define NMS 500//N과M의 최대 크기
int N, M;//가로크기 , 세로 크기
int ret;//최종 최대값
int B[NMS][NMS];//보드판 초기입력
int cB[NMS][NMS];//테트로미노 생성할 배열
int dy[] = {0,1,0,-1};
int dx[] = {1,0,-1,0};
void printArr(int A[NMS][NMS]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d", A[i][j]);
		}
		printf("\n");
	}
}
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = 0;
	ret = 0x80000000;
	memset(B, 0, sizeof(B));
	memset(cB, 0, sizeof(cB));
	//초기 입력
	scanf("%d %d", &N, &M);//가로 세로 크기 입력
	for (int i = 0; i < N; i++) {//초기 배열값 입력
		for (int j = 0; j < M; j++) {
			scanf("%d", &B[i][j]);
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x, int cnt,int sum) {
	if (cnt == 3) {//나머지 테트리스 모양
		ret = max(ret, sum);
		return;
	}

	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (safe(ny, nx) && cB[ny][nx] == 0) {
			cB[ny][nx] = 1;
			sum += B[ny][nx];
			dfs(ny, nx, cnt + 1,sum);
			sum -= B[ny][nx];
			cB[ny][nx] = 0;
		}
	}
}
void dfs1(int y, int x, int cnt,int dir, int sum) {//가운데 ->인경우
	if (cnt == 2) {
		ret = max(ret, sum);
		return;
	}
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (safe(ny, nx) && cB[ny][nx] == 0) {//가운데 부분에 추가해서 계산
			if (cnt == 1) {
				int cdir = dir;
				cdir=(++cdir)%4;
				int cny = y + dy[cdir]; int cnx = x + dx[cdir];
				if (safe(cny, cnx)) {
					sum += B[ny][nx];
					sum += B[cny][cnx];
					cB[ny][nx] = 1;
					cB[cny][cnx] = 1;
					dfs1(ny, nx, cnt + 1, dir, sum);
					cB[cny][cnx] = 0;
					sum -= B[ny][nx];
					sum -= B[cny][cnx];
					cB[ny][nx] = 0;
				}
				else return;

			}
			else {
				cB[ny][nx] = 1;
				sum += B[ny][nx];
				dfs1(ny, nx, cnt + 1,dir, sum);
				sum -= B[ny][nx];
				cB[ny][nx] = 0;
			}
		}
}
void gameStart() {//게임 시작
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cB[i][j] = 1;
			dfs(i, j, 0,B[i][j]);//배열의 시작y,x,cnt;
			for (int dir = 0; dir < 4; dir++) {
				dfs1(i, j, 0, dir, B[i][j]);
			}
			cB[i][j] = 0;
		}
	}
}
int main(void) {
	int T = 1;//테스트 개스
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//초기화 및 초기 입력
		init_input();
		gameStart();//게임 시작
		//출력값
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}