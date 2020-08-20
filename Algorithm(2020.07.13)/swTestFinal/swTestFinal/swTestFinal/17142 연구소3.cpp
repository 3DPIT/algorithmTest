#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
#define N_SIZE 51
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int N, M;//������ ũ��, ���̷��� ����
int virusMap[N_SIZE][N_SIZE];//�ԷµǴ� ��
int ret;//������ ����
vector<int>D;//���̷��� ���� ����
struct Data {
	int y, x,cnt;
};
vector<Data>v;//���̷��� ����
bool safe(int y, int x) {//���� üũ �Լ�
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	N = M = 0;
	ret = 0x7fffffff;//�ʱ�ȭ
	memset(virusMap, 0, sizeof(virusMap));
	D.clear();
	v.clear();
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &virusMap[i][j]);// �Է� 
			if (virusMap[i][j] == 2) {//���̷��� ����
				v.push_back({ i,j,0});
			}
		}
	}
}

void dfs(int idx, int d) {
	if (idx > v.size())return;// ���� �Ѿ�°� üũ
	if (d == M) {// ���̷��� �˻� ����
		int cnt = 0x80000000;//�ִ밪 ã��
		queue<Data>q;
		int visit[N_SIZE][N_SIZE] = { 0, };//�湮 üũ
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < M; i++) {
			int y = v[D[i]].y; int x = v[D[i]].x;
			q.push({ y,x,1 });
			visit[y][x] = 1;
		}
		while (!q.empty()) {// ���̷��� ���� ����
			Data c = q.front(); q.pop();
		//if(virusMap[c.y][c.x]==0)  cnt = cnt < c.cnt ? c.cnt : cnt;// �ִ밪 ����
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (visit[n.y][n.x] == 0 && safe(n.y, n.x) && virusMap[n.y][n.x] != 1) {
						visit[n.y][n.x] = n.cnt; //�湮üũ
						q.push(n);
				}
			}
		}
		//��ĭ Ȯ�� �ϱ�
		int flag = 0;// ���ĭ ���̷��� �۶߸��� ���� ���
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (virusMap[i][j]==0&& visit[i][j] ==0) {
					flag = 1;
					break;
				}
			 else if(virusMap[i][j] == 0)cnt = cnt < visit[i][j] ? visit[i][j] : cnt;// �ִ밪 ����

			}
			if (flag)break;
		}

		if (flag == 0) {
			ret = ret > cnt ? cnt : ret;//�ּҰ� ����
		}
		return;
	}

	D.push_back(idx);//���̷��� ����
	dfs(idx + 1, d + 1);//���̷��� �̰�
	D.pop_back();
	dfs(idx+1, d);//���̷��� �Ȼ̰�
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0, 0);
		if (0x7fffffff == ret)ret = -1;// ���̷��� ���� ��� ����Ű�� ���
		else if (0x80000000 == ret)ret = 0;
		else ret -= 1;
		//��� ��ġ
	//	printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}