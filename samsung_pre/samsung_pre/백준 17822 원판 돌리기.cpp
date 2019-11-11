#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define NS 52
#define MS 52
int N, M, T;
int num[NS][MS];
int xi, di, ki;
int chk[NS][MS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int flag;// ���߿� �������� ������ �ִ��� �ľ��ϱ�����
int flag1;
int ret;
void sumNum() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			ret += num[i][j];
		}
	}
}
void dfs(int y, int x, int sameNum) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (ny <= 0)continue;
		if (ny > N)continue;
		if (nx <= 0)nx = M;
		if (nx > M)nx = 1;
		if (chk[ny][nx] == 0 && num[ny][nx] == sameNum && num[ny][nx] != 0) {
			chk[ny][nx] = 1;
			num[ny][nx] = 0;
			flag = 1;
			dfs(ny, nx, sameNum);
		}

	}
}
void searchNum() {
	memset(chk, 0, sizeof(chk));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (chk[i][j] == 0 && num[i][j] != 0) {
				flag = 0;
				chk[i][j] = 1;
				dfs(i, j, num[i][j]);
				if (flag == 1) {//�Ѱ��� �ߺ��Ǽ� ��������
					num[i][j] = 0;
					flag1 = 1;
				}
			}
		}
	}
}
void rightClock(int y) {//0 �ð����
	int snum = num[y][M];
	for (int x = M - 1; x >= 1; x--) {
		num[y][x + 1] = num[y][x];
	}
	num[y][1] = snum;//���� ����
}
void leftClock(int y) {//1 �ݽð� ����
	int sum = num[y][1];
	for (int x = 2; x <= M; x++) {
		num[y][x - 1] = num[y][x];
	}
	num[y][M] = sum;
}
void calNum(int sum, int cnt) {
	float a = (float)sum / cnt;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (num[i][j] != 0 && num[i][j] < a) {
				num[i][j]++;
			}
			else if (num[i][j] != 0 && num[i][j] > a) {
				num[i][j]--;
			}
		}
	}
}
void rotCir() {//���� ������ �ù�
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &xi, &di, &ki);
		for (int i = 1; i <= M; i++) {
			if (i % xi == 0) {//xi�� ����̸�
				if (di == 0) {
					for (int k = 0; k < ki; k++) {
						rightClock(i);
					}
				}
				else if (di == 1) {
					for (int k = 0; k < ki; k++) {
						leftClock(i);
					}
				}
			}
		}
		searchNum();
		if (flag1 == 0) {
			int sum = 0;
			int cnt = 0;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					sum += num[i][j];
					if (num[i][j] != 0) {
						cnt++;
					}
				}
			}
			//sum = sum / cnt;//��հ�
			if (cnt != 0)
				calNum(sum, cnt);
		}
	}
}
void init() {
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &num[i][j]);
		}
	}
	rotCir();
	sumNum();
}
int main(void) {
	init();
	cout << ret << endl;
	return 0;
}