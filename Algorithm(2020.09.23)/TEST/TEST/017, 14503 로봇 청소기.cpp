#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NMSIZE 50 //���ο� ������ �ִ� ũ��
int N, M;//����ũ��, ����ũ��
int ret;//������ �����
int rY, rX, rDir;//�κ��� ���� ��ġ�� ����
int square[NMSIZE][NMSIZE];//�ʱ� �Է¹迭
int dy[] = { -1,0,1,0 };//��, �� ,��, ��
int dx[] = { 0,1,0,-1 };
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ 
	ret = 1;//���� 1�̱� ������ �����ϱ� ���ؼ�
	N = M = 0;
	rY = rX = rDir = 0;
	memset(square, 0, sizeof(square));
	//�ʱ� �Է�
	scanf("%d %d", &N, &M);//���� ���� ũ�� �Է�
	scanf("%d %d %d", &rY, &rX, &rDir);//�κ��� ���� ��ǥ�� ����
	for (int y = 0; y < N; y++) {//�ʱ� �Է°� �迭 ����
		for (int x = 0; x < M; x++) {
			scanf("%d", &square[y][x]);
		}
	}
}
void cleanRoom() {
	//0�� ��ĭ 1�� �� 2�̻��� û���ѱ��� 
	while (1) {
		//���� ��ġ�� û���Ѵ�.
		if (square[rY][rX] == 0) {
			square[rY][rX] = ++ret;
		}
		//���� ��ġ���� ���� ������ �������� ���ʹ������ ���ʴ�� Ž���� �����Ѵ�.
		int num = 0;
		int dir = rDir;
		for (num = 0; num < 4; num++) {//�׹��� �˻�
			dir=(4+(--dir))%4;
			int ny = rY + dy[dir]; int nx = rX + dx[dir];//���� ���� �˻�
			//���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�, �� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ �����Ѵ�.
			if (square[ny][nx] == 0) {
				rY = ny; rX = nx;//��ĭ �̵� ��Ű��
				rDir = dir;//���� �����ְ�
				break;
			}
			//���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ ���ư���.
			
		}
		if (num == 4) {//�׹��� ��� û�Ұ� �Ǿ��ִ� ���
			//�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ��쿡��, �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư���.
			int ny = rY - dy[rDir]; int nx = rX - dx[rDir];//�ڹ��� 
			if (square[ny][nx] !=1) {//������̶��
				rY = ny; rX = nx;//�̵��Ѱɷ� �ֽ�ȭ
			}
			//�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���̸鼭, ���� ������ ���̶� ������ �� �� ���� ��쿡�� �۵��� �����.
			else if (square[ny][nx] != 0) {//���ΰ�쳪 û���� �����̶��
				return;//û�� ����
			}
		}
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//�ʱ�ȭ �� �ʱ� �Է�
		init_input();
		cleanRoom();//�κ� û�ұ� û�� ����
		//����� ���
		printf("%d\n", ret-1);
		//printf("#%d %d\n", tc, ret-1);
	}
	return 0;
}