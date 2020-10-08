#include<stdio.h>
#include<vector>
#include<iostream>
#include<string.h>
using namespace std;
#define DSIZE 13
#define WSIZE 20
int D, W, K;//�β�, ����ũ��, �հݱ���
int T;//�׽�Ʈ ���̽� ����
int film[DSIZE][WSIZE];//�Է����� �־����� �ʸ�
int ret;//����� ����
int d[DSIZE];
void init() {//�ʱ�ȭ
	D = W = K = 0;
	ret = 0x7fffffff;
	memset(film, 0, sizeof(film));
}
void copy(int idx, int copyFilm[WSIZE], int flag) {// ���� ��ġ ����
	if (flag == 0) {//���
		for (int i = 0; i < W; i++)
			copyFilm[i] = film[idx][i];
	}
	else {//����
		for (int i = 0; i < W; i++)
			film[idx][i] = copyFilm[i];
	}
}
void changeType(int idx, int type, int copyFilm[WSIZE]) {//Ÿ�� ����
	if (type != 2) {
		for (int i = 0; i < W; i++)
			film[idx][i] = type;
	}
}
bool kTest() {//�հ� ���� �Ǻ�
	int Test = 0;//W���� �հ� �̸� true �ƴϸ� false
	for (int j = 0; j < W; j++) {
		for (int i = 0; i < D - 1; i++) {
			int cnt = 1;
			for (int ci = i + 1; ci < D; ci++) {
				if (film[i][j] == film[ci][j]) {//�ʸ��� ������ 
					cnt++;
				}
				else {
					break;
				}
			}
			if (cnt >= K) {
				Test++;
				break;
			}
		}
		if (Test != j + 1)return false;
	}
	return true;
}
void dfs(int idx, int type, int cnt) {
	if (ret <= cnt)return;//Ȥ�� ���� �ּҰ����� Ŀ���� ���̸� ����
	if (idx == D + 1)return;
	else {//�հ� ���� �Ǻ�
		//�Ǻ�����
		if (kTest()) {
			ret = ret > cnt ? cnt : ret;//�ּҰ� ����
		}
	}
	int copyFilm[WSIZE] = { 0, };//���� �ʸ� ����
	dfs(idx + 1, 0, cnt);//�״��
	copy(idx, copyFilm, 0);//�̸� ����
	changeType(idx, 0, copyFilm);
	dfs(idx + 1, 0, cnt + 1);//AŸ������
	changeType(idx, 1, copyFilm);
	dfs(idx + 1, 1, cnt + 1);//BŸ������
	copy(idx, copyFilm, 1);//���
}
int main(void) {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		//�Է��ϱ�
		scanf("%d %d %d", &D, &W, &K);
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &film[i][j]);
			}
		}
		//�˰��� ����
		dfs(0, 0, 0);
		//���
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}