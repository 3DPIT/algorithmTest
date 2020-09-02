#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define N_SIZE 13
struct Data {
	int y,x, dir, num;
}H[11];
int dy[] = {0,0,0,-1,1 };//���� 
int dx[] = {0,1,-1,0,0 };
int ret=-1;//������
int N, K;//�迭ũ��, ���� ����
int input[N_SIZE][N_SIZE];//�Է����� ������ ��
vector<Data>horse[N_SIZE][N_SIZE];//���� ��������ִ� �迭
bool safe(int y, int x) {//���� Ȯ��
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	//�ʱ�ȭ
	N = K = 0;
	ret = -1;
	memset(input, 0, sizeof(input));
	memset(horse, 0, sizeof(horse));
	memset(H, 0, sizeof(H));
	//�Է�
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	for (int k = 0; k < K; k++) {
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		horse[y-1][x-1].push_back({y-1,x-1,dir,k + 1});//���� ������ ����
		H[k + 1].y = y-1; H[k + 1].x = x-1; H[k + 1].dir = dir; H[k + 1].num = k + 1;
		//y,x,dir,num �Է�
	}
}
int white(int y, int x, int dir, int num,int ny,int nx) {
	int size = horse[y][x].size();//�������� ���� ��
	for (int i = 0; i < size; i++) {//�̵� ������ �� �ø���
		H[horse[y][x][i].num].y = ny; H[horse[y][x][i].num].x = nx;//��ġ �ֽ�ȭ
		horse[ny][nx].push_back({ ny,nx,horse[y][x][i].dir,horse[y][x][i].num });
	}
	while (horse[y][x].size() != 0) {
		horse[y][x].pop_back();
	}//������ �ʱ�ȭ
	return 1;
}
int red(int y, int x, int dir, int num, int ny, int nx) {
	int size = horse[y][x].size();//�������� ���� ��
	for (int i = size-1; i >=0; i--) {//�̵� ������ �� �ø���
		H[horse[y][x][i].num].y = ny; H[horse[y][x][i].num].x = nx;//��ġ �ֽ�ȭ
		horse[ny][nx].push_back({ ny,nx,horse[y][x][i].dir,horse[y][x][i].num });
	}
	while (horse[y][x].size() != 0) {
		horse[y][x].pop_back();
	}//������ �ʱ�ȭ
	return 1;
}
int blue(int y, int x, int dir, int num, int ny, int nx) {
	if (1 == dir)dir = 2;
	else if (2 == dir)dir = 1;
	else if (3 == dir)dir = 4;
	else if (4 == dir)dir = 3;
	H[num].dir = dir;
	horse[y][x][0].dir = dir;
	if (safe(y + dy[dir], x + dx[dir])) {//����� ���� ����
		if (input[y + dy[dir]][x + dx[dir]] == 0) {
			white(y, x, dir, num, y + dy[dir], x + dx[dir]);
		}
		if (input[y + dy[dir]][x + dx[dir]] == 1) {
			red(y, x, dir, num, y + dy[dir], x + dx[dir]);
			}
	}
	return 1;
}

void gameStart() {
	int Time = 0;
	int Flag = 0;//Ȯ��
	while (1) {
		Time++;
		if (Time == 1001)break;
		for (int i = 1; i <= K; i++) {//�� �˻�
			int y, x, dir;
			y = H[i].y; x = H[i].x; dir = H[i].dir;//i ���� ����
			if (horse[y][x][0].num != i)continue;
			int ny = y + dy[dir]; int nx = x + dx[dir];
			if (!safe(ny, nx) || input[ny][nx] == 2) {//blue
				blue(y, x, dir, i, ny, nx);
	
			}
			if (safe(ny, nx) && input[ny][nx] == 0) {//white
				white(y, x, dir, i, ny, nx); 
	
			}
			if (safe(ny, nx) && input[ny][nx] == 1) {//red
				red(y, x, dir, i, ny, nx);

			}
		}//1�� ���� ��
		if (Flag)break;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (horse[i][j].size() >= 4) {
					ret = Time;
					return;
				}
			}
		}
	}//1�� ���� ��
	if (Flag) ret =  Time;//4�� ž�ϼ��� 
	else ret = -1;
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		gameStart();

		//���
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}