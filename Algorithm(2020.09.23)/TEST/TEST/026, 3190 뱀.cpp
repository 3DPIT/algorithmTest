#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<vector>
using namespace std;
#define NS 101//배열의 최대 크기
int N, K, L;//배열크기, 사과 개수, 경로개수
int ret;//결과값
int map[NS][NS];//뱀의 경로 배열
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
void init_input() {//초기화 및 초기 입력
	//초기화 
	N = K = L = 0;
	ret = 0;
	memset(map, 0, sizeof(map));
	//초기 입력
	scanf("%d %d",&N, &K);
	for (int k = 0; k < K; k++) {//사과 위치 
		int y, x;
		scanf("%d %d",&y, &x);
		map[y][x] = -1;//사과 저장
	}
}
bool safe(int y, int x) {//범위
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void gameStart() {
	int y = 1, x = 1, dir = 0, size = 1, tail = 1;//뱀의 상태
	scanf("%d", &L);
	for (int l = 0; l < L; l++) {
		int X; char C;//게임시작 시간으로 부터 X초, 방향 C-> D오른쪽,L왼쪽
		scanf("%d %c", &X, &C);
		while(1) {//시뮬 시작
			if (ret == X) {//방향 전환하는곳
				if (C == 'D') {//오른쪽 방향 전환
					dir = (++dir) % 4;
				}
				else if(C == 'L') {//왼쪽 방향 전환
					dir = (4+(--dir)) % 4;
				}
				if(l!=L-1)
				break;
			}
			//1. 먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.

			int ny = y + dy[dir]; int nx = x + dx[dir];
			if (!safe(ny,nx)||(map[ny][nx]!=0&&map[ny][nx] >= tail-1&&size!=1)) {//꼬리에 닿는 경우 나 나가는 경우
				if (l != L - 1) {//남은 경로 없애기
					for (l++; l < L; l++) {
						scanf("%d %c", &X, &C);
					}
				}
				break;
			}

			//2. 만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
			if (map[ny][nx] == -1) {
				map[ny][nx] = ++ret;//사과 먹고
				size++;
			}
			//3. 만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.즉, 몸길이는 변하지 않는다.
			else if (map[ny][nx] != -1) {
				map[ny][nx] = ++ret;
				tail++;//꼬리칸 비워주기
			}
			y = ny; x = nx;
		}
	}
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		gameStart();//게임 시작
		//출력
		printf("%d\n", ret+1);
		//printf("#%d %d\n", tc, ret+1);
	}
	return 0;
}
