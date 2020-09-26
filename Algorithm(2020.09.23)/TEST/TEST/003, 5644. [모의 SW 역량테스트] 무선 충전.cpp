#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define MSIZE 105
#define ASIZE 10
struct Data {
	int Y, X, C, P;//������ ��ġ�� Y,X, ��������, ����
}BC[ASIZE];
int BCidx = 0;
int userMap[2][MSIZE];//�������� ��� ���� �迭
int dy[] = { 0,-1,0,1,0 };//�̵� ����, ��, ��, ��, ��
int dx[] = { 0,0,1,0,-1 };
int M, A;//���̵��ð�, BC�� ����
int ret;//����� ����
int user0Y,user0X,user1Y,user1X;//������ �ʱ� ��ġ
vector<int>u1; vector<int>u2;//���� BC���� Ȯ��
void init() {
	//�ʱ�ȭ
	u1.clear(), u2.clear();
	user0Y = 1, user0X = 1, user1Y = 10, user1X = 10;
	memset(userMap, 0, sizeof(userMap));
	memset(BC, 0, sizeof(BC));
	M = A = 0;
	ret = 0;
	
	//�Է�
	scanf("%d %d", &M, &A);
	//���� ��� �迭 ����
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &userMap[i][j]);
		}
	}
	//BC ���� ����
	for (int i = 0; i < A; i++) {
		scanf("%d %d %d %d",&BC[i].X, &BC[i].Y, &BC[i].C, &BC[i].P);
	}
}
void chkBC() {
	for (int i = 0; i < A; i++) {//����Ȯ��
		int D = abs(user0Y - BC[i].Y) + abs(user0X - BC[i].X);
		if (BC[i].C >= D) {//����1�� ������ �� ������ ����
			u1.push_back(i);
		}
		D = abs(user1Y - BC[i].Y) + abs(user1X - BC[i].X);
		if (BC[i].C >= D) {//����2�� ������ �� ������ ����
			u2.push_back(i);
		}
	}
}
void userConnect(int num) {//���� �ִ밪 ���ϱ�
	if (num == 1) {
		int Max = 0x80000000;
		for (int i = 0; i < u1.size(); i++) {// ����1�� ��������
			if (Max < BC[u1[i]].P)Max = BC[u1[i]].P;//�ִ� ���Ӱ���
		}
		ret += Max;//�ִ� ����
	}
	if (num == 2) {
		int Max = 0x80000000;
		for (int i = 0; i < u2.size(); i++) {//����2�� ��������
			if (Max < BC[u2[i]].P)Max = BC[u2[i]].P;//�ִ� ���Ӱ���
		}
		ret += Max;//�ִ� ����
	}
	if (num == 3) {
		int Max = 0x80000000;
		for (int i = 0; i < u1.size(); i++) {//�� ������ ���Ӱ����Ѱ����� 
			for (int j = 0; j < u2.size(); j++) {
				if (u1[i] != u2[j]) {
					if (Max < BC[u1[i]].P + BC[u2[j]].P)Max = BC[u1[i]].P + BC[u2[j]].P;
				}
				else if (u1[i] == u2[j]) {
					if (Max < BC[u1[i]].P )Max = BC[u1[i]].P;
				}
			}
		}
		ret += Max;//�ִ� ����
	}
}
void Play() {
	chkBC();//���� ���� BCȮ��
	if (u1.size() != 0 && u2.size() == 0) {//���Ӱ��� ����1�� �ִ°��
		userConnect(1);//���� �ִ밪 ���ϱ�
	}
	else if (u1.size() != 0 && u2.size() != 0) {//�Ѵ� ���Ӱ����Ѱ��
		userConnect(3);//���� �ִ밪 ���ϱ�
	}
	else if (u1.size() == 0 && u2.size() != 0) {//���Ӱ��� ����2�� �ִ°��
		userConnect(2);//���� �ִ밪 ���ϱ�
	}
}
void goUser() {
	Play();//������ Ȯ��
	for (int m = 0; m < M; m++) {//�̵�����
		u1.clear(); u2.clear();
		user0X += dx[userMap[0][m]]; user0Y += dy[userMap[0][m]];
		user1X += dx[userMap[1][m]]; user1Y += dy[userMap[1][m]];
		Play();
	}
}
int main(void) {
	int T;//�׽�Ʈ���̽� ����
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();//�ʱ�ȭ �� �Է�
		goUser();//���� ���
		printf("#%d %d\n", tc, ret);
	}

	return 0;
}