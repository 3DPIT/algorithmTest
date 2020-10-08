#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#define NMSIZE 50
int N, M, T;//y��, x��, �ð�
int map[NMSIZE][NMSIZE];//�ʱ� �Է����� �־����� �迭
int a1y, a1x, a2y, a2x;//����û���� ��ġ
int dy[] = { 0,-1,0,1 };//�̵��� ���� �迭
int dx[] = { 1,0,-1,0 };
int ret;//����� ����
void initAndInput() {//�ʱ�ȭ�� �Է�
	N = M = T = a1y = a1x = a2y = a2x = ret=0;
	memset(map, 0, sizeof(map));
	int flag = 0;
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1) {
				if (!flag) {//���û���� ��ġ ����
					a1y = i; a1x = j;
					flag = 1;//�ϴ�û���� ������ ���ؼ�
				}
				if (flag) {//�ϴ�û���� ��ġ ����
					a2y = i; a2x = j;
				}
			}
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
bool isafe1(int y, int x) {//��ܰ�� Ż�� Ȯ��
	return y == a1y + 1 || x == M || y == -1;
}
bool isafe2(int y, int x) {//�ϴܰ�� Ż�� Ȯ��
	return x == M || y == a2y-1 || y == N;
}
void downClean() {//�ϴ� ��� ����
	int cy = a2y; int cx = a2x; int dir = 3;//����û���� ���� ��ġ�� ���� ����
	while (1) {
		int ny = cy + dy[dir]; int nx = cx + dx[dir];//���� ��ġ üũ
		if (a2y == ny && a2x == nx) {
			map[cy][cx] = 0;
			break;
		}
		if (isafe2(ny, nx)) {//���� ��ȯ ��Ű��
			dir++;
			if (dir == 4)dir = 0;
		}
		else if(map[cy][cx]!=-1){//����û���Ⱑ �ƴ� �����̶��
			map[cy][cx] = map[ny][nx];
			cy = ny; cx = nx;//��ġ �̵���Ű��
		}
		else {
			cy = ny; cx = nx;//��ġ �̵���Ű��
		}
	}
}
void upClean() {//��� ���� ����
	int cy = a1y; int cx = a1x; int dir = 1;//����û���� ���� ��ġ�� ���� ����
	while (1) {
		int ny = cy + dy[dir]; int nx = cx + dx[dir];//���� ��ġ üũ
		if (a1y == ny && a1x == nx) {
			map[cy][cx] = 0;
			break;
		}
		if (isafe1(ny, nx)) {//���� ��ȯ ��Ű��
			dir--;
			if (dir == -1)dir = 3;
		}
		else if (map[cy][cx] != -1) {//����û���Ⱑ �ƴ� �����̶��
			map[cy][cx] = map[ny][nx];
			cy = ny; cx = nx;//��ġ �̵���Ű��
		}
		else {
			cy = ny; cx = nx;
		}
	}
}
void cleanAir() {
	//�̼������� Ȯ��ȴ�.Ȯ���� �̼������� �ִ� ��� ĭ���� ���ÿ� �Ͼ��.
//(r, c)�� �ִ� �̼������� ������ �� �������� Ȯ��ȴ�.
//������ ���⿡ ����û���Ⱑ �ְų�, ĭ�� ������ �� �������δ� Ȯ���� �Ͼ�� �ʴ´�.
//Ȯ��Ǵ� ���� Ar, c / 5�̰� �Ҽ����� ������.
//(r, c)�� ���� �̼������� ���� Ar, c - (Ar, c / 5)��(Ȯ��� ������ ����) �̴�.
//����û���Ⱑ �۵��Ѵ�.
//����û���⿡���� �ٶ��� ���´�.
//���� ����û������ �ٶ��� �ݽð�������� ��ȯ�ϰ�, �Ʒ��� ����û������ �ٶ��� �ð�������� ��ȯ�Ѵ�.
//�ٶ��� �Ҹ� �̼������� �ٶ��� ������ ��� �� ĭ�� �̵��Ѵ�.
//����û���⿡�� �δ� �ٶ��� �̼������� ���� �ٶ��̰�, ����û����� �� �̼������� ��� ��ȭ�ȴ�.
	while (T--) {
		//�̼� ���� Ȯ��
		int cMap[NMSIZE][NMSIZE] = { 0, };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] >=1) {
					int chkCnt = 0;//Ȯ��� ������ ����
					for (int dir = 0; dir < 4; dir++) {
						int ny = i + dy[dir]; int nx = j + dx[dir];
						if (safe(ny, nx) && map[ny][nx] != -1) {
							cMap[ny][nx] += map[i][j] / 5;
							chkCnt++;
						}
					}
					map[i][j] = map[i][j]-((map[i][j] / 5)*chkCnt);
				}
			}//for j
		}//for i

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				map[i][j] += cMap[i][j];//Ȯ�� �Ȱ� ���� �ϱ�
			}
		}
		//��� ����û���� ����

		upClean();
		//�ϴ� ���� û���� ����
		downClean();
	}//while(T--)
	//���� ���� ������ ������
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != -1)ret += map[i][j];
		}
	}
}
int main(void) {
	initAndInput();
	cleanAir();
	printf("%d\n", ret);
	return 0;
}