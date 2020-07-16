#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define MAP_SIZE 16 //���ִ� ������
int N, M, D;//��, ��, �Ÿ�
int castleMap[MAP_SIZE][MAP_SIZE];//����� ��
int copyCastleMap[MAP_SIZE][MAP_SIZE];//������ ��
int Max = 0x80000000;
void print(int pArr[MAP_SIZE][MAP_SIZE]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << pArr[i][j];
		}
		cout << endl;
	}
}
struct Data {
	int y, x;
};
void copy(int carr[MAP_SIZE][MAP_SIZE], int arr[MAP_SIZE][MAP_SIZE]) {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			carr[i][j] = arr[i][j];
		}
	}
}
void downArr() {
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			copyCastleMap[i + 1][j] = copyCastleMap[i][j];//��ĭ�� ��������
		}
	}
	for (int j = 0; j < M; j++) {//���� ���� 0���� �ʱ�ȭ 
		copyCastleMap[0][j] = 0;
	}
}
int emermyDie() {
	int enermyNum = 0;
	int MaxDownN = N;
	copy(copyCastleMap, castleMap);
	int cnt = 0;//�ü� 3������ üũ
	while (MaxDownN--) {//������ �����ִ��
		vector<Data>Die;
		for (int i = 0; i < M; i++) {//�ü� ã��
			if (copyCastleMap[N][i] == 2) {//�ü� ã������ ���� �� ã��
				
				int hunterY = N;// �ü��� y,x ��ǥ 
				int hunterX = i;
				int minD = 0x7fffffff;//���� ���� �Ÿ� �ּҰ�
				int minY = 0x7fffffff;
				int minX = 0x7fffffff;				
				for (int y = 0; y < N; y++) {
					for (int x = 0; x < M; x++) {
						if (copyCastleMap[y][x] == 1) {// ���� ã������
							int d = abs(hunterY - y) + abs(hunterX - x);
							//if (d <= D) {
							//	if (minD > d) {//�ּҹ����� ���̸� �׶��� y,x �����ϱ�����
							//		minD = d;
							//		minY = y;
							//		minX = x;
							//	}
							//	if (minD == d) {
							//		if (minX > x) {
							//			minD = d;
							//			minY = y;
							//			minX = x;
							//		}
							//	}
							//}//
							if (d <= D) {
								if (minD > d || (minD == d && minX > x)) {
									minD = d;
									minY = y;
									minX = x;
								}
							}
						}
					}
				}
				if (minY != 0x7fffffff) {//���� ���� �־�����
					Die.push_back({ minY,minX });
				}
				else {
					Die.push_back({ -1,-1 });
				}
			}
		}
		//�����̱�
		for (int i = 0; i < 3; i++) {
			if (Die.size()!=0&&Die[i].y!=-1&&copyCastleMap[Die[i].y][Die[i].x] == 1) {
				copyCastleMap[Die[i].y][Die[i].x] = 0;
				enermyNum++;
			}
		}
		//Die.clear();//�� ��ġ �ʱ�ȭ
		//cout << "���� ��" << endl;
		//cout << enermyNum << endl;
		//cout << "�� ������" << endl;
		//print(copyCastleMap);
		//�迭������
		downArr();
		//cout << "�迭 ������" << endl;
		//print(copyCastleMap);
	}
	return enermyNum;
}
void dfs(int idx, int d) {
	if (d == 3) {//�ü� ��ġ ���� �� �ù� ����

		int num = emermyDie();//���� ��ġ���� �ִ� ���� ����
		Max = Max < num ? num : Max;//���� �ִ����μ� ����Ǵ� ����
		return;
	}
	for (int i = idx; i < M; i++) {
		castleMap[N][i] = 2;//�ü� ��ġ ���
		dfs(i + 1, d + 1);
		castleMap[N][i] = 0;
	}

}
void init() {
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {//�ʿ� ����ġ ǥ��
		for (int j = 0; j < M; j++) {
			scanf("%d", &castleMap[i][j]);
		}
	}
	dfs(0, 0);//�ü���ġ ����
}
int main(void) {
	init();
	cout << Max << endl;

}
