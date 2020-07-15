#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define BOARD_SIZE 31
int N, M;//��, �� ũ��
int pointCnt = 0;//���� ����
char Board[BOARD_SIZE][BOARD_SIZE];//������ 
int visit[BOARD_SIZE][BOARD_SIZE];//�湮Ȯ��
//int pointChk = 0;//���� ���� üũ ����
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int cMin = 0x7fffffff;//���� ������ġ�� �ּҰ�
int fMin = 0x7fffffff;//������ ���� �ּҰ�
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x, int cnt, int dir, int mainC) {
	//if (pointCnt == pointChk) {//���� �ٵ��Ҵٸ�
	//	cMin = cMin > cnt ? cnt : cMin;
	//	return;
	//}
	//int ny = y + dy[dir]; int nx = x + dx[dir];
	//if (!safe(ny, nx) || visit[ny][nx] == 1||Board[ny][nx]=='*') {//���� ��ȯ�ؾ��ϴ� �����
	//	for (int d = 0; d < 4; d++) {//���� �ٲ��ֱ�
	//		if (dir == d)continue;
	//		if (safe(y + dy[d], x + dx[d]) && visit[y+dy[d]][x+dx[d]] == 0 && Board[y+dy[d]][x+dx[d]] =='.') {
	//			visit[y + dy[d]][x + dx[d]] = 1;
	//			dfs(y + dy[d], x + dx[d], d, cnt + 1, pointChk+1);//���� ���� ���� ��Ű�� �ѱ��
	//			visit[y + dy[d]][x + dx[d]] = 0;//��Ʈ��ŷ �Ǹ� �� ���� ���·� ���� 
	//		}
	//	}
	//}
	//else if(safe(ny,nx)&&visit[ny][nx]==0&Board[ny][nx]=='.') {
	//	visit[ny][nx] = 1;
	//	dfs(ny, nx, dir, cnt,pointChk+1);//�׳� �Ѱ��ֱ�
	//	visit[ny][nx] = 0;//��Ʈ��ŷ �Ǹ� �� ���� ���·� ���� 
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
			if (Board[i][j] == '.') {//������ġ ã��
				for (int dir = 0; dir < 4; dir++) {//�׹��� ������� �ֱ�
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
		if (0x7fffffff == fMin)fMin = -1;//������ -1
		if (pointCnt == 1)fMin = 0;
		printf("Case %d: %d\n", t, fMin);
		init1();
		
	}
}
int main(void) {
		init();
		return 0;
}