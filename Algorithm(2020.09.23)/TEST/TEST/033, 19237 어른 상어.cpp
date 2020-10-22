#include<stdio.h>
#include<vector>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
#define NS 21//최대 배열 사이즈
int ret;//결과값
int N, M, K;//배열 크기, 상어 수, 상어 자체의 흔적 시간
int dy[] = { 0,-1,1,0,0 };// 1: 위, 2: 아래 3: 왼 4 : 오
int dx[] = { 0,0,0,-1,1 };
struct Data {
	int n; int c1; int f;//상어의 숫자, 상어의 남은 흔적 시간,상어의 흔적이면 0, 상어이면 1
}B[NS][NS];
struct Data1 {
	int y, x, dir, n;
}sharkPos[NS*NS];//상어의 위치 실시간 확인 위함

int sharkDir[NS*NS][5][5];//상어의 각 방향마다의 우선 순위 저장 배열
bool safe(int y, int x) {//범위 확인 함수
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void init_input() {//초기화 및 초기 입력
	//초기화 
	N = M = K = ret = 0;
	memset(B, 0, sizeof(B));
	memset(sharkDir, 0, sizeof(sharkDir));
	memset(sharkPos, 0, sizeof(sharkPos));
	//초기입력
	scanf("%d %d %d", &N, &M, &K);//배열 크기, 상어 수, 상어 흔적 수
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &B[i][j].n);//배열의 입력
			if (B[i][j].n != 0) {//상어의 위치 저장
				sharkPos[B[i][j].n].y = i; sharkPos[B[i][j].n].x = j;
				sharkPos[B[i][j].n].n = B[i][j].n;
				B[i][j].f = 1;
				B[i][j].c1 = 4;
			}
		}
	}
	for (int i = 0; i < M; i++) {//현재 상어의 방향 저장
		int dir = 0; scanf("%d", &dir);
		sharkPos[i + 1].dir = dir;
		sharkPos[i + 1].n = i + 1;

	}
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			int a, b, c, d;//우선 순위 적용
			scanf("%d %d %d %d", &a, &b, &c, &d);
			sharkDir[i][j][1] = a;
			sharkDir[i][j][2] = b;
			sharkDir[i][j][3] = c;
			sharkDir[i][j][4] = d;
		}
	}
}
void playGame() {
	while (ret <= 1000) {
		ret++;//시간 증가
		//1. 상어의 이동
		for (int si = 1; si <=M ; si++) {
			Data1 c = sharkPos[si];
			int c1 = 0;//인접 구역에 빈공간 없는것 체크하기 위함
			for (int d = 1; d <= 4; d++) {
				int dir = sharkDir[si][sharkPos[si].dir][d];
				Data1 n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.dir = dir; n.n = c.n;
				//a. 인접칸중에 흔적이 없는 칸 먼저 푸쉬
				if (safe(n.y, n.x) && B[n.y][n.x].c1 == 0 && B[n.y][n.x].f == 0 && B[n.y][n.x].n == 0) {
					c1=1;
					B[c.y][c.x].f = 0;
					B[c.y][c.x].n = si;
					B[c.y][c.x].c1 = K;
					sharkPos[si] = n;
					break;
				}
			}
			if (c1 == 0) {//b. 그런칸이 없다면 자신 냄새 흔적 칸으로 푸쉬
				for (int d = 1; d <= 4; d++) {
					int dir = sharkDir[si][sharkPos[si].dir][d];
					Data1 n;
					n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.dir = dir; n.n = c.n;
					if (safe(n.y, n.x) && B[n.y][n.x].f==0&& B[n.y][n.x].n == si) {
						B[c.y][c.x].f = 0;
						B[c.y][c.x].c1 = K;
						B[c.y][c.x].n = si;
						sharkPos[si] = n;
						break;
					}
				}
			}
		}
		//2. 이동중 상어끼리 충돌한것중 작은 상어가 큰상어 내보내기
		for (int si = 1; si <M; si++) {
			for (int sj = si+1; sj <= M; sj++) {
				if (si == sj)continue;
				if (si < sj&&sharkPos[si].y == sharkPos[sj].y&&sharkPos[si].x == sharkPos[sj].x) {
					sharkPos[sj].dir = 0; sharkPos[sj].n = -1; sharkPos[sj].x = 0; sharkPos[sj].y = 0;
				}
			}
		}
		for (int si = 1; si <= M; si++) {//배열에 다시 입력
			if (sharkPos[si].n == -1)continue;
			B[sharkPos[si].y][sharkPos[si].x].c1 = K; B[sharkPos[si].y][sharkPos[si].x].n = si;
			B[sharkPos[si].y][sharkPos[si].x].f = 1;
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (B[i][j].f != 1 && B[i][j].c1 != 0) {
					B[i][j].c1--;
					if (B[i][j].c1 == 0) {
						B[i][j].n = 0;
					}
				}
			}
		}
		int sc1 = 0;
		for (int si = 1; si <= M; si++) {
			if (sharkPos[si].n != -1)sc1++;
		}
		if (sc1 == 1)break;//상어 한마리 남은 경우
	}
	if (ret == 1001)ret = -1;//4. 1000이 넘은 경우에도 상어 1마리가 아니면 -1를 출력
}
int main(void) {
	int T = 1;//테스트케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기입력
		playGame();
		printf("%d\n", ret);//printf("#%d %d\n", tc, ret);
	}
	return 0;
}