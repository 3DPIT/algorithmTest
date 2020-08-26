#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define N_SIZE 52
#define M_SIZE 52
int N, M, T;//y축,x축,테스트할 개수
int cycleInput[N_SIZE][M_SIZE];// 원 입력 배열
int visit[N_SIZE][M_SIZE];//dfs 방문체크 배열
int ret;// 최종값 저장
int dy[] = { 0,1,0,-1 };//방향 y
int dx[] = { 1,0,-1,0 };//방향 x
int cM;
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void init() {
	// 초기화 하는 위치
	memset(cycleInput, 0, sizeof(cycleInput));
	memset(visit, 0, sizeof(visit));
	N = M = T = ret = 0;
	scanf("%d %d %d", &N, &M, &T);
	 cM = M;
	for (int i = 0; i < N; i++) {// 데이터 입력
		for (int j = 0; j < M; j++) {
			scanf("%d", &cycleInput[i][j]);
		}
	}
}
//구현 내용
void clockRotaion(int idx, int cnt, int d) {
	//시계방향 돌리는 함수
	if (d == 0) {
		for (int c = 0; c < cnt; c++) {
			int lastNum = cycleInput[idx][M - 1];// 가장 끝값
			for (int i = M - 2; i >= 0; i--) {
				cycleInput[idx][i + 1] = cycleInput[idx][i];
			}
			cycleInput[idx][0] = lastNum;
		}
	}
	//반시계 방향 돌리는 함수
	if (d == 1) {
		for (int c = 0; c < cnt; c++) {
			int firstNum = cycleInput[idx][0];//맨 앞값 저장
			for (int i = 1; i < M; i++) {
				cycleInput[idx][i - 1] = cycleInput[idx][i];
			}
			cycleInput[idx][M - 1] = firstNum;
		}
	}
}
//dfs 함수 구현 전부 다 돌아가는
bool flag = 0;// 제거되는 수 있는지 확인 변수
void dfs(int y, int x,int num) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		// 범위 넘어가는것 체크
		if (nx == M) {
			nx = 0;
		}
		if (-1 == nx) {
			nx = M - 1;
		}
		//방문 및 갈 수 있는 방향 체크
		if (safe(ny,nx)&&0==visit[ny][nx] && cycleInput[ny][nx] == num) {
			visit[ny][nx] = 1;//방문체크
			cycleInput[ny][nx] = 0;
			flag = 1;
			dfs(ny,nx,num);// dfs 돌리기
		}
	}
}
//수를 제거 못하면 평균값 구하는 함수 
void DFS() {
	memset(visit, 0, sizeof(visit));
	bool FLAG =1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (cycleInput[i][j]!=0
				&&visit[i][j] == 0) {
				dfs(i, j, cycleInput[i][j]);
				if (flag) {
					flag = 0;
					visit[i][j] = 1;
					cycleInput[i][j] = 0;
					FLAG = 0;//제거되는것 있는지 확인 변수
				}
			}
		}
	}

	if (FLAG) {//제거되는것 없으면 평균값 구하기
		int cnt = 0;//숫자 갯수 세기
		int sum = 0;//숫자 합 
		double avgSum = 0;
		for (int i = 0; i < N; i++) {//숫자의 합과 갯수 구하는 곳
			for (int j = 0; j < M; j++) {
				if (cycleInput[i][j] != 0) {
					sum += cycleInput[i][j];
					cnt++;
				}
			}
		}//
		avgSum = (double)sum / cnt;
		for (int i = 0; i < N; i++) {//평균보다 크면 -1. 작으면 +1
			for (int j = 0; j < M; j++) {
				if (cycleInput[i][j] != 0 && avgSum < cycleInput[i][j])// 작은경우
				{
					cycleInput[i][j] -= 1;
				}
				else if (cycleInput[i][j] != 0 && avgSum > cycleInput[i][j])// 큰경우
				{
					cycleInput[i][j] += 1;
				}

			}
		}
	}//if(FLAG) 끝부분
}
void arrSum() {

}
void Rotation() {// 최종으로 돌아가면서 계산하는곳
	for (int t = 1; t <= T; t++) {//시작
		int x, d, k;
		scanf("%d %d %d", &x, &d, &k);//x배수, d방향(0: 시계, 1: 반시계),k번회전
		for (int i = 0; i < N; i++) {
			int X = i + 1;
			if (X%x == 0) {//x의 배수라면 
				clockRotaion(i, k, d);//돌릴 y축, 회전수, 방향
			}
		}
		DFS();
	}
	//배열의 숫자 합구하기
	arrSum();
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);//테스트 케이스 입력
	for (int tc = 1; tc <= testCase; tc++) {
		init();//초기화 및 입력 
		Rotation();
		//printf("#%d %d\n", tc, ret);// 출력
		printf("%d\n", ret);
	}
	return 0;
}