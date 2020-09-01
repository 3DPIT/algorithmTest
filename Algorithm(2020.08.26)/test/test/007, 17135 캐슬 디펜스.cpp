#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
#define N_SIZE 16
#define M_SIZE 16
int N, M, D;//�迭ũ�� y x,���ϼ� �ִ� �� �Ÿ�
int castle[N_SIZE][M_SIZE];//�Է� �迭
int ret;//�ִ� �� ����
struct Data {
	int y, x;
}dieArr[3];
void init() {
	//�ʱ�ȭ
	memset(castle, 0, sizeof(castle));
	N = M = D = 0;
	ret = 0x80000000;
	//�Է�
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &castle[i][j]);//���� ���� �Է� 
		}
	}
}
void downArr() {
	for (int i = N-1; i >=1; i--) {//�迭 ������
		for (int j = 0; j < M; j++) {
			castle[i][j] = castle[i-1][j];
		}
	}
	for (int j = 0; j < M; j++) {//���� ���� 0���� �ʱ�ȭ
		castle[0][j] = 0;
	}
}
void copy(int Ccastle[N_SIZE][M_SIZE],int castle[N_SIZE][M_SIZE]) {//�迭 ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Ccastle[i][j] = castle[i][j];
		}
	}
}
int playGame() {
	int cnt = 0;
	int Ccastle[N_SIZE][M_SIZE] = { 0, };
	copy(Ccastle, castle);
	for (int k = 0; k < N; k++) {
		memset(dieArr, 0, sizeof(dieArr));//�ʱ�ȭ
		int idx = 0;//���� ��ǥ �� �ε���
		for (int x = 0; x < M; x++) {// �ü��� ��ǥ ã������ �ݺ���
			int sY = N, sX = -1;// �ü��� ��ǥ �����ϴ� ���� 
			if (castle[N][x] == 0) continue;
			sX = x;//y���� N ���� �����̹Ƿ� x���� �����ϸ��		
			int minD, minY, minX;
			minD = minY = minX = 0x7fffffff;//�ּ��� D���̰� y�� ���ϱ� ���� ����
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (castle[i][j] == 1) {//���߽߰�
						int distance = abs(N - i) + abs(sX - j);
						if (distance <= D) {//���� ���� �� �ִ� ����
							if (minD >= distance) {
								if (minD > distance || (minD == distance && minX > j)) {
									minD = distance;
									minY = i;
									minX = j;
								}
							}
						}//�Ÿ� �� if��
					}
				}
			}//ó�� ������

			if (minD != 0x7fffffff) {//���� ���� �ִٸ� �����Ű��
				dieArr[idx].y = minY; dieArr[idx++].x = minX;
			}
		}
		for (int dieI = 0; dieI < idx; dieI++) {
			if (castle[dieArr[dieI].y][dieArr[dieI].x] == 1) {
				castle[dieArr[dieI].y][dieArr[dieI].x] = 0;
				cnt++;//�����̰� ����
			}
		}
		downArr();
	}//N�� �� ������
	copy(castle, Ccastle);
	return cnt;//���� �� ������
}
void dfs(int idx, int d) {
	if (idx > M)return;// �ε��� �Ѿ�� ����
	if (d == 3) {//�ü� ��ġ �����ϸ� ���°�
		int die = playGame();
		ret = ret < die ? die : ret;//�ִ밪 ����
		return;
	}

	castle[N][idx] = 1;//�ü� ��ġ �����ϱ�
	dfs(idx + 1, d + 1);//�ü� �̴� ���
	castle[N][idx]=0;
	dfs(idx + 1, d);//�ü� �Ȼ̰� �ε��� �ø��°��
}

int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0, 0);
		//printf("#%d %d\n",tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}