#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define NS 11//���μ��� �ִ� ����
#define HS 31//���μ��� �ִ� ����
int N, M, H;//���μ��� ��, �׾����ִ� ���μ�, ������ �մ� ���μ��� ��
int ret;//����� �Է�
int ladder[HS][NS];//��ٸ� �迭
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ 
	N = M = H = 0; ret = 0x7fffffff;
	memset(ladder, 0, sizeof(ladder));
	//�ʱ� �Է�
	scanf("%d %d %d", &N, &M, &H);//�ʱ� �Է�
	for (int m = 0; m < M; m++) {//���μ� �׾� ����
		int y, x;
		scanf("%d %d", &y, &x);
		ladder[y][x] = 1;// ���μ� �߱�
	}
}
bool chkLadder() {//��ٸ� ���� �´��� Ȯ��
	for (int x = 1; x <= N; x++) {
		int cx = x;
		for (int y = 1; y <= H; y++) {
			if (ladder[y][cx] == 1) {
				cx++;
			}
			else if (ladder[y][cx - 1] == 1) {
				cx--;
			}
		}
		if (x != cx)return false;//���ǿ� ���� �ʴ� ���
	}
	return true;//���ǿ� �����ϴ� ��� 
}
void dfs(int y, int x, int cnt) {
	if (ret < cnt)return;
	else if(0<=cnt&&cnt<=3){//0�� �������� Ȯ���ϱ� 
		if (chkLadder()) {
			ret = min(ret, cnt);
		}
		if (cnt == 3)return;
	}
	for (int i = y; i <= H; i++) {
		for (int j = x; j <= N; j++) {
			if (ladder[i][j] == 0 && ladder[i][j - 1] == 0 && ladder[i][j + 1] == 0) {
				//���� ��ġ�� �׾��� ���� �ʰ� ���ʵ� ���� ���� ���
				ladder[i][j] = 1;//�� �߱�
				dfs(i, j + 1, cnt + 1);
				ladder[i][j] = 0;//�ٽ� ���ƿ� �����ϱ�
			}
		}
		x = 1;
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		dfs(1, 1, 0);
		//���
		if (0x7fffffff == ret)ret = -1;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}