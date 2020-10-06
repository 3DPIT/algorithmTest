#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>	
using namespace std;
#define NSIZE 21
int soil[NSIZE][NSIZE];//���� ��ġ�ϴ� �迭
int N, M;//���� ũ��� ������ ���
int ret = 0x80000000;//�ִ밪
void init() {//���� �ʱ�ȭ
	N = M = 0;
	ret = 0x80000000;
	memset(soil, 0, sizeof(soil));
}
void searchHome() {//���� �� Ž��
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {//���� ��ġ �Է� ( �� : 1 )
		for (int j = 0; j < N; j++) {
			scanf("%d", &soil[i][j]);
		}//for j
	}// for i
	for (int cy = 0; cy < N; cy++) {//���� Ȯ�� ��ġ ����
		for (int cx = 0; cx < N; cx++) {
			int D[NSIZE*NSIZE] = { 0, };//���� ���� ���
			int maxDistance = 0x80000000;
			for (int hy = 0; hy < N; hy++) {// ���� ��ġ 
				for (int hx = 0; hx < N; hx++) {
					if (soil[hy][hx] == 1) {//���̶�� �Ÿ� �����ϱ�
						int distance = abs(cy - hy) + abs(cx - hx);//�Ÿ� ����
						D[distance+1]++;
						maxDistance = max(maxDistance, distance + 1);//�ִ� �Ÿ���
					}
				}//for hx
			}//for hy
			
			//����ȸ���� ����(2) = ���� �����޴� ������ ���� ��� ����(3*5) - � ���(13)
			int home = 0;//���� ��
			for (int k = 1; k <= maxDistance;k++) {
				int manageCost=(k*k)+((k-1)*(k-1));//� ���
				//printf("k = %d , manageCost = %d\n", k, manageCost);//� ��� Ȯ��
				home += D[k];//���� ��
				int serviceHome = 0; 
				serviceHome = M * home;//���� �����޴� ������ ���� ��� ����
				int securityProfit = serviceHome - manageCost;//����ȸ���� ����
				if (securityProfit >=0) {//���ذ� �ƴϸ� �ΰ��� �ִ��
 					ret = max(ret, home);//���� �ִ��� ���� ���� ���� 
				}
			}

		}//for cx
	}//for cy 
}
int main(void) {
	int T;//�׽�Ʈ ���̽� ����
	scanf("%d",&T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		searchHome();
		printf("#%d %d\n", tc, ret);//���� ��� ����
	}
	return 0;
}