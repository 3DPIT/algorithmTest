#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define N_SIZE 11
int board[N_SIZE][N_SIZE];//10 * 10 �迭
int ret = 0x7fffffff;//�ּҰ�
int paper[6] = { 0,5,5,5,5,5 };//������ ���� üũ ���� �迭
bool safe(int y, int x) {//�迭 ���� üũ
	return 0 <= y && y < 10 && 0<=x&& x < 10;
}
int init() {//�ʱ�ȭ �۾�
	ret = 0x7fffffff;
	memset(board, 0, sizeof(board));//�Է� �迭 0���� �ʱ�ȭ
	int zeroCnt = 0;
	for (int y = 0; y < 10; y++) {//�� �Է�
		for (int x = 0; x < 10; x++) {
			scanf("%d", &board[y][x]);
			if (board[y][x] == 0)zeroCnt++;
		}
	}
	if (zeroCnt == 100)return 0;//��� ���� 0�̸� 0����ϱ� ����
	return 1;//�ƴϸ� ���ǹ� ���۽�Ű�� ����
}
void copy(int cboard[N_SIZE][N_SIZE], int board[N_SIZE][N_SIZE]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cboard[i][j] = board[i][j];
		}
	}
}
bool chk(int cy, int cx, int size) {
		for (int y = cy; y < cy + size; y++) {
			for (int x = cx; x < cx + size; x++) {
				if (safe(y, x)) {
					if(board[y][x] == 0)return false;
				}
				else return false;
			}
		}
		return true;
}
void copypaint(int y, int x, int idx, int num) {
	for (int i = y; i < y + idx; i++) {
		for (int j = x; j < x + idx; j++) {
			board[i][j] = num;
		}
	}
}
void dfs(int cnt) {
	if (cnt > ret)return;
	int flag = 0;//�ʱ�ȭ ����
	int cy = -1, cx = -1;
		for (int y = 0; y < 10; y++) {//��ǥ ã��
			for (int x = 0; x < 10; x++) {
				if (board[y][x] == 1) {
					cy = y; cx = x;//1�� ��ġ y,x ��ǥ 
					flag = 1;//1�� ��ġ ���� ǥ��
					break;
				}
			}
			if (flag)break;
	   }

	if (flag==0) {//���� ���� ����
		ret = ret > cnt ? cnt : ret;//�ּҰ� ����
		return;
	}
	int cboard[N_SIZE][N_SIZE] = { 0, };//ī���� �迭
	for (int i = 1; i <= 5; i++) {
		if (paper[i] == 0)continue;
		if (chk(cy,cx,i)) {
			copypaint(cy, cx, i, 0);
			paper[i]--;//���� ���
			dfs(cnt + 1);//����� ����ũ��, ����
			paper[i]++;//���� ����
			copypaint(cy, cx, i, 1);
		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		if (init()) {
			dfs(0);
		}
		else {//0���� �ٷ� ��½�
			ret = 0;
		}
		if (ret == 0x7fffffff)ret = -1;
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}

	return 0;
}