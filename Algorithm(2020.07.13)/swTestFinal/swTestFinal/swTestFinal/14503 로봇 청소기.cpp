#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define MAP_SIZE 51
int N, M;//�� ��
int map[MAP_SIZE][MAP_SIZE];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int y, x, dir;
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void init() {
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &y, &x, &dir);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
void play() {
	int clean_room = 1;
	while (1) {// ���� �ݺ�
		if (map[y][x] == 0) {//���� ��ġ�� û���Ѵ�.
			map[y][x] = ++clean_room;
		}
		//���� ��ġ���� ���� ������ �������� ���ʹ������ ���ʴ�� Ž���� �����Ѵ�.
		int i = 0;
		int cdir = dir;
		for (i = 0; i < 4; i++) {
			cdir--;
			if (cdir == -1)cdir = 3;
			if (safe(y + dy[cdir], x + dx[cdir]));
			//���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�, �� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ �����Ѵ�.
			if (map[y + dy[cdir]][x + dx[cdir]]==0) {
				y = y + dy[cdir]; x = x + dx[cdir];
				dir = cdir;
				break;
			}
		}
		//���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ ���ư���.
		if (i == 4) {
			//�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ��쿡��, �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư���.
			if (map[y - dy[dir]][x - dx[dir]] !=1) {
				y -= dy[dir]; x -= dx[dir];
			}
			else {
				break;
			}
			//�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���̸鼭, ���� ������ ���̶� ������ �� �� ���� ��쿡�� �۵��� �����.
		}
		//�κ� û�ұ�� �̹� û�ҵǾ��ִ� ĭ�� �� û������ ������, ���� ����� �� ����.
	}
	cout << clean_room - 1<endl;
}
int main(void) {
	init();
	play();
	return 0;
}


