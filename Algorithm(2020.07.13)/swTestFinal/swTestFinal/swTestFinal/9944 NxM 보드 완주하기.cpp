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
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int cMin = 0x7fffffff;//현재 보드위치의 최소값
int fMin = 0x7fffffff;//마지막 최종 최소값
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x, int cnt, int dir, int mainC) {
	//if (pointCnt == pointChk) {//전부 다돌았다면
	//	cMin = cMin > cnt ? cnt : cMin;
	//	return;
	//}
	//int ny = y + dy[dir]; int nx = x + dx[dir];
	//if (!safe(ny, nx) || visit[ny][nx] == 1||Board[ny][nx]=='*') {//방향 전환해야하는 경우라면
	//	for (int d = 0; d < 4; d++) {//방향 바꿔주기
	//		if (dir == d)continue;
	//		if (safe(y + dy[d], x + dx[d]) && visit[y+dy[d]][x+dx[d]] == 0 && Board[y+dy[d]][x+dx[d]] =='.') {
	//			visit[y + dy[d]][x + dx[d]] = 1;
	//			dfs(y + dy[d], x + dx[d], d, cnt + 1, pointChk+1);//방향 갯수 증가 시키고 넘기기
	//			visit[y + dy[d]][x + dx[d]] = 0;//백트래킹 되면 값 이전 상태로 변경 
	//		}
	//	}
	//}
	//else if(safe(ny,nx)&&visit[ny][nx]==0&Board[ny][nx]=='.') {
	//	visit[ny][nx] = 1;
	//	dfs(ny, nx, dir, cnt,pointChk+1);//그냥 넘겨주기
	//	visit[ny][nx] = 0;//백트래킹 되면 값 이전 상태로 변경 
	//}
	if (cnt == pointCnt) {
		if (cMin > mainC)cMin = mainC;
		return;
	}
	int ny = y + dy[dir];
	int nx = x + dx[dir];
	if (safe(ny, nx) && Board[ny][nx] == '.'&&visit[ny][nx] == 0) {
		visit[ny][nx] = 1;
		dfs(ny, nx, cnt + 1, dir, mainC);
		visit[ny][nx] = 0;
	}
	else {
		for (int dir1 = 0; dir1 < 4; dir1++) {
			if (dir == dir1)continue;
			int ny1 = y + dy[dir1];
			int nx1 = x + dx[dir1];
			if (safe(ny1, nx1) && Board[ny1][nx1] == '.'&&visit[ny1][nx1] == 0) {
				visit[ny1][nx1] = 1;
				dfs(ny1, nx1, cnt + 1, dir1, mainC + 1);
				visit[ny1][nx1] = 0;
			}
		}
	}
}
void testPlay() {
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if (Board[i][j] == '.') {//시작위치 찾고
				for (int dir = 0; dir < 4; dir++) {//네방향 순서대로 넣기
					visit[i][j] = 1;
					dfs(i, j, 1,dir,1);
					visit[i][j] = 0;
					fMin = fMin > cMin ? cMin : fMin;
					memset(visit, 0, sizeof(visit));
				}
			}
		}
	}
}
void init1() {
	N = M = pointCnt = 0;
	cMin=fMin = 0x7fffffff;
	memset(Board, 0, sizeof(Board));
	memset(visit, 0, sizeof(visit));
}
void init() {
	int t = 0;
	while (cin >> N >> M) {
		t++;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf(" %1c", &Board[i][j]);
				if (Board[i][j] == '.') {
					pointCnt++;
				}
			}
		}
		testPlay();
		if (0x7fffffff == fMin)fMin = -1;//못가면 -1
		if (pointCnt == 1)fMin = 0;
		printf("Case %d: %d\n", t, fMin);
		init1();
		
	}
}
int main(void) {
		init();
		return 0;
}