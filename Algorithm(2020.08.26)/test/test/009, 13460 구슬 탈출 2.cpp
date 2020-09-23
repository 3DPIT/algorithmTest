#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
#define BOARD_SIZE 11//보드 최대 사이즈
char board[BOARD_SIZE][BOARD_SIZE];
int visit[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];//맵 공위치 체크
//맵 이동을 위한 우,하,좌,상
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, M;//맵의 크기 선정 변수
int ret;//결과값 저장 변수
void print(char m[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%c ", m[i][j]);
		}
		printf("\n");
	}
}
struct BallData {//공의 데이터 저장을 위한 구조체
	int ry, rx, by, bx, cnt;
}firstBall;
struct Data {
	int y, x;
};
int hy, hx;// 홀의 위치
void init() {
	//초기화
	N = M = 0; ret = 0x7fffffff;
	memset(board, 0, sizeof(board));
	memset(visit, 0, sizeof(visit));
	//시작
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &board[i][j]);//입력
			if (board[i][j] == 'R') {
				firstBall.ry = i;//빨간공 위치 저장
				firstBall.rx = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'B') {
				firstBall.by = i;//파란공 위치 저장
				firstBall.bx = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'O') {
				hy = i; hx = j;//홀의 위치 저장
			}
		}
	}
	//print(board);
}
Data ballMove(int y, int x, int dir) {
	Data n;
	while (1) {
		n.y = y + dy[dir]; n.x = x + dx[dir];
		if (board[n.y][n.x] == '#' || board[n.y][n.x] == 'O') {
			if (board[n.y][n.x] == '#') {
				n.y -= dy[dir]; n.x -= dx[dir];
			}
			break;
		}
		y = n.y; x = n.x;
	}
	return n;
}
void BFS() {
	//큐선언하고 초기 빨강 파랑 공위치 푸쉬
	queue<BallData>q;
	q.push({ firstBall.ry,firstBall.rx,firstBall.by,firstBall.bx,0 });
	while (!q.empty()) {
		BallData  c = q.front(); q.pop();
		if ((c.ry == hy && c.rx == hx) || c.cnt == 11) {//들어갔으면 종료 
			if (c.cnt != 11)ret = c.cnt;//탈출 조건 홀위치거나 10회초과된경우
			break;
		}
		for (int dir = 0; dir < 4; dir++) {
			BallData n;
			Data R, B;
			R = ballMove(c.ry, c.rx, dir);//빨간공 이동
			B = ballMove(c.by, c.bx, dir);//파란공 이동
			if (R.y == B.y&&R.x == B.x&&board[R.y][R.x] == 'O') continue;//두개다 홀에 빠진 경우

			int redD = abs(c.ry - R.y) + abs(c.rx - R.x);
			int blueD = abs(c.by - B.y) + abs(c.bx - B.x);
			if (R.y == B.y&&R.x == B.x) {//같은 위치에 있는경우
				if (redD < blueD) {//빨강이 먼저 도착한 경우
					B.y -= dy[dir];//한칸 뒤로 이동
					B.x -= dx[dir];
				}
				else if (redD > blueD) {//파랑이 먼저 도착한 경우
					R.y -= dy[dir];//한칸 뒤로 이동
					R.x -= dx[dir];
				}
			}
			//board[R.y][R.x] = 'R';
			//board[B.y][B.x] = 'B';
			//for (int i = 0; i < N; i++) {
			//	for (int j = 0; j < M; j++) {
			//		cout <<" "<< board[i][j];
			//	}
			//	cout << '\n';
			//}
			//cout << '\n';
			//board[R.y][R.x] = '.';
			//board[B.y][B.x] = '.';
			if (B.y == hy && B.x == hx)continue;
			if (visit[R.y][R.x][B.y][B.x] == 0) {//중복 체크
				visit[R.y][R.x][B.y][B.x] = 1;
				q.push({ R.y,R.x,B.y,B.x,c.cnt + 1 });
			}

		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);//테스트 케이스입력
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		BFS();
		if (0x7fffffff == ret)ret = -1;//공 못들어가는 경우
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}