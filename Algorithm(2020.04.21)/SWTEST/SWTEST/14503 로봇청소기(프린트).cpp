#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
#define NS 51
#define MS 51
int N, M;
int y, x, dir,ret,Time;
int map[NS][MS];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
void init() {
	N=M=y = x = dir = ret=0;
	Time = 2;
	memset(map, 0, sizeof(map));
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << "  " << map[i][j];
			}
			cout << endl;
		}
	}
}
void cleanRoom() {
	while(1) {
		if (map[y][x] == 0) {// ������ġ û��
			map[y][x] =Time++;
		}
		print("�κ��ǰ��", 0);
		int cdir = dir;
		int i = 0;
		for (i = 0; i < 4; i++) {//���� ��ġ �������ο��� Ž��
			dir--;
			if (dir == -1) dir = 3;
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (safe(ny, nx)) {
				if (map[ny][nx]==0) {//Ž���ߴµ����� 0�̸� ���� ��ȯ�� �̵� break;
					y = ny; x = nx;
					break;
				}
			}
			else continue;

		}
		if (i == 4) {//�׹��� �ٵ��Ҵµ� û�Ұ���������
			dir = cdir;
			int ny = y - dy[dir];
			int nx = x - dx[dir];
			if (map[ny][nx] != 1) {//���� ��ġ �����ϰ� ��ĭ�ڷ� �̵�
				y = ny;
				x = nx;
			}
			else {		// �̶� ��ĭ�ڿ� ���̸� �۵� �Ϸ� ��Ű��
				break;

			}

		}
		
	}
}
int main(void) {
	int T = 2;
	for (int t = 1; t <= T; t++) {
		init();
		scanf("%d %d", &N, &M);
		scanf("%d %d %d", &y, &x, &dir);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		print("�Է¸�", 0);

		cleanRoom();
		printf("#%d %d\n", t, Time-2);
		//printf("%d\n", Time-1);
	}

	return 0;
}