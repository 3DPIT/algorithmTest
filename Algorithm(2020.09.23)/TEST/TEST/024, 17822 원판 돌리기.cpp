
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
using namespace std;
#define NMS 51//���� ���� �ִ� ũ��
int N, M, T;//����, ���� ũ�� , �ð�
int ret;//��� ��
int circle[NMS][NMS];// ���� �迭
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int visit[NMS][NMS];//�湮 üũ
int flag;//���� üũ

struct Data {
	int num, dir, cnt;//����, ����, ����
};
struct Data1 {
	int y, x;
};

vector<Data>order;//�ֹ� Ȯ��
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ 
	order.clear();
	N = M = T = flag = ret = 0;
	memset(visit, 0, sizeof(visit));
	memset(circle, 0, sizeof(circle));
	//�ʱ� �Է�
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &circle[i][j]);//�ʱ� ���� ���� �Է�
		}//for j
	}//for i
	for (int t = 1; t <= T; t++) {
		int num, dir, cnt;
		scanf("%d %d %d", &num, &dir, &cnt);//��� ����
		order.push_back({ num,dir,cnt%M });
	}
}
void clockTurn(int num, int cnt) {//�ð���� ��
	for (int i = 0; i < N; i++) {
		if ((i + 1) % num == 0) {//����ΰ��
			for (int c = 0; c < cnt; c++) {
				int cnum = circle[i][M - 1];//���� ���� ����
				for (int j = M - 1; j >= 1; j--) {
					circle[i][j] = circle[i][j - 1];
				}
				circle[i][0] = cnum;
			}
		}
	}
}
void reclockTurn(int num, int cnt) {//�ݽð���� ��
	for (int i = 0; i < N; i++) {
		if ((i + 1) % num == 0) {//����ΰ��
			for (int c = 0; c < cnt; c++) {
				int cnum = circle[i][0];//���� ���� ����
				for (int j = 0; j < M - 1; j++) {
					circle[i][j] = circle[i][j + 1];
				}
				circle[i][M - 1] = cnum;
			}
		}
	}
}
void dfs(int y, int x, int num) {//���� �� ���� dfs
	//�Ѱ� �ټ� �ִ� �� x==-1 -> x=M-1 
	// x==M -> x=0;
	//�Ѿ�� �ȵǴ� ����
	//y==-1, y==N+1
	for (int dir = 0; dir < 4; dir++) {
		Data1 n;
		n.y = y + dy[dir]; n.x = x + dx[dir];
		if (n.y != -1 && n.x != N + 1) {
			if (n.x == -1) {
				n.x = M - 1;
			}
			if (n.x == M) {
				n.x = 0;
			}
		}
		if (visit[n.y][n.x] == 0 && circle[n.y][n.x] == num) {
			circle[n.y][n.x] = 0;
			visit[n.y][n.x] = 1;
			flag = 1;
			dfs(n.y, n.x, num);
		}

	}
}
void DFS() {//������ �����ϱ� ����
	memset(visit, 0, sizeof(visit));
	int f = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (circle[i][j] != 0) {
				visit[i][j] = 1;
				dfs(i, j, circle[i][j]);
				if (flag) {
					f = 1;
					circle[i][j] = 0;
					visit[i][j] = 1;
					flag = 0;
				}
			}
		}
	}
	flag = f;
}
void chkNum() {//���� �������� ��
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret += circle[i][j];
		}
	}
}
void circleTurn() {
	for (int t = 0; t < T; t++) {
		//��ȣ�� xi�� ����� ������ di�������� kiĭ ȸ����Ų��.di�� 0�� ���� �ð� ����, 1�� ���� �ݽð� �����̴�.
		if (order[t].dir == 0) {//�ð� �̵�
			clockTurn(order[t].num, order[t].cnt);
		}
		if (order[t].dir == 1) {//�ݽð� �̵�
			reclockTurn(order[t].num, order[t].cnt);
		}
		flag = 0;//�÷��� �ʱ�ȭ
		//�׷��� ���� �ִ� ��쿡�� ���ǿ��� �����ϸ鼭 ���� ���� ��� �����.
		DFS();//���� ���¿��� ������ �� ����
		if (flag == 0) {//�����Ұ��� ���� ���
			//���� ��쿡�� ���ǿ� ���� ���� ����� ���ϰ�, ��պ��� ū ������ 1�� ����, ���� ������ 1�� ���Ѵ�.
			double num = 0; int numcnt = 0;;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (circle[i][j] != 0) {
						num += circle[i][j];
						numcnt++;
					}
				}
			}
			//��� ���ϱ�
			num = num / numcnt;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (circle[i][j] != 0) {
						if (circle[i][j] > num) {//��պ��� ū��
							circle[i][j]--;
						}
						else if (circle[i][j] < num) {//��պ��� ������
							circle[i][j]++;
						}
					}// if circle
				}//for j
			}//for i
		}//if flag
	}//for t
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret += circle[i][j];
		}
	}
}
int main(void) {
	int testCase = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		circleTurn();//���� ������
		//���
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}