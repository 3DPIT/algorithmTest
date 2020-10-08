#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define NSIZE 101
int N;//���簢���� ũ�� 
int square[NSIZE][NSIZE];//�Է� ������
int ret;//�����
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
bool safe(int y, int x) {//���� Ȯ��
	return 0 <= y && y < N && 0 <= x && x < N;
}
struct whiteHoll {
	int y, x;
};
vector<whiteHoll>WH[5];//��Ȧ�� ������ ����
void init() {//�ʱ�ȭ
	N = 0;
	ret = 0x80000000;//�ִ밪 �̱�
	memset(square, 0, sizeof(square));
	memset(WH, 0, sizeof(WH));
}
void gamePlay() {//�ɺ� �˰���
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			if (square[y][x] == 0) {//��� ��ġ ����
				for (int dir = 0; dir < 4; dir++) {
					int ny = y; int nx = x;//��ġ
					int ndir = dir;//����
					int score = 0;//����
					while (1) {
						ny += dy[ndir]; nx += dx[ndir];//��ġ
						if (safe(ny, nx)) {//�簢�� ���ΰ��
							if ((ny==y&&nx==x)||square[ny][nx] == -1) {//��Ȧ ������ Ż�� �ϰ� �̶� ���� �ִ밪 ����
								ret = ret < score ? score : ret;//�ִ밪 ����
								break;
							}
							else if (square[ny][nx] == 1) {//1��쿡 dir ���� ��ȭ
								if (ndir == 0)ndir = 2;
								else if (ndir == 1)ndir = 3;
								else if (ndir == 2)ndir = 1;
								else if (ndir == 3)ndir = 0;
								score++;//���� ����
							}
							else if (square[ny][nx] == 2) {//2��쿡 dir ���� ��ȭ
								if (ndir == 0)ndir = 1;
								else if (ndir == 1)ndir = 3;
								else if (ndir == 2)ndir = 0;
								else if (ndir == 3)ndir = 2;
								score++;//���� ����
							}
							else if (square[ny][nx] == 3) {//3��쿡 dir ���� ��ȭ
								if (ndir == 0)ndir = 3;
								else if (ndir == 1)ndir = 2;
								else if (ndir == 2)ndir = 0;
								else if (ndir == 3)ndir = 1;
								score++;//���� ����
							}
							else if (square[ny][nx] == 4) {//4��쿡 dir ���� ��ȭ
								if (ndir == 0)ndir = 2;
								else if (ndir == 1)ndir = 0;
								else if (ndir == 2)ndir = 3;
								else if (ndir == 3)ndir = 1;
								score++;//���� ����
							}
							else if (square[ny][nx] == 5) {//5��쿡 dir ���� ��ȭ
								if (ndir == 0)ndir = 2;
								else if (ndir == 1)ndir = 3;
								else if (ndir == 2)ndir = 0;
								else if (ndir == 3)ndir = 1;
								score++;//���� ����
							}
							else if (square[ny][nx] >= 6) {//6-10�� ��Ȧ ��쿡 ��ġ ��ȭ��Ű��
								int cy = 0, cx = 0;//������ ��ġ
								for (int i = 0; i <WH[square[ny][nx]-6].size(); i++) {//�ݴ��� ��Ȧ�� ��ġ �̵�
									if (ny == WH[square[ny][nx] - 6][i].y&&ny == WH[square[ny][nx] - 6][i].x)continue;
									else {
										cy = WH[square[ny][nx] - 6][i].y;//��ġ ����
										cx = WH[square[ny][nx] - 6][i].x;
										break;
									}
								}
								ny = cy;
								nx = cx;
							}
							if ((ny == y && nx == x) || square[ny][nx] == -1) {//��Ȧ ������ Ż�� �ϰ� �̶� ���� �ִ밪 ����
								ret = ret < score ? score : ret;//�ִ밪 ����
								break;
							}
						}
						else {//���� �Ѿ��쳪 ���� �ε��� ��� �ݴ�� ���� ��ȭ
							if (ndir == 0) ndir = 2;
							else if (ndir == 1)ndir = 3;
							else if (ndir == 2)ndir = 0;
							else if (ndir == 3)ndir = 1;
							score++;//���� ����
						}

					}//while(1)

				}//for dir
			}
		}//for x
	}//for y
}
int main(void) {
	int T;//�׽�Ʈ���̽�
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {//�Է°� �Է�
			for (int j = 0; j < N; j++) {
				scanf("%d", &square[i][j]);
				if (square[i][j] >= 6) {
					WH[square[i][j] - 6].push_back({ i,j });//��Ȧ ������ ����
				}
			}
		}
		gamePlay();
		printf("#%d %d\n", tc, ret);
	}
}