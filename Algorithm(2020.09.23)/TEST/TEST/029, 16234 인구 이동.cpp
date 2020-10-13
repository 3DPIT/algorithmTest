#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 51//�迭�� �ִ� ũ��
int N, L, R;//�迭�� ũ��, �α�����L�̻�, �α����� R����
int SUM; int SIDX;//���� �����ϴ� ������ �հ� ����
struct Data {
	int sum, cnt, ret;//dfs���� ������ ����� ����
}dfsNum[NS*NS];
struct Data1 {
	int y, x, cnt;
};
int flag = 0;//�α��̵� �ߴ��� �ľ�
int S[NS][NS];// ���� �ԷµǴ� �迭
int ret;//�����
int visit[NS][NS];//�湮 üũ
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = L = R = ret = SUM = SIDX = 0;
	memset(dfsNum, 0, sizeof(dfsNum));
	memset(S, 0, sizeof(S));
	memset(visit, 0, sizeof(visit));
	//�ʱ� �Է�
	scanf("%d %d %d", &N, &L, &R);//�迭�� ũ��, ���������� �̻� ���� ��
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &S[i][j]);//�迭 �ʱ� �Է�
		}
	}
}
bool safe(Data1 c) {
	return 0 <= c.y&&c.y < N && 0 <= c.x&&c.x < N;
}
void dfs(int y, int x, int cnt) {

	for (int dir = 0; dir < 4; dir++) {
		Data1 n;
		n.y = y + dy[dir]; n.x = x + dx[dir];
		int iSum = abs(S[y][x] - S[n.y][n.x]);
		if (safe(n) && visit[n.y][n.x] == 0 && L <= iSum && iSum <= R) {
			//������ �ȳѾ�� �湮���� ������, ���̰� L�̻� R�����ΰ��
			visit[n.y][n.x] = cnt;
			SUM += S[n.y][n.x];
			SIDX++;
			flag = 1;
			dfs(n.y, n.x, cnt);
		}
	}
}
bool DFS() {
	flag = 0;
	memset(dfsNum, 0, sizeof(dfsNum));
	memset(visit, 0, sizeof(visit));
	int cnt = 1;//�� ���� ������
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == 0) {
				SUM = S[i][j];
				SIDX = 1;
				visit[i][j] = cnt;
				dfs(i, j, cnt);//���� ��ǥ�� y,x,��ȣ,��,���� ����
				dfsNum[cnt].sum = SUM;
				dfsNum[cnt].cnt = SIDX;
				dfsNum[cnt].ret = SUM / SIDX;
				cnt++;
			}
		}
	}
	if(flag==0)return true;//�α��̵� �Ϸ�
	//�α� �̵� ��� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			S[i][j] = dfsNum[visit[i][j]].ret;
		}
	}
	return false;//�α� �̵������� ����
}
void humanMove() {
	while (++ret) {
		if (DFS())break;
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		humanMove();//�α� �̵� ����
		//���
		printf("%d\n", ret - 1); //printf("#%d %d\n", tc, ret-1);

	}
	return 0;
}