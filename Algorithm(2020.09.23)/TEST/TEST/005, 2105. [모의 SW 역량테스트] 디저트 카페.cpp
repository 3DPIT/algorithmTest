#include<stdio.h>
#include<iostream>
#include<string.h>
#include<iostream>
using namespace std;
#define NSIZE 21
#define FOODSIZE 101
//�밡�� ���� �迭
int dy[] = { 1,1,-1,-1 };
int dx[] = { 1,-1,-1,1 };
int input[NSIZE][NSIZE];//�Է����� �־����� �� ���� �迭
int num[FOODSIZE];//����Ʈ üũ�ϴ� �迭
int N, T;//�迭�� ũ��� �׽�Ʈ ���̽�
int ret;//����� 
bool safe(int y, int x) {//���� üũ �Լ�
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	//�ʱ�ȭ
	memset(input, 0, sizeof(input));
	memset(num, 0, sizeof(num));
	N = 0;
	ret = 0x80000000;//�ִ밪
	//�Է�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	return;
}
void play() {//���� ������ ���� �Լ�
	int visit[NSIZE][NSIZE] = { 0, };
	for (int y = 0; y < N; y++) {//Ž������
		for (int x = 0; x < N; x++) {
			//�밢�� �簢���� ���� ����

			for (int a = 1; a <= N; a++) {
				for (int b = 1; b <= N; b++) {
					int flag = 0;//Ż�� ���� ����
					int cnt = 0;//����Ʈ ������ ���� ����
					memset(num, 0, sizeof(num));
					memset(visit, 0, sizeof(visit));//üũȮ�� �迭 ����������

					cnt = 0;//����Ʈ ������ ���� ����
					int cy = y, cx = x;//���� ��ǥ��
					for (int dir = 0; dir < 4; dir++) {
						if (dir == 0 || dir == 2) {//�����ʴ밢�� �Ʒ�, ���� �밢�� ��
							for (int i = 0; i < a; i++) {
								int ny = cy + dy[dir]; int nx = cx + dx[dir];//���� ��ġ
								if (!num[input[ny][nx]] && safe(ny, nx)) {
									visit[ny][nx] = 1;
									num[input[ny][nx]] = 1;//�ߺ� üũ
									cy = ny; cx = nx;//��ġ �ѱ��
									cnt++;//����Ʈ ����
								}
								else {//����ų� �ߺ��ΰ��
									flag = 1;
									break;
								}
							}
						}
						else {//���ʴ밢�� �Ʒ�, ������ �밢�� ��
							for (int j = 0; j < b; j++) {
								int ny = cy + dy[dir]; int nx = cx + dx[dir];//���� ��ġ
								if (!num[input[ny][nx]] && safe(ny, nx)) {
									visit[ny][nx] = 1;
									num[input[ny][nx]] = 1;//�ߺ� üũ
									cy = ny; cx = nx;//��ġ �ѱ��
									cnt++;//����Ʈ ����
								}
								else {
									flag = 1;
									break;
								}
							}
						}
						if (dir == 3 && flag == 0 && cnt != 0) {

										//cout << endl;
										//for (int ii = 0; ii < N; ii++) {
										//	for (int jj = 0; jj < N; jj++) {
										//		printf("%2d", visit[ii][jj]);
										//	}
										//	cout << endl;
										//}
							ret = ret < cnt ? cnt : ret;
						}
					}
				}
			}

		}
	}
	if (ret == 0x80000000)ret = -1;
}
int main(void) {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}