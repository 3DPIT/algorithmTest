#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define NSIZE 50
int tunnel[NSIZE][NSIZE];//�ͳ��� �����Է� �迭
int visitT[NSIZE][NSIZE];//�ͳ��� �̵���� üũ �迭
int N, M, R, C, L;//����, ����, ������ ����, ������ ����, �ð�
int ret;//����� �Է�
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
//����ü ������
struct Data {//������ �̵���� ť�� �� ������
	int y, x, cnt;//��ǥ�� ���� �ð�
};
void init() {//������ �ʱ�ȭ
	N = M = R = C = L = ret;
	memset(tunnel, 0, sizeof(tunnel));
	memset(visitT, 0, sizeof(visitT));
}
bool dirNum(int dir, Data n) {//����  �ִ� ��ġ��� true,  �ƴϸ� false ��ȯ
	if (dir == 0 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 2 || tunnel[n.y][n.x] == 5 || tunnel[n.y][n.x] == 6)) {
		return 1;
	}
	if (dir == 1 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 3 || tunnel[n.y][n.x] == 6 || tunnel[n.y][n.x] == 7)) {
		return 1;
	}
	if (dir == 2 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 2 || tunnel[n.y][n.x] == 4 || tunnel[n.y][n.x] == 7)) {
		return 1;
	}
	if (dir == 3 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 3 || tunnel[n.y][n.x] == 4 || tunnel[n.y][n.x] == 5)) {
		return 1;
	}
	return 0;
}
void running() {
	queue<Data>q;//ť ����
	q.push({ R,C,0 });//ť Ǫ��
	visitT[R][C] = 1;//ť �湮 üũ
	ret = 1;//���� ������ ���� �� �ִ� ��ġ�� ����
	while (!q.empty()) {//ť�� �������� ����
		Data c = q.front(); q.pop();
		if (c.cnt == L - 1)break;//L���� �ð��Ǹ� ����
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = c.y + dy[dir]; n.x = c.x + dx[dir];// ������ġ �ε���
			n.cnt = c.cnt + 1;//�ð� ����
			if (tunnel[c.y][c.x] == 1 && visitT[n.y][n.x] == 0) {//������ ��ġ�� 1�� �������϶� ���� ��ġ�� 1,2,5,6�ε� �湮 ���� ���
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 2 && visitT[n.y][n.x] == 0 && (dir == 0 || dir == 2)) {
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 3 && visitT[n.y][n.x] == 0 && (dir == 1 || dir == 3)) {
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 4 && visitT[n.y][n.x] == 0 && (dir == 0 || dir == 1)) {
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 5 && visitT[n.y][n.x] == 0 && (dir == 1 || dir == 2)) {
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 6 && visitT[n.y][n.x] == 0 && (dir == 2 || dir == 3)) {
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 7 && visitT[n.y][n.x] == 0 && (dir == 0 || dir == 3)) {
				if (dirNum(dir, n)) {
					ret++;//������ ��ġ ����
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
		}
	}
}
int main(void) {
	int T;//�׽�Ʈ���̽� ����
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		//�Է°� �Է�
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &tunnel[i][j]);
			}
		}
		running();//������ �̵�
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}