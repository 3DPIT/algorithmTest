#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
#define NSIZE 20//�ִ� ������ ũ��
int board[NSIZE][NSIZE];//�Է����� �־����� �迭
int N, ret;//������ ũ��, �����
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	memset(board, 0, sizeof(board));
	N = 0; ret = 0x80000000;
	//�ʱ� �Է�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);//�Է�
		}
	}
}
void rotation_arr(int board[NSIZE][NSIZE]) {
	int copy[NSIZE][NSIZE] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copy[i][j] = board[N - j - 1][i];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = copy[i][j];
		}
	}
}
void copy(int c[NSIZE][NSIZE], int b[NSIZE][NSIZE]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			c[i][j] = b[i][j];
		}
	}
}
void down_arr() {
	vector<int>q;
	for (int j= 0; j < N; j++) {
		for (int i = N - 1;i>=0; i--) {
			if (board[i][j] != 0)q.push_back(board[i][j]);//�ϴ� ����
			board[i][j] = 0;//�ʱ�ȭ ��Ű��
		}
		for (int i = 0; i < q.size()-1; i++) {
			if (q.size() == 0)break;
			if (q[i] == q[i + 1]&&q[i]!=0) {
				q[i]+=q[i+1];
				q.erase(q.begin() + i+1);
			}
		}
		for (int i = N - 1;q.size(); i--) {
			board[i][j] = q.front();
			q.erase(q.begin());
		}
	}

}
int f = 0;
void dfs(int cnt) {
	if (cnt == 5) {//�ִ� �ټ��� ������
		f++;
		int mNum = 0x80000000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				mNum = max(mNum, board[i][j]);
			}
		}
		ret = max(ret, mNum);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int cboard[NSIZE][NSIZE] = { 0, };//�迭 ����
		copy(cboard, board);
		down_arr();
		dfs(cnt + 1);
		rotation_arr(cboard);//�迭 ������	
		copy(board, cboard);
	}
}
int main(void) {
	int T = 1;
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		dfs(0);
		printf("%d\n", ret);
		//cout << f << endl;
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}