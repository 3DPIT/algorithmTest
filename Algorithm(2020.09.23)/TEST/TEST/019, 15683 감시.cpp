#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define NMS 8//���ο� ������ �ִ� ũ��
int N, M;//�繫���� ���ο� ���� ũ��
int ret;//����� 
int room[NMS][NMS];//�繫�� ����
struct Data {
	int y, x, num;
}cctv[65];//��ü�� cctv�� �� ����Ͽ� �ִ� 64��
int cctvIdx;
int dy[] = { 0,1,0,-1 };//cctv ���� ����
int dx[] = { 1,0,-1,0 };
int cctvCnt[6] = { 0,4,2,4,4,1 };//cctv�ѹ� �� ���� ����
void copy(int cr[NMS][NMS], int r[NMS][NMS]) {//�迭 ���� �Լ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cr[i][j] = r[i][j];
		}
	}
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M =cctvIdx= 0;
	ret = 0x7fffffff;//�ּҰ�
	memset(room, 0, sizeof(room));
	//�ʱ� �Է�
	scanf("%d %d", &N, &M);//���� ���� ũ�� �Է�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &room[i][j]);//�ʱ� �Է�
			if (room[i][j] != 6 && room[i][j] != 0) {//cctv���� ã��
				cctv[cctvIdx].y = i; cctv[cctvIdx].x = j; cctv[cctvIdx].num = room[i][j];
				//cctv�� ��ǥ���� ��ȣ
				cctvIdx++;
			}
		}
	}
}
bool isafe(int y, int x) {
	return y < 0 || y == N || x < 0 || x == M;
}
void paint(Data c, int dir) {//���� ĥ�ϱ�
	dir = dir % 4;
	while (1) {
		Data n;
		n.y = c.y + dy[dir]; n.x = c.x + dx[dir];//���� ����
		if (isafe(n.y, n.x) || room[n.y][n.x] == 6)break;
		room[n.y][n.x] = 9;//cctv ��� �Է�
		c.y = n.y; c.x = n.x;
	}
}
int zeroCnt() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (room[i][j] == 0)cnt++;
		}
	}
	return cnt;
}
void dfs(int idx, int cnt) {
	if (cnt == cctvIdx) {
		ret=min(ret,zeroCnt());//�ּҰ� ����
		return;
	}
	for (int i = idx; i < cctvIdx; i++) {
		int cctvNumber = cctv[i].num;//cctv �ѹ�
		int croom[NMS][NMS] = { 0, };//���纻
		for (int dir = 0; dir < cctvCnt[cctvNumber]; dir++) {//cctv ����
			copy(croom, room);
			//����Ʈ ĥ�ϱ�
			if (cctvNumber == 1) {
				paint(cctv[i], dir);
			}
			else if (cctvNumber == 2) {
				paint(cctv[i], dir);
				paint(cctv[i], dir+2);
			}
			else if (cctvNumber == 3) {
				paint(cctv[i], dir);
				paint(cctv[i], dir + 1);

			}
			else if (cctvNumber == 4) {
				paint(cctv[i], dir);
				paint(cctv[i], dir + 1);
				paint(cctv[i], dir + 2);
			}
			else if (cctvNumber == 5) {
				paint(cctv[i], dir);
				paint(cctv[i], dir + 1);
				paint(cctv[i], dir + 2);
				paint(cctv[i], dir + 3);
			}
			dfs(i+1, cnt + 1);
			copy(room, croom);
		}
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
//	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		dfs(0, 0);
		//���
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);

	}
	return 0;
}