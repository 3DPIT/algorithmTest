#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define ROOM_SIZE 9
int room[ROOM_SIZE][ROOM_SIZE];
int cctvCnt[] = { 0,4,2,4,4,1 };// cctv ����
int N, M;
int dy[] = { 0,1,0,-1 };//�� �� �� ��
int dx[] = { 1,0,-1,0 };
int Min = 0x7fffffff;//�ּҰ�
struct Data {//y,x,�� cctv ���� ���
	int y, x, type;
};
vector<Data>CCTV;//cctv ��� ����
void init() {//�ʱⰪ ����
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &room[i][j]);
			if (room[i][j] != 6// ���̳� ������� �ƴѰ� ����
				&& room[i][j] != 0) {
				CCTV.push_back({ i,j,room[i][j] });
			}
		}
	}
}
bool safe(int y, int x) {//���� ���� �Ѿ���� üũ
	return 0 <= y && y < N && 0 <= x && x < M;
}
void search(int dir, int y, int x) {//��ο� ǥ���ϱ�
	dir = (dir % 4);// dir ȸ�� 
	while (1) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (room[ny][nx] != 6&&safe(ny,nx)) {
			room[ny][nx] = 8;// ���ÿ��� ����
		}
		else {
			break;
		}
		y = ny; x = nx;
	}
}
void copy(int cr[ROOM_SIZE][ROOM_SIZE], int r[ROOM_SIZE][ROOM_SIZE]) {//�迭 ����
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cr[i][j] = r[i][j];
		}
	}
}
void print(int idx,int i) {//���� ��� ������
	if (CCTV[idx].type == 1) {
		search(i, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
	}
	if (CCTV[idx].type == 2) {
		search(i, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 2, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
	}
	if (CCTV[idx].type == 3) {
		search(i, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 1, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
	}
	if (CCTV[idx].type == 4) {
		search(i, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 1, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 2, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
	}
	if (CCTV[idx].type == 5) {
		search(i, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 1, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 2, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
		search(i + 3, CCTV[idx].y, CCTV[idx].x);//���� ,y,x �ѱ��
	}
}
void dfs(int idx,int cnt) {
	if (cnt == CCTV.size()) {// ���� �������� cctv ��� ������ ��� ���� �簢 ���� �˻��ϱ� 
		int ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (room[i][j] == 0) {
					ret++;//�簢���� ����Ǵ°�
				}
			}
		}
		Min = Min > ret ? ret : Min;//�簢������ �ּҰ�
		return;
	}
	int croom[ROOM_SIZE][ROOM_SIZE] = { 0, };//������ �����ϴ� �迭
	for (int i = 0; i < cctvCnt[CCTV[idx].type]; i++) {
		copy(croom, room);
		print(idx, i);//cctv���� ��� ������
		dfs(idx + 1, cnt + 1);
		copy(room, croom);
	}
}
int main(void) {
	init();
	dfs(0,0);
	cout << Min << endl;
	return 0;
}