#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define N_SIZE 13
struct Data {
	int y,x, dir, num;
}H[11];
int dy[] = {0,0,0,-1,1 };//방향 
int dx[] = {0,1,-1,0,0 };
int ret=-1;//최종값
int N, K;//배열크기, 말의 개수
int input[N_SIZE][N_SIZE];//입력으로 들어오는 값
vector<Data>horse[N_SIZE][N_SIZE];//말의 정보들어있는 배열
bool safe(int y, int x) {//범위 확인
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	//초기화
	N = K = 0;
	ret = -1;
	memset(input, 0, sizeof(input));
	memset(horse, 0, sizeof(horse));
	memset(H, 0, sizeof(H));
	//입력
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	for (int k = 0; k < K; k++) {
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		horse[y-1][x-1].push_back({y-1,x-1,dir,k + 1});//말의 데이터 저장
		H[k + 1].y = y-1; H[k + 1].x = x-1; H[k + 1].dir = dir; H[k + 1].num = k + 1;
		//y,x,dir,num 입력
	}
}
int white(int y, int x, int dir, int num,int ny,int nx) {
	int size = horse[y][x].size();//이전공간 말의 수
	for (int i = 0; i < size; i++) {//이동 공간에 말 올리기
		H[horse[y][x][i].num].y = ny; H[horse[y][x][i].num].x = nx;//위치 최신화
		horse[ny][nx].push_back({ ny,nx,horse[y][x][i].dir,horse[y][x][i].num });
	}
	while (horse[y][x].size() != 0) {
		horse[y][x].pop_back();
	}//데이터 초기화
	return 1;
}
int red(int y, int x, int dir, int num, int ny, int nx) {
	int size = horse[y][x].size();//이전공간 말의 수
	for (int i = size-1; i >=0; i--) {//이동 공간에 말 올리기
		H[horse[y][x][i].num].y = ny; H[horse[y][x][i].num].x = nx;//위치 최신화
		horse[ny][nx].push_back({ ny,nx,horse[y][x][i].dir,horse[y][x][i].num });
	}
	while (horse[y][x].size() != 0) {
		horse[y][x].pop_back();
	}//데이터 초기화
	return 1;
}
int blue(int y, int x, int dir, int num, int ny, int nx) {
	if (1 == dir)dir = 2;
	else if (2 == dir)dir = 1;
	else if (3 == dir)dir = 4;
	else if (4 == dir)dir = 3;
	H[num].dir = dir;
	horse[y][x][0].dir = dir;
	if (safe(y + dy[dir], x + dx[dir])) {//흰색과 빨간 조건
		if (input[y + dy[dir]][x + dx[dir]] == 0) {
			white(y, x, dir, num, y + dy[dir], x + dx[dir]);
		}
		if (input[y + dy[dir]][x + dx[dir]] == 1) {
			red(y, x, dir, num, y + dy[dir], x + dx[dir]);
			}
	}
	return 1;
}

void gameStart() {
	int Time = 0;
	int Flag = 0;//확인
	while (1) {
		Time++;
		if (Time == 1001)break;
		for (int i = 1; i <= K; i++) {//말 검사
			int y, x, dir;
			y = H[i].y; x = H[i].x; dir = H[i].dir;//i 말의 정보
			if (horse[y][x][0].num != i)continue;
			int ny = y + dy[dir]; int nx = x + dx[dir];
			if (!safe(ny, nx) || input[ny][nx] == 2) {//blue
				blue(y, x, dir, i, ny, nx);
	
			}
			if (safe(ny, nx) && input[ny][nx] == 0) {//white
				white(y, x, dir, i, ny, nx); 
	
			}
			if (safe(ny, nx) && input[ny][nx] == 1) {//red
				red(y, x, dir, i, ny, nx);

			}
		}//1번 포문 끝
		if (Flag)break;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (horse[i][j].size() >= 4) {
					ret = Time;
					return;
				}
			}
		}
	}//1번 와일 끝
	if (Flag) ret =  Time;//4개 탑완성시 
	else ret = -1;
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		gameStart();

		//출력
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}