#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
#define MAXNM 10
#define NMSIZE 705
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int ret;
int N, M, K, X;//����, ����, �ð�, �����
int board[NMSIZE][NMSIZE];//�Է� ��
int visit[NMSIZE][NMSIZE];// ť �迭 üũ
struct Data {
	int y, x, num,active,life;
};
queue<Data>q[11];//ť�迭
void init() {
	//�ʱ�ȭ
	N = M = ret = 0;
	memset(board, 0, sizeof(board));
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < 11; i++) { while (!q[i].empty())q[i].pop(); }//ť�ʱ�ȭ
	//�Է�
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 350; i < N + 350; i++) {
		for (int j = 350; j < M + 350; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j] != 0) {
				visit[i][j] = 1;
				q[board[i][j]].push({ i,j,board[i][j],board[i][j],board[i][j] });//����, �����
			}
		}
	}
}
void play() {
	while (K--) {//K�Ⱓ ����
		for (int i = 10; i >= 1; i--) {
			int size = q[i].size();
			if (size == 0)continue;//ť üũ
			queue<Data>q1;//ť ����
			while (size--) {//���� ť ��ŭ ������
			
				Data c = q[i].front(); q[i].pop();
				if(c.active!=0)c.active--;
				else {
					Data n;
					for (int dir = 0; dir < 4; dir++) {
						n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
						if (visit[n.y][n.x] == 0 && board[n.y][n.x] == 0) {
							board[n.y][n.x] = c.num;
							n.life = c.num;
							n.active = c.num;
							n.num = c.num;
							visit[n.y][n.x] = c.num;// �迭 üũ
							q1.push(n);
						}
					}
					c.life--;
				}
				if (c.life >= 1) {//�� �̿��� ���
					q1.push(c);
				}
			}
			while (!q1.empty()) {//�� ����
				q[i].push(q1.front()); q1.pop();
			}
		}

	}
	for (int i = 1; i <= 10; i++) {
		ret += q[i].size();
	}
}
int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		play();
		printf("#%d %d\n", test_case, ret);
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}
