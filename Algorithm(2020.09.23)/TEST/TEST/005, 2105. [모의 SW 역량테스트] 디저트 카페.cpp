#include<stdio.h>
#include<iostream>
#include<string.h>
#include<iostream>
using namespace std;
#define NSIZE 21
#define FOODSIZE 101
//대가선 방향 배열
int dy[] = { 1,1,-1,-1 };
int dx[] = { 1,-1,-1,1 };
int input[NSIZE][NSIZE];//입력으로 주어지는 값 저장 배열
int num[FOODSIZE];//디저트 체크하는 배열
int N, T;//배열의 크기와 테스트 케이스
int ret;//결과값 
bool safe(int y, int x) {//범위 체크 함수
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	//초기화
	memset(input, 0, sizeof(input));
	memset(num, 0, sizeof(num));
	N = 0;
	ret = 0x80000000;//최대값
	//입력
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	return;
}
void play() {//음식 먹으러 가는 함수
	int visit[NSIZE][NSIZE] = { 0, };
	for (int y = 0; y < N; y++) {//탐색시작
		for (int x = 0; x < N; x++) {
			//대각선 사각형의 길의 선정

			for (int a = 1; a <= N; a++) {
				for (int b = 1; b <= N; b++) {
					int flag = 0;//탈출 위한 변수
					int cnt = 0;//디저트 먹은거 개수 저장
					memset(num, 0, sizeof(num));
					memset(visit, 0, sizeof(visit));//체크확인 배열 잘찍히는지

					cnt = 0;//디저트 먹은거 개수 저장
					int cy = y, cx = x;//현재 좌표값
					for (int dir = 0; dir < 4; dir++) {
						if (dir == 0 || dir == 2) {//오른쪽대각선 아래, 왼쪽 대각선 위
							for (int i = 0; i < a; i++) {
								int ny = cy + dy[dir]; int nx = cx + dx[dir];//다음 위치
								if (!num[input[ny][nx]] && safe(ny, nx)) {
									visit[ny][nx] = 1;
									num[input[ny][nx]] = 1;//중복 체크
									cy = ny; cx = nx;//위치 넘기기
									cnt++;//디저트 먹음
								}
								else {//벗어나거나 중복인경우
									flag = 1;
									break;
								}
							}
						}
						else {//왼쪽대각선 아래, 오른쪽 대각선 위
							for (int j = 0; j < b; j++) {
								int ny = cy + dy[dir]; int nx = cx + dx[dir];//다음 위치
								if (!num[input[ny][nx]] && safe(ny, nx)) {
									visit[ny][nx] = 1;
									num[input[ny][nx]] = 1;//중복 체크
									cy = ny; cx = nx;//위치 넘기기
									cnt++;//디저트 먹음
								}
								else {
									flag = 1;
									break;
								}
							}
						}
						if (dir == 3 && flag == 0 && cnt != 0) {

										//cout << endl;
										//for (int ii = 0; ii < N; ii++) {
										//	for (int jj = 0; jj < N; jj++) {
										//		printf("%2d", visit[ii][jj]);
										//	}
										//	cout << endl;
										//}
							ret = ret < cnt ? cnt : ret;
						}
					}
				}
			}

		}
	}
	if (ret == 0x80000000)ret = -1;
}
int main(void) {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}