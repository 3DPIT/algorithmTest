#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define N_SIZE 51
int N, L, R;// �迭�� ũ��, �ּ�, �ִ� ��
int ret;//����� ����
int humanMap[N_SIZE][N_SIZE];// �α��� ���� �迭
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int flag = 0;//���� ������ üũ
int visit[N_SIZE][N_SIZE] = { 0, };
struct Data {
	int sum, num;
};
Data a[2501];// ������ �� ����ϱ�
void init() {
	// �ʱ�ȭ ��Ű��
	N = L = R = ret = 0;
	memset(humanMap, 0, sizeof(humanMap));
	//
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {	// �α� ������ �Է�
		for (int j = 0; j < N; j++) {
			scanf("%d", &humanMap[i][j]);
		}
	}
	//
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
void dfs(int y, int x, int cnt) {

	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (safe(y,x)) {
			int num = abs(humanMap[y][x] - humanMap[ny][nx]);// �α����� �� ���
			if (L <= num && num <= R && visit[ny][nx] == 0) {
				flag = 1;
				a[cnt].sum += humanMap[ny][nx];//1�� ������ �����Ͱ� �����ϱ�
				a[cnt].num++;//������ �� ������Ű��
				visit[ny][nx] = cnt;
				dfs(ny, nx, cnt);
			}
		}
	}
}
int openLine() {
	int cnt = 0;
	memset(visit, 0, sizeof(visit));
	memset(a, 0, sizeof(a));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == 0) {
				++cnt;
				a[cnt].sum = humanMap[i][j];
				a[cnt].num = 1;
				visit[i][j] = cnt;
				dfs(i, j, cnt);
				a[visit[i][j]].sum /= a[visit[i][j]].num;
			}
		}
	}

	for (int i = 0; i < N; i++) {// �α� �й��ϱ�
		for (int j = 0; j < N; j++) {
			if (visit[i][j] >= 1) {
				int num = a[visit[i][j]].sum;
				// ������ �α���
				humanMap[i][j] = num;
			}
		}
	}
	return flag;
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		while (1) {
			int cnt = openLine();
			if (cnt == 0)break;
			flag = 0;
			++ret;
		}
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}