#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
#define MIN(a,b) (((a)>(b)) ? (b) :(a))
#define MAX(a,b) (((a)<(b)) ? (b) :(a))

#define N_SIZE 51
int N, M;//�� ũ��, ���̷��� ����
int virusMap[N_SIZE][N_SIZE];//�Է����� �־����� �迭
int visit[N_SIZE][N_SIZE];//���̷��� �湮üũ
int ret;//������
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
struct Data {
	int y, x, cnt;
};
vector<int> virusSelect;//ť Ž������
int IDX = 0;//���̷��� ���� �ľ�
Data virus[11];
bool safe(int y, int x) {//���� üũ �Լ�
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	//�ʱ�ȭ ���� �� �Է� ����
	N = M = IDX = 0; ret = 0x7fffffff;
	memset(virusMap, 0, sizeof(virusMap));
	memset(visit, 0, sizeof(visit));

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &virusMap[i][j]);
			if (virusMap[i][j] == 2) {
				virus[IDX].y = i; virus[IDX].x = j;
				IDX++;
			}
		}
	}
}
void dfs(int idx, int d) {
	if (idx > IDX)return;
	if (d == M) {
		queue<Data>q;
		memset(visit, 0, sizeof(visit));
		int cnt = 0x80000000;//�ִ� ������ ��
		for (int i = 0; i < M; i++) {
			int y = virus[virusSelect[i]].y;
			int x = virus[virusSelect[i]].x;
			q.push({y,x,0});
			visit[y][x] = 1;
		}
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			cnt=MAX(cnt, c.cnt);
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y =c.y+dy[dir]; n.x =c.x+dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && virusMap[n.y][n.x] != 1 && visit[n.y][n.x] == 0) {
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}
		int flag = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (virusMap[i][j] != 1 && visit[i][j] == 0) {
					flag = 1; break;
				}
			}
		}
		if(flag==0)ret=MIN(ret, cnt);
		return;
	}
	virusSelect.push_back(idx);
	dfs(idx + 1, d + 1);//�̴� ���
	virusSelect.pop_back();
	dfs(idx + 1, d);//�Ȼ̴� ���
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0,0);
		if (ret == 0x7fffffff)ret = -1;
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}