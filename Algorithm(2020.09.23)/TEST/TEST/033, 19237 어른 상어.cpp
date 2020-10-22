#include<stdio.h>
#include<vector>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
#define NS 21//�ִ� �迭 ������
int ret;//�����
int N, M, K;//�迭 ũ��, ��� ��, ��� ��ü�� ���� �ð�
int dy[] = { 0,-1,1,0,0 };// 1: ��, 2: �Ʒ� 3: �� 4 : ��
int dx[] = { 0,0,0,-1,1 };
struct Data {
	int n; int c1; int f;//����� ����, ����� ���� ���� �ð�,����� �����̸� 0, ����̸� 1
}B[NS][NS];
struct Data1 {
	int y, x, dir, n;
}sharkPos[NS*NS];//����� ��ġ �ǽð� Ȯ�� ����

int sharkDir[NS*NS][5][5];//����� �� ���⸶���� �켱 ���� ���� �迭
bool safe(int y, int x) {//���� Ȯ�� �Լ�
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ 
	N = M = K = ret = 0;
	memset(B, 0, sizeof(B));
	memset(sharkDir, 0, sizeof(sharkDir));
	memset(sharkPos, 0, sizeof(sharkPos));
	//�ʱ��Է�
	scanf("%d %d %d", &N, &M, &K);//�迭 ũ��, ��� ��, ��� ���� ��
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &B[i][j].n);//�迭�� �Է�
			if (B[i][j].n != 0) {//����� ��ġ ����
				sharkPos[B[i][j].n].y = i; sharkPos[B[i][j].n].x = j;
				sharkPos[B[i][j].n].n = B[i][j].n;
				B[i][j].f = 1;
				B[i][j].c1 = 4;
			}
		}
	}
	for (int i = 0; i < M; i++) {//���� ����� ���� ����
		int dir = 0; scanf("%d", &dir);
		sharkPos[i + 1].dir = dir;
		sharkPos[i + 1].n = i + 1;

	}
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			int a, b, c, d;//�켱 ���� ����
			scanf("%d %d %d %d", &a, &b, &c, &d);
			sharkDir[i][j][1] = a;
			sharkDir[i][j][2] = b;
			sharkDir[i][j][3] = c;
			sharkDir[i][j][4] = d;
		}
	}
}
void playGame() {
	while (ret <= 1000) {
		ret++;//�ð� ����
		//1. ����� �̵�
		for (int si = 1; si <=M ; si++) {
			Data1 c = sharkPos[si];
			int c1 = 0;//���� ������ ����� ���°� üũ�ϱ� ����
			for (int d = 1; d <= 4; d++) {
				int dir = sharkDir[si][sharkPos[si].dir][d];
				Data1 n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.dir = dir; n.n = c.n;
				//a. ����ĭ�߿� ������ ���� ĭ ���� Ǫ��
				if (safe(n.y, n.x) && B[n.y][n.x].c1 == 0 && B[n.y][n.x].f == 0 && B[n.y][n.x].n == 0) {
					c1=1;
					B[c.y][c.x].f = 0;
					B[c.y][c.x].n = si;
					B[c.y][c.x].c1 = K;
					sharkPos[si] = n;
					break;
				}
			}
			if (c1 == 0) {//b. �׷�ĭ�� ���ٸ� �ڽ� ���� ���� ĭ���� Ǫ��
				for (int d = 1; d <= 4; d++) {
					int dir = sharkDir[si][sharkPos[si].dir][d];
					Data1 n;
					n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.dir = dir; n.n = c.n;
					if (safe(n.y, n.x) && B[n.y][n.x].f==0&& B[n.y][n.x].n == si) {
						B[c.y][c.x].f = 0;
						B[c.y][c.x].c1 = K;
						B[c.y][c.x].n = si;
						sharkPos[si] = n;
						break;
					}
				}
			}
		}
		//2. �̵��� ���� �浹�Ѱ��� ���� �� ū��� ��������
		for (int si = 1; si <M; si++) {
			for (int sj = si+1; sj <= M; sj++) {
				if (si == sj)continue;
				if (si < sj&&sharkPos[si].y == sharkPos[sj].y&&sharkPos[si].x == sharkPos[sj].x) {
					sharkPos[sj].dir = 0; sharkPos[sj].n = -1; sharkPos[sj].x = 0; sharkPos[sj].y = 0;
				}
			}
		}
		for (int si = 1; si <= M; si++) {//�迭�� �ٽ� �Է�
			if (sharkPos[si].n == -1)continue;
			B[sharkPos[si].y][sharkPos[si].x].c1 = K; B[sharkPos[si].y][sharkPos[si].x].n = si;
			B[sharkPos[si].y][sharkPos[si].x].f = 1;
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (B[i][j].f != 1 && B[i][j].c1 != 0) {
					B[i][j].c1--;
					if (B[i][j].c1 == 0) {
						B[i][j].n = 0;
					}
				}
			}
		}
		int sc1 = 0;
		for (int si = 1; si <= M; si++) {
			if (sharkPos[si].n != -1)sc1++;
		}
		if (sc1 == 1)break;//��� �Ѹ��� ���� ���
	}
	if (ret == 1001)ret = -1;//4. 1000�� ���� ��쿡�� ��� 1������ �ƴϸ� -1�� ���
}
int main(void) {
	int T = 1;//�׽�Ʈ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ��Է�
		playGame();
		printf("%d\n", ret);//printf("#%d %d\n", tc, ret);
	}
	return 0;
}