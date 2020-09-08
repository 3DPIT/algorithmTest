#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
#define BOARD_SIZE 11//���� �ִ� ������
char board[BOARD_SIZE][BOARD_SIZE];
int visit[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];//�� ����ġ üũ
//�� �̵��� ���� ��,��,��,��
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, M;//���� ũ�� ���� ����
int ret;//����� ���� ����
void print(char m[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%c ", m[i][j]);
		}
		printf("\n");
	}
}
struct BallData {//���� ������ ������ ���� ����ü
	int ry, rx, by, bx, cnt;
}firstBall;
struct Data {
	int y, x;
};
int hy, hx;// Ȧ�� ��ġ
void init() {
	//�ʱ�ȭ
	N = M = 0; ret = 0x7fffffff;
	memset(board, 0, sizeof(board));
	memset(visit, 0, sizeof(visit));
	//����
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %1c", &board[i][j]);//�Է�
			if (board[i][j] == 'R') {
				firstBall.ry = i;//������ ��ġ ����
				firstBall.rx = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'B') {
				firstBall.by = i;//�Ķ��� ��ġ ����
				firstBall.bx = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'O') {
				hy = i; hx = j;//Ȧ�� ��ġ ����
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
	//ť�����ϰ� �ʱ� ���� �Ķ� ����ġ Ǫ��
	queue<BallData>q;
	q.push({ firstBall.ry,firstBall.rx,firstBall.by,firstBall.bx,0 });
	while (!q.empty()) {
		BallData  c = q.front(); q.pop();
		if ((c.ry == hy && c.rx == hx) || c.cnt == 11) {//������ ���� 
			if (c.cnt != 11)ret = c.cnt;//Ż�� ���� Ȧ��ġ�ų� 10ȸ�ʰ��Ȱ��
			break;
		}
		for (int dir = 0; dir < 4; dir++) {
			BallData n;
			Data R, B;
			R = ballMove(c.ry, c.rx, dir);//������ �̵�
			B = ballMove(c.by, c.bx, dir);//�Ķ��� �̵�
			if (R.y == B.y&&R.x == B.x&&board[R.y][R.x] == 'O') continue;//�ΰ��� Ȧ�� ���� ���

			int redD = abs(c.ry - R.y) + abs(c.rx - R.x);
			int blueD = abs(c.by - B.y) + abs(c.bx - B.x);
			if (R.y == B.y&&R.x == B.x) {//���� ��ġ�� �ִ°��
				if (redD < blueD) {//������ ���� ������ ���
					B.y -= dy[dir];//��ĭ �ڷ� �̵�
					B.x -= dx[dir];
				}
				else if (redD > blueD) {//�Ķ��� ���� ������ ���
					R.y -= dy[dir];//��ĭ �ڷ� �̵�
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
			if (visit[R.y][R.x][B.y][B.x] == 0) {//�ߺ� üũ
				visit[R.y][R.x][B.y][B.x] = 1;
				q.push({ R.y,R.x,B.y,B.x,c.cnt + 1 });
			}

		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);//�׽�Ʈ ���̽��Է�
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		BFS();
		if (0x7fffffff == ret)ret = -1;//�� ������ ���
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}