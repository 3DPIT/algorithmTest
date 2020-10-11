#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
#define NMS 16//���� ���� �ִ� ũ��
int N, M, D;//����, ����, �Ÿ�
int C[NMS+1][NMS];//ĳ��
int ret;//����� ����
struct Data {
	int y, x;
};
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = D = 0;
	ret = 0x80000000;//�ִ밪
	//�ʱ� �Է�
	scanf("%d %d %d", &N, &M, &D);//���� , ����, �Ÿ� �Է�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &C[i][j]);//�迭 ���� ���� �Է�
		}
	}
}
void copy(int c[NMS][NMS], int cc[NMS][NMS]) {//�迭 ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			c[i][j] = cc[i][j];
		}
	}
}
void downEnemy() {//�� ���� �ϱ�
	for (int y = N - 1; y >= 1; y--) {
		for (int x = 0; x < M; x++) {
			C[y][x] = C[y - 1][x];//��ĭ ������
		}
	}
	for (int x = 0; x < M; x++) {//��ĭ ����ֱ�
		C[0][x] = 0;
	}
}

//1. �ü� ��ġ ã��
void dfs(int idx, int cnt) {
	if (idx == M+1)return;
	if (cnt == 3) {//�ü� ��ġ ���� �Ϸ�
		int cC[NMS][NMS] = { 0, };//���� �迭
		copy(cC, C);//�迭 ���
		int enemy = 0;//���� ���� ��
		Data sniper[3]; int sIdx = 0;
		for (int j = 0; j < M; j++) {
			if (C[N][j] == 1) {//�������� ��ġ ����
				sniper[sIdx].y = N; sniper[sIdx++].x = j;
			}
		}
		for (int time = 0; time < N; time++) {//���� �����ϴ� ��
			queue<Data>enemyDie;//���� �� ����
			for (int s = 0; s < sIdx; s++) {//�������� �Ѹ� �� �����ϱ�
				int minD = 0x7fffffff; int minY = 0x7fffffff; int minX = 0x7fffffff;//�ּ� �Ÿ��� ������ ��ǥ

				for (int y = N - 1; y >= 0; y--) {
					for (int x = 0; x < M; x++) {
						if (C[y][x] != 0) {
							//2. D�ȿ� ������ ���� ���� �ִ� ��ã��
							int distance = abs(y - sniper[s].y) + abs(x - sniper[s].x);
							if (distance <= D) {//���� �ȿ� �ִ°Ŷ�� ã�°� ����
								if (minD >=distance){
									if (minD == distance&&minX>x) {
										minY = y; minX = x;
									}
									else if(minD>distance){
										minD = distance;
										minY = y; minX = x;
									}
								}
							}
						}
					}
				}
				if (minD != 0x7fffffff&&minY!=0x7fffffff&&minX!=0x7fffffff) {
					enemyDie.push({ minY, minX });
				}
			}
			//3. �þ߿� ���� �� ���̱�
			while (!enemyDie.empty()) {
				Data c = enemyDie.front(); enemyDie.pop();
				if (1 == C[c.y][c.x]) {//���� ���̸� ���̰� cnt ++
					C[c.y][c.x] = 0; enemy++;
				}
			}
			//4. �迭 ������
			downEnemy();
		}
		// 5. ������ �� ���������� ���� ���� �ִ밪 �����ϱ�
		copy(C, cC);//�迭 ����
		ret = max(ret, enemy);//�ִ밪 ����
		return;
	}
	C[N][idx] = 1;
	dfs(idx + 1, cnt + 1);//�ü� ���� ���
	C[N][idx] = 0;
	dfs(idx + 1, cnt);//�ü� �Ȼ��� ���

}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);//�׽�Ʈ ���̽� �Է�
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		dfs(0, 0);
		//���
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}