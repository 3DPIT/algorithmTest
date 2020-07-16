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
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int cMin = 0x7fffffff;//���� ������ġ�� �ּҰ�
int fMin = 0x7fffffff;//������ ���� �ּҰ�
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x, int dir, int cnt, int pointChk) {// ���� y��ǥ,x��ǥ, ����,������ȯ��
	if (pointCnt == pointChk) {//���� �ٵ��Ҵٸ�
		cMin = cMin > cnt ? cnt : cMin;
		return;
	}
	int ny = y + dy[dir]; int nx = x + dx[dir];
	if (!safe(ny, nx) || visit[ny][nx] == 1 || Board[ny][nx] == '*') {//���� ��ȯ�ؾ��ϴ� �����
		for (int d = 0; d < 4; d++) {//���� �ٲ��ֱ�
			if (dir == d)continue;
			if (safe(y + dy[d], x + dx[d]) && visit[y + dy[d]][x + dx[d]] == 0 && Board[y + dy[d]][x + dx[d]] == '.') {
				visit[y + dy[d]][x + dx[d]] = 1;
				pointChk++;
				dfs(y + dy[d], x + dx[d], d, cnt + 1, pointChk);//���� ���� ���� ��Ű�� �ѱ��
				pointChk--;
				visit[y + dy[d]][x + dx[d]] = 0;//��Ʈ��ŷ �Ǹ� �� ���� ���·� ���� 
			}
		}
	}
	else if (safe(ny, nx) && visit[ny][nx] == 0 & Board[ny][nx] == '.') {
		visit[ny][nx] = 1;
		pointChk++;
		dfs(ny, nx, dir, cnt, pointChk);//�׳� �Ѱ��ֱ�
		pointChk--;
		visit[ny][nx] = 0;//��Ʈ��ŷ �Ǹ� �� ���� ���·� ���� 
	}
}
void testPlay() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Board[i][j] == '.') {//������ġ ã��
				for (int dir = 0; dir < 4; dir++) {//�׹��� ������� �ֱ�
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
				if (Board[i][j] == '.') {//���� ���� ���°�
					pointCnt++;
				}
			}
		}
		testPlay();
		c++;
		if (0x7fffffff == fMin)fMin = -1;//������ -1
		if (pointCnt == 1)fMin = 0;
		printf("Case %d: %d\n", c, fMin);
		cMin = fMin = 0x7fffffff;
		N = M = pointCnt = 0;//�ʱ�ȭ
	}
}
int main(void) {
	init();
	return 0;
}