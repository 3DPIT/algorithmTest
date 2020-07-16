#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define BOARD_SIZE 31
int N, M;//행, 열 크기
int pointCnt = 0;//점의 갯수
char Board[BOARD_SIZE][BOARD_SIZE];//보드판 
int visit[BOARD_SIZE][BOARD_SIZE];//방문확인
//int pointChk = 0;//점의 갯수 체크 갯수
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int cMin = 0x7fffffff;//현재 보드위치의 최소값
int fMin = 0x7fffffff;//마지막 최종 최소값
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x, int dir, int cnt, int pointChk) {// 맵의 y좌표,x좌표, 방향,방향전환수
	if (pointCnt == pointChk) {//전부 다돌았다면
		cMin = cMin > cnt ? cnt : cMin;
		return;
	}
	int ny = y + dy[dir]; int nx = x + dx[dir];
	if (!safe(ny, nx) || visit[ny][nx] == 1 || Board[ny][nx] == '*') {//방향 전환해야하는 경우라면
		for (int d = 0; d < 4; d++) {//방향 바꿔주기
			if (dir == d)continue;
			if (safe(y + dy[d], x + dx[d]) && visit[y + dy[d]][x + dx[d]] == 0 && Board[y + dy[d]][x + dx[d]] == '.') {
				visit[y + dy[d]][x + dx[d]] = 1;
				pointChk++;
				dfs(y + dy[d], x + dx[d], d, cnt + 1, pointChk);//방향 갯수 증가 시키고 넘기기
				pointChk--;
				visit[y + dy[d]][x + dx[d]] = 0;//백트래킹 되면 값 이전 상태로 변경 
			}
		}
	}
	else if (safe(ny, nx) && visit[ny][nx] == 0 & Board[ny][nx] == '.') {
		visit[ny][nx] = 1;
		pointChk++;
		dfs(ny, nx, dir, cnt, pointChk);//그냥 넘겨주기
		pointChk--;
		visit[ny][nx] = 0;//백트래킹 되면 값 이전 상태로 변경 
	}
}
void testPlay() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Board[i][j] == '.') {//시작위치 찾고
				for (int dir = 0; dir < 4; dir++) {//네방향 순서대로 넣기
					visit[i][j] = 1;
					dfs(i, j, dir, 1, 1);
					fMin = fMin > cMin ? cMin : fMin;
					memset(visit, 0, sizeof(visit));
					visit[i][j] = 0;

				}
			}
		}
	}
}
void init() {
	int c = 0;
	while (cin >> N >> M) {
		memset(Board, 0, sizeof(Board));
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf(" %1c", &Board[i][j]);
				if (Board[i][j] == '.') {//점의 갯수 세는곳
					pointCnt++;
				}
			}
		}
		testPlay();
		c++;
		if (0x7fffffff == fMin)fMin = -1;//못가면 -1
		if (pointCnt == 1)fMin = 0;
		printf("Case %d: %d\n", c, fMin);
		cMin = fMin = 0x7fffffff;
		N = M = pointCnt = 0;//초기화
	}
}
int main(void) {
	init();
	return 0;
}