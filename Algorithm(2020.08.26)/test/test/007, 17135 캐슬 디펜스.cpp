#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
#define N_SIZE 16
#define M_SIZE 16
int N, M, D;//배열크기 y x,죽일수 있는 적 거리
int castle[N_SIZE][M_SIZE];//입력 배열
int ret;//최대 수 저장
struct Data {
	int y, x;
}dieArr[3];
void init() {
	//초기화
	memset(castle, 0, sizeof(castle));
	N = M = D = 0;
	ret = 0x80000000;
	//입력
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &castle[i][j]);//적의 정보 입력 
		}
	}
}
void downArr() {
	for (int i = N-1; i >=1; i--) {//배열 내리기
		for (int j = 0; j < M; j++) {
			castle[i][j] = castle[i-1][j];
		}
	}
	for (int j = 0; j < M; j++) {//제일 윗줄 0으로 초기화
		castle[0][j] = 0;
	}
}
void copy(int Ccastle[N_SIZE][M_SIZE],int castle[N_SIZE][M_SIZE]) {//배열 복사
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Ccastle[i][j] = castle[i][j];
		}
	}
}
int playGame() {
	int cnt = 0;
	int Ccastle[N_SIZE][M_SIZE] = { 0, };
	copy(Ccastle, castle);
	for (int k = 0; k < N; k++) {
		memset(dieArr, 0, sizeof(dieArr));//초기화
		int idx = 0;//적의 좌표 의 인덱스
		for (int x = 0; x < M; x++) {// 궁수의 좌표 찾기위한 반복문
			int sY = N, sX = -1;// 궁수의 좌표 저장하는 변수 
			if (castle[N][x] == 0) continue;
			sX = x;//y값은 N 으로 고정이므로 x값만 변경하면됨		
			int minD, minY, minX;
			minD = minY = minX = 0x7fffffff;//최소의 D값이고 y값 구하기 위한 변수
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (castle[i][j] == 1) {//적발견시
						int distance = abs(N - i) + abs(sX - j);
						if (distance <= D) {//적을 죽일 수 있는 범위
							if (minD >= distance) {
								if (minD > distance || (minD == distance && minX > j)) {
									minD = distance;
									minY = i;
									minX = j;
								}
							}
						}//거리 비교 if끝
					}
				}
			}//처음 포문끝

			if (minD != 0x7fffffff) {//죽일 적이 있다면 저장시키기
				dieArr[idx].y = minY; dieArr[idx++].x = minX;
			}
		}
		for (int dieI = 0; dieI < idx; dieI++) {
			if (castle[dieArr[dieI].y][dieArr[dieI].x] == 1) {
				castle[dieArr[dieI].y][dieArr[dieI].x] = 0;
				cnt++;//적죽이고 세기
			}
		}
		downArr();
	}//N번 적 내려감
	copy(castle, Ccastle);
	return cnt;//죽인 적 보내기
}
void dfs(int idx, int d) {
	if (idx > M)return;// 인덱스 넘어가면 리턴
	if (d == 3) {//궁수 위치 선정하면 들어가는곳
		int die = playGame();
		ret = ret < die ? die : ret;//최대값 산출
		return;
	}

	castle[N][idx] = 1;//궁수 위치 선정하기
	dfs(idx + 1, d + 1);//궁수 뽑는 경우
	castle[N][idx]=0;
	dfs(idx + 1, d);//궁수 안뽑고 인덱스 올리는경우
}

int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0, 0);
		//printf("#%d %d\n",tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}