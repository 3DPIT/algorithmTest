#include<stdio.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
#define NS 21
int N;//�ٴ��� ũ��
int sea[NS][NS];//�ʱ� �Է� �迭 �ٴ� ����
int ret;//�����
int dy1[4] = { 0,1,0,-1 };
int dx1[4] = { 1,0,-1,0 };
struct Data {
	int y, x,cnt;
};
queue<Data>q;//����� �̵� ��� ���� ť
int init_input(){//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = ret = 0;
	memset(sea, 0, sizeof(sea));
	//�ʱ� �Է�
	scanf("%d",&N);//�ٴ��� ũ�� �Է�
	int cnt = 0;//���� ����� ������ �ľ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &sea[i][j]);// �ʱ� �Է�
			if (sea[i][j] == 9) {
				q.push({ i,j });
				sea[i][j] = 0;//��ġ ����
			}
			if (sea[i][j] != 0)cnt++;
		}
	}
	if (cnt == 0)return 0;
	return 1;
}
bool safe(Data c) {//���� Ȯ��
	return 0 <= c.y && c.y < N && 0 <= c.x && c.x < N;
}
void eatFish() {//���� ��� ����
	int sharkSize = 2;//��� ũ��
	int eat = 0;//���� ����
	while (1) {
		int visit[NS][NS] = { 0, };//�湮 üũ
		visit[q.front().y][q.front().x] = 1;
		int dy = 0x7fffffff; int dx = 0x7fffffff; int dd = 0x7fffffff;//���� ������ ���� ���� �̱� ����
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			//���� �� �ִ� ����Ⱑ 1�������� ���ٸ�, �Ÿ��� ���� ����� ����⸦ ������ ����.
			if (sea[c.y][c.x]!=0&&sea[c.y][c.x]<sharkSize&dd >= c.cnt) {
				//�Ÿ��� ����� ����Ⱑ ���ٸ�, ���� ���� �ִ� �����, �׷��� ����Ⱑ �����������,
				//���� ���ʿ� �ִ� ����⸦ �Դ´�.
				if (dd == c.cnt) {
					dd = c.cnt;
					if (dy>c.y||(dy==c.y&&dx>c.x)) {
						dy = c.y; dx = c.x;
					}
				}
				else if (dd > c.cnt) {
					dd = c.cnt;
					dy = c.y; dx = c.x;
				}
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy1[dir]; n.x = c.x + dx1[dir];
				n.cnt = c.cnt + 1;//���� ��ǥ��
				if (safe(n) && visit[n.y][n.x] == 0 && 0 <= sea[n.y][n.x] && sea[n.y][n.x] <= sharkSize) {
					//���� �Ÿ��� �ְ�, �湮������ ������, �ڱ�ũŰ���� �۰ų� ���� ��쿡�� Ǫ��
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}//while !q.empty()
		if (dd != 0x7fffffff) {//���� ��Ⱑ �ִ� ���
			eat++;
			if (eat == sharkSize) {//ũ�� ��ŭ ���� ��� ����
				sharkSize++;
				eat = 0;
			}
			ret += dd;//�ɸ� �ð�
			sea[dy][dx] = 0;
			q.push({ dy,dx,0 });
		}
		else if (dd == 0x7fffffff) {
		//�� �̻� ���� �� �ִ� ����Ⱑ ������ ���ٸ� �Ʊ� ���� ���� ���� ������ ��û�Ѵ�.
			break;
		}
	}//while 1
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽�
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		if(init_input()){//�ʱ�ȭ �� �ʱ� �Է�
			eatFish();// ����� ��� ����
			//���
			printf("%d\n", ret); printf("#%d %d\n", tc, ret);
		}
		else {//����� ���� ���
			//���
			printf("%d\n", ret); printf("#%d %d\n", tc, ret);
		}
	}
	return 0;
}

//�Ÿ��� �Ʊ� �� �ִ� ĭ���� ����Ⱑ �ִ� ĭ���� �̵��� ��, �������ϴ� ĭ�� ������ �ּڰ��̴�.
