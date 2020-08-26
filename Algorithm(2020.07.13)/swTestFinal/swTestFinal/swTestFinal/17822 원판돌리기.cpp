#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define N_SIZE 52
#define M_SIZE 52
int N, M, T;//y��,x��,�׽�Ʈ�� ����
int cycleInput[N_SIZE][M_SIZE];// �� �Է� �迭
int visit[N_SIZE][M_SIZE];//dfs �湮üũ �迭
int ret;// ������ ����
int dy[] = { 0,1,0,-1 };//���� y
int dx[] = { 1,0,-1,0 };//���� x
int cM;
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void init() {
	// �ʱ�ȭ �ϴ� ��ġ
	memset(cycleInput, 0, sizeof(cycleInput));
	memset(visit, 0, sizeof(visit));
	N = M = T = ret = 0;
	scanf("%d %d %d", &N, &M, &T);
	 cM = M;
	for (int i = 0; i < N; i++) {// ������ �Է�
		for (int j = 0; j < M; j++) {
			scanf("%d", &cycleInput[i][j]);
		}
	}
}
//���� ����
void clockRotaion(int idx, int cnt, int d) {
	//�ð���� ������ �Լ�
	if (d == 0) {
		for (int c = 0; c < cnt; c++) {
			int lastNum = cycleInput[idx][M - 1];// ���� ����
			for (int i = M - 2; i >= 0; i--) {
				cycleInput[idx][i + 1] = cycleInput[idx][i];
			}
			cycleInput[idx][0] = lastNum;
		}
	}
	//�ݽð� ���� ������ �Լ�
	if (d == 1) {
		for (int c = 0; c < cnt; c++) {
			int firstNum = cycleInput[idx][0];//�� �հ� ����
			for (int i = 1; i < M; i++) {
				cycleInput[idx][i - 1] = cycleInput[idx][i];
			}
			cycleInput[idx][M - 1] = firstNum;
		}
	}
}
//dfs �Լ� ���� ���� �� ���ư���
bool flag = 0;// ���ŵǴ� �� �ִ��� Ȯ�� ����
void dfs(int y, int x,int num) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		// ���� �Ѿ�°� üũ
		if (nx == M) {
			nx = 0;
		}
		if (-1 == nx) {
			nx = M - 1;
		}
		//�湮 �� �� �� �ִ� ���� üũ
		if (safe(ny,nx)&&0==visit[ny][nx] && cycleInput[ny][nx] == num) {
			visit[ny][nx] = 1;//�湮üũ
			cycleInput[ny][nx] = 0;
			flag = 1;
			dfs(ny,nx,num);// dfs ������
		}
	}
}
//���� ���� ���ϸ� ��հ� ���ϴ� �Լ� 
void DFS() {
	memset(visit, 0, sizeof(visit));
	bool FLAG =1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (cycleInput[i][j]!=0
				&&visit[i][j] == 0) {
				dfs(i, j, cycleInput[i][j]);
				if (flag) {
					flag = 0;
					visit[i][j] = 1;
					cycleInput[i][j] = 0;
					FLAG = 0;//���ŵǴ°� �ִ��� Ȯ�� ����
				}
			}
		}
	}

	if (FLAG) {//���ŵǴ°� ������ ��հ� ���ϱ�
		int cnt = 0;//���� ���� ����
		int sum = 0;//���� �� 
		double avgSum = 0;
		for (int i = 0; i < N; i++) {//������ �հ� ���� ���ϴ� ��
			for (int j = 0; j < M; j++) {
				if (cycleInput[i][j] != 0) {
					sum += cycleInput[i][j];
					cnt++;
				}
			}
		}//
		avgSum = (double)sum / cnt;
		for (int i = 0; i < N; i++) {//��պ��� ũ�� -1. ������ +1
			for (int j = 0; j < M; j++) {
				if (cycleInput[i][j] != 0 && avgSum < cycleInput[i][j])// �������
				{
					cycleInput[i][j] -= 1;
				}
				else if (cycleInput[i][j] != 0 && avgSum > cycleInput[i][j])// ū���
				{
					cycleInput[i][j] += 1;
				}

			}
		}
	}//if(FLAG) ���κ�
}
void arrSum() {

}
void Rotation() {// �������� ���ư��鼭 ����ϴ°�
	for (int t = 1; t <= T; t++) {//����
		int x, d, k;
		scanf("%d %d %d", &x, &d, &k);//x���, d����(0: �ð�, 1: �ݽð�),k��ȸ��
		for (int i = 0; i < N; i++) {
			int X = i + 1;
			if (X%x == 0) {//x�� ������ 
				clockRotaion(i, k, d);//���� y��, ȸ����, ����
			}
		}
		DFS();
	}
	//�迭�� ���� �ձ��ϱ�
	arrSum();
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);//�׽�Ʈ ���̽� �Է�
	for (int tc = 1; tc <= testCase; tc++) {
		init();//�ʱ�ȭ �� �Է� 
		Rotation();
		//printf("#%d %d\n", tc, ret);// ���
		printf("%d\n", ret);
	}
	return 0;
}