#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
#define NMS 500//N��M�� �ִ� ũ��
int N, M;//����ũ�� , ���� ũ��
int ret;//���� �ִ밪
int B[NMS][NMS];//������ �ʱ��Է�
int cB[NMS][NMS];//��Ʈ�ι̳� ������ �迭
int dy[] = {0,1,0,-1};
int dx[] = {1,0,-1,0};
void printArr(int A[NMS][NMS]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d", A[i][j]);
		}
		printf("\n");
	}
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = 0;
	ret = 0x80000000;
	memset(B, 0, sizeof(B));
	memset(cB, 0, sizeof(cB));
	//�ʱ� �Է�
	scanf("%d %d", &N, &M);//���� ���� ũ�� �Է�
	for (int i = 0; i < N; i++) {//�ʱ� �迭�� �Է�
		for (int j = 0; j < M; j++) {
			scanf("%d", &B[i][j]);
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void dfs(int y, int x, int cnt,int sum) {
	if (cnt == 3) {//������ ��Ʈ���� ���
		ret = max(ret, sum);
		return;
	}

	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (safe(ny, nx) && cB[ny][nx] == 0) {
			cB[ny][nx] = 1;
			sum += B[ny][nx];
			dfs(ny, nx, cnt + 1,sum);
			sum -= B[ny][nx];
			cB[ny][nx] = 0;
		}
	}
}
void dfs1(int y, int x, int cnt,int dir, int sum) {//��� ->�ΰ��
	if (cnt == 2) {
		ret = max(ret, sum);
		return;
	}
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (safe(ny, nx) && cB[ny][nx] == 0) {//��� �κп� �߰��ؼ� ���
			if (cnt == 1) {
				int cdir = dir;
				cdir=(++cdir)%4;
				int cny = y + dy[cdir]; int cnx = x + dx[cdir];
				if (safe(cny, cnx)) {
					sum += B[ny][nx];
					sum += B[cny][cnx];
					cB[ny][nx] = 1;
					cB[cny][cnx] = 1;
					dfs1(ny, nx, cnt + 1, dir, sum);
					cB[cny][cnx] = 0;
					sum -= B[ny][nx];
					sum -= B[cny][cnx];
					cB[ny][nx] = 0;
				}
				else return;

			}
			else {
				cB[ny][nx] = 1;
				sum += B[ny][nx];
				dfs1(ny, nx, cnt + 1,dir, sum);
				sum -= B[ny][nx];
				cB[ny][nx] = 0;
			}
		}
}
void gameStart() {//���� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cB[i][j] = 1;
			dfs(i, j, 0,B[i][j]);//�迭�� ����y,x,cnt;
			for (int dir = 0; dir < 4; dir++) {
				dfs1(i, j, 0, dir, B[i][j]);
			}
			cB[i][j] = 0;
		}
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//�ʱ�ȭ �� �ʱ� �Է�
		init_input();
		gameStart();//���� ����
		//��°�
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}