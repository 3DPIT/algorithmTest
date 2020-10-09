#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
#define NSIZE 50//���� ũ��
#define MSIZE 10//���̷��� �ִ��
int D[MSIZE];//Ȱ�����̷��� ����
int lab[NSIZE][NSIZE];//������ ��Ȳ ����
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, M;//��������ũ��, ���̷����� ����
int ret;//����� ����
struct Data
{
	int y, x,cnt;//��ġ y,x,��
};//���̷����� ���� ���
Data virus[MSIZE];
int v_idx;//���̷��� ����
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = v_idx=0;
	ret = 0x7fffffff;//�ּҰ� ���ϱ� 
	memset(lab, 0, sizeof(lab));
	memset(virus, 0, sizeof(virus));
	memset(D, 0, sizeof(D));
	//�ʱ� �Է�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &lab[i][j]);
			if (lab[i][j] == 2) {//���̷��� ���� ����
				virus[v_idx].y = i; virus[v_idx].x = j;
				v_idx++;
			}
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
void dfs(int idx, int cnt) {
	if (cnt == M) {//M�� ��ŭ ���̷��� �̱�
		int visit[NSIZE][NSIZE] = { 0, };//�湮 üũ
		queue<Data>q;
		for (int i = 0; i < v_idx; i++) {
			if (D[i] == 1) {
				q.push({ virus[i].y,virus[i].x,1 });//ť�� �ֱ�
				visit[virus[i].y][virus[i].x] = 1;
			}
		}
		while (!q.empty()) {//���̷��� ��ġ��
			Data c = q.front(); q.pop();//ť������ �̰� ��
			for (int dir = 0; dir < 4; dir++) {
				Data n;//���� ��ġ ����
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0
					&& lab[n.y][n.x] != 1) {//���� �ƴϱ⸸ �ϸ� �ѱ��
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}
		int cnt = 0x80000000;//���� �ִ� �ð� Ȯ��
		for (int y = 0; y < N; y++) {//�ּ� �ð� Ȯ��
			for (int x = 0; x < N; x++) {
				if (lab[y][x] != 1 && lab[y][x] != 2) {//���̷����ִ°��̾ƴϰ� ���̾ƴѰ��
					cnt = max(cnt, visit[y][x]);
				}
				if (lab[y][x] == 0 && visit[y][x] == 0) {//������ε� ���̷��� ������ Ż
					return;
				}
			}
		}
		if (cnt == 0x80000000)cnt = 0;
		ret = min(ret, cnt);
		return;
	}
	for (int i = idx; i < v_idx; i++) {
		D[i] = 1;
		dfs(i+1, cnt + 1);
		D[i] = 0;
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ���̽�
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		dfs(0, 0);//���̷��� ���Ľ���
		if (0x7fffffff == ret)ret = -1;//���̷��� �� ��ä��� ���
		//���
		else if(ret!=-1&&ret!=0) ret--;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}