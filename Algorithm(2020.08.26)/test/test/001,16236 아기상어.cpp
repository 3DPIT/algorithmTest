#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define N_SIZE 21
int N;// ������ ������
int seaMap[N_SIZE][N_SIZE];//�Ʊ���� ����� ���� �迭
int visit[N_SIZE][N_SIZE];//�Ʊ��� �湮 üũ �迭
int ret = 0;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {//ť�� ���� �ڷ���
	int y, x, cnt;
};
queue<Data>q;// ť����
bool safe(int y, int x) {//�迭 ���� üũ �Լ�
	return 0 <= y && y < N && 0 <= x && x < N;
}

void init() {
	//�ʱ�ȭ 
	N = ret = 0;
	memset(seaMap, 0, sizeof(seaMap));
	memset(visit, 0, sizeof(visit));
	while (!q.empty())q.pop();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {// ������ �Է�
		for (int j = 0; j < N; j++) {
			scanf("%d", &seaMap[i][j]);
			if (seaMap[i][j] == 9) {// �Ʊ��� ��ġ ã��
				q.push({ i,j,0 });
				visit[i][j] = 1;
				seaMap[i][j] = 0;
			}
		}
	}
}
void BFS() {// �ùķ��̼� ���� �Լ�
	int sharkSize = 2;//��� ũ��
	int fishEat = 0;//�� ����� ������ 
	while (1) {//�Ʊ�� ���� ã���� ���� �ݺ�
		int minY, minX, minCnt;//�ּ� y,x,�ּҰŸ� ����
		minY = minX = minCnt = 0x7fffffff;
		while (!q.empty()) {//ť�� �������� �ݺ� ����
			Data c = q.front(); q.pop();
			if (minCnt < c.cnt)break;
			if (seaMap[c.y][c.x] != 0 && seaMap[c.y][c.x] < sharkSize&&minCnt >= c.cnt) {//���� ���ִ� �����
				minCnt = c.cnt;
				if (minY > c.y || ((minY == c.y && (minX > c.x)))) {
					minY = c.y;
					minX = c.x;//��ǻ� x���� �ּҷ� ����
				}
			}// ���� Ȯ�� �� �ּҰ� ����

			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0 && seaMap[n.y][n.x] <= sharkSize) {
					//���� ���� �ʰ�  �湮 �Ѱ��� �ƴϰ� ���� �۰ų� ���� ���
					visit[n.y][n.x] = 1;
					q.push(n);
				}
			}

		}//ť�� �κ�
		if (0x7fffffff == minY) {//���� ����� �� ������ ����
			break;
		}
		else {
			ret += minCnt;//�ּҰŸ� ����
			fishEat++;
			if (fishEat == sharkSize) {//���ũ�� ��ŭ ���� ��� ũ�� +1
				fishEat = 0;
				sharkSize++;
			}
			while (!q.empty())q.pop();//�ϴ� �ʱ�ȭ
			q.push({ minY,minX,0 });
			memset(visit, 0, sizeof(visit));
			visit[minY][minX] = 1;
			seaMap[minY][minX] = 0;

		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		BFS();
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}