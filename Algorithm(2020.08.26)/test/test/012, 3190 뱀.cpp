#include<stdio.h>
#include<string.h>
using namespace std;
#define NSIZE 101 //맵 최대크기+1
int input[NSIZE][NSIZE];//사과나 뱀 위치 저장
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, X,K;//크기, 초, 사과개수
char C;//방향
int ret = 0; // 결과값
void init() {
	N = X = 0; C = NULL;
	memset(input, 0, sizeof(input));
	scanf("%d", &N);
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {//사과 위치
		int y, x;
		scanf("%d %d", &y, &x);
		input[y][x] = -1;//사과 위치 입력
	}
	scanf("%d", &X);
}
bool iSafe(int y, int x) {
	return y < 1 || y>N || x<1 || x>N;
}
void playGame() {
	int xTime = 0;
	int y = 1, x = 1,dir=0;
	int size = 1;
	ret = 1;
	input[y][x] = 1;
	for (int it = 0; it < X; it++) {
		scanf("%d %c", &xTime,&C);
		while (1) {
			if (ret == xTime+1) {//방향 전환시
				if (C == 'D')dir++;//오른쪽 전환
				if (C == 'L')dir--;//왼쪽 전환
				if (dir == 4)dir = 0;
				else if (dir == -1)dir = 3;
				if(it!=X-1)break;// 입력이 끝나는 경우 완료되면 안되므로
			}
			int tail = ret - size;
			if (input[y][x] == -1) {//사과 먹었을때
				size++;
			}
			else if ((size != 1 && input[y][x] >=tail) || iSafe(y, x)) {//끝나는 경우
				while (it < X - 1) {//입력이 끝나지 않은 경우 입력 시키기
					scanf("%d %c", &xTime, &C);
					it++;
				}
				break;//게임 종료
			}
			input[y][x]=ret++;//맵에 기록
			y += dy[dir];
			x += dx[dir];

		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		playGame();
		//printf("#%d %d\n", tc, ret-1);
		printf("%d\n", ret-1);
	}
	return 0;
}
