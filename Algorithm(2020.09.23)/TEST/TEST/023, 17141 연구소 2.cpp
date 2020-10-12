#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
#define NS 51//�������� �ִ� ũ��
#define MS 11
int N, M, ret;//�������� ũ��, ���̷��� ���� ����, ����� ���� ����
int lab[NS][NS];//������ �迭
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, cnt;
}virus[MS];
int vIdx;//���̷��� ����
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = vIdx=0;
	ret = 0x7fffffff;//�ּҰ�
	memset(lab, 0, sizeof(lab));
	memset(virus, 0, sizeof(virus));
	//�ʱ� �Է�
	scanf("%d %d", &N, &M);//������ ũ��, ���̷��� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &lab[i][j]);//������ ���� �Է�
			if (lab[i][j] == 2) {
				virus[vIdx].y = i; virus[vIdx].x = j; virus[vIdx].cnt = 0;
				vIdx++;//���̷��� ���� ����
			}
		}
	}
}
bool safe(int y, int x) {//�迭�� ���� 
	return 0 <= y && y < N && 0 <= x && x < N;
}
//1. M���� ���̷��� dfs�� �̿��Ͽ� ����
void dfs(int idx, int c) {//���̷��� ������, ������ ��
	if (idx == vIdx+1)return;
	if (c == M) {
		queue<Data>q;//���̷��� ���� �غ� ť
		int visit[NS][NS] = { 0, };//�湮 üũ
		for (int i = 0; i < vIdx; i++) {//���̷��� ����
			if (virus[i].cnt == 1) {
				q.push(virus[i]);
				visit[virus[i].y][virus[i].x] = 1;
			}
		}
		//2. BFS�� �̿��Ͽ� ���̷��� ����  cnt�� �ִ뱸�س���
		int cnt = 0;//cnt ť�����ִ밪 
		while (!q.empty()){
			Data c = q.front(); q.pop();
			cnt = c.cnt;
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];//���� ��ǥ
				n.cnt = c.cnt+1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0 && lab[n.y][n.x] != 1) {
					//���� ���� �ȿ��ְ� �湮������ ������ ���� �ƴѰ�� Ǫ��
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}
		//3. ���� �����ϰ� 0 �ΰ����� ��� �ִ��� üũ�ϱ�
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (lab[i][j] == 0 && visit[i][j] == 0)return;//�̰�� �����Ѱ� �ƴ�
			}
		}
		//4. cnt�� �ּҰ� �����ϱ�
		ret = min(ret, cnt-1);
		return;
	}
	virus[idx].cnt = 1;//���̷��� ����
	dfs(idx + 1, c + 1);
	virus[idx].cnt = 0;//���̷��� ����
	dfs(idx + 1, c);
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		dfs(0, 0);
		if (0x7fffffff == ret)ret = -1;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}