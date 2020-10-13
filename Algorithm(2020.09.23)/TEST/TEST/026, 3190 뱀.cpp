#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<vector>
using namespace std;
#define NS 101//�迭�� �ִ� ũ��
int N, K, L;//�迭ũ��, ��� ����, ��ΰ���
int ret;//�����
int map[NS][NS];//���� ��� �迭
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ 
	N = K = L = 0;
	ret = 0;
	memset(map, 0, sizeof(map));
	//�ʱ� �Է�
	scanf("%d %d",&N, &K);
	for (int k = 0; k < K; k++) {//��� ��ġ 
		int y, x;
		scanf("%d %d",&y, &x);
		map[y][x] = -1;//��� ����
	}
}
bool safe(int y, int x) {//����
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void gameStart() {
	int y = 1, x = 1, dir = 0, size = 1, tail = 1;//���� ����
	scanf("%d", &L);
	for (int l = 0; l < L; l++) {
		int X; char C;//���ӽ��� �ð����� ���� X��, ���� C-> D������,L����
		scanf("%d %c", &X, &C);
		while(1) {//�ù� ����
			if (ret == X) {//���� ��ȯ�ϴ°�
				if (C == 'D') {//������ ���� ��ȯ
					dir = (++dir) % 4;
				}
				else if(C == 'L') {//���� ���� ��ȯ
					dir = (4+(--dir)) % 4;
				}
				if(l!=L-1)
				break;
			}
			//1. ���� ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.

			int ny = y + dy[dir]; int nx = x + dx[dir];
			if (!safe(ny,nx)||(map[ny][nx]!=0&&map[ny][nx] >= tail-1&&size!=1)) {//������ ��� ��� �� ������ ���
				if (l != L - 1) {//���� ��� ���ֱ�
					for (l++; l < L; l++) {
						scanf("%d %c", &X, &C);
					}
				}
				break;
			}

			//2. ���� �̵��� ĭ�� ����� �ִٸ�, �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
			if (map[ny][nx] == -1) {
				map[ny][nx] = ++ret;//��� �԰�
				size++;
			}
			//3. ���� �̵��� ĭ�� ����� ���ٸ�, �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.��, �����̴� ������ �ʴ´�.
			else if (map[ny][nx] != -1) {
				map[ny][nx] = ++ret;
				tail++;//����ĭ ����ֱ�
			}
			y = ny; x = nx;
		}
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		gameStart();//���� ����
		//���
		printf("%d\n", ret+1);
		//printf("#%d %d\n", tc, ret+1);
	}
	return 0;
}
