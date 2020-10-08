#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define NSIZE 101
int N;//정사각형의 크기 
int square[NSIZE][NSIZE];//입력 데이터
int ret;//결과값
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
bool safe(int y, int x) {//범위 확인
	return 0 <= y && y < N && 0 <= x && x < N;
}
struct whiteHoll {
	int y, x;
};
vector<whiteHoll>WH[5];//웜홀의 데이터 저장
void init() {//초기화
	N = 0;
	ret = 0x80000000;//최대값 뽑기
	memset(square, 0, sizeof(square));
	memset(WH, 0, sizeof(WH));
}
void gamePlay() {//핀볼 알고리즘
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			if (square[y][x] == 0) {//출발 위치 선정
				for (int dir = 0; dir < 4; dir++) {
					int ny = y; int nx = x;//위치
					int ndir = dir;//방향
					int score = 0;//점수
					while (1) {
						ny += dy[ndir]; nx += dx[ndir];//위치
						if (safe(ny, nx)) {//사각형 안인경우
							if ((ny==y&&nx==x)||square[ny][nx] == -1) {//블랙홀 만나면 탈출 하고 이때 점수 최대값 산출
								ret = ret < score ? score : ret;//최대값 산출
								break;
							}
							else if (square[ny][nx] == 1) {//1경우에 dir 방향 변화
								if (ndir == 0)ndir = 2;
								else if (ndir == 1)ndir = 3;
								else if (ndir == 2)ndir = 1;
								else if (ndir == 3)ndir = 0;
								score++;//점수 증가
							}
							else if (square[ny][nx] == 2) {//2경우에 dir 방향 변화
								if (ndir == 0)ndir = 1;
								else if (ndir == 1)ndir = 3;
								else if (ndir == 2)ndir = 0;
								else if (ndir == 3)ndir = 2;
								score++;//점수 증가
							}
							else if (square[ny][nx] == 3) {//3경우에 dir 방향 변화
								if (ndir == 0)ndir = 3;
								else if (ndir == 1)ndir = 2;
								else if (ndir == 2)ndir = 0;
								else if (ndir == 3)ndir = 1;
								score++;//점수 증가
							}
							else if (square[ny][nx] == 4) {//4경우에 dir 방향 변화
								if (ndir == 0)ndir = 2;
								else if (ndir == 1)ndir = 0;
								else if (ndir == 2)ndir = 3;
								else if (ndir == 3)ndir = 1;
								score++;//점수 증가
							}
							else if (square[ny][nx] == 5) {//5경우에 dir 방향 변화
								if (ndir == 0)ndir = 2;
								else if (ndir == 1)ndir = 3;
								else if (ndir == 2)ndir = 0;
								else if (ndir == 3)ndir = 1;
								score++;//점수 증가
							}
							else if (square[ny][nx] >= 6) {//6-10인 웜홀 경우에 위치 변화시키기
								int cy = 0, cx = 0;//복사할 위치
								for (int i = 0; i <WH[square[ny][nx]-6].size(); i++) {//반대쪽 웜홀로 위치 이동
									if (ny == WH[square[ny][nx] - 6][i].y&&ny == WH[square[ny][nx] - 6][i].x)continue;
									else {
										cy = WH[square[ny][nx] - 6][i].y;//위치 복사
										cx = WH[square[ny][nx] - 6][i].x;
										break;
									}
								}
								ny = cy;
								nx = cx;
							}
							if ((ny == y && nx == x) || square[ny][nx] == -1) {//블랙홀 만나면 탈출 하고 이때 점수 최대값 산출
								ret = ret < score ? score : ret;//최대값 산출
								break;
							}
						}
						else {//벽을 넘어선경우나 벽에 부딪힌 경우 반대로 방향 변화
							if (ndir == 0) ndir = 2;
							else if (ndir == 1)ndir = 3;
							else if (ndir == 2)ndir = 0;
							else if (ndir == 3)ndir = 1;
							score++;//점수 증가
						}

					}//while(1)

				}//for dir
			}
		}//for x
	}//for y
}
int main(void) {
	int T;//테스트케이스
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {//입력값 입력
			for (int j = 0; j < N; j++) {
				scanf("%d", &square[i][j]);
				if (square[i][j] >= 6) {
					WH[square[i][j] - 6].push_back({ i,j });//웜홀 데이터 저장
				}
			}
		}
		gamePlay();
		printf("#%d %d\n", tc, ret);
	}
}