#include<stdio.h>
#include<string.h>
using namespace std;
#define NSIZE 101 //�� �ִ�ũ��+1
int input[NSIZE][NSIZE];//����� �� ��ġ ����
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, X,K;//ũ��, ��, �������
char C;//����
int ret = 0; // �����
void init() {
	N = X = 0; C = NULL;
	memset(input, 0, sizeof(input));
	scanf("%d", &N);
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {//��� ��ġ
		int y, x;
		scanf("%d %d", &y, &x);
		input[y][x] = -1;//��� ��ġ �Է�
	}
	scanf("%d", &X);
}
bool iSafe(int y, int x) {
	return y < 1 || y>N || x<1 || x>N;
}
void playGame() {
	int xTime = 0;
	int y = 1, x = 1,dir=0;
	int size = 1;
	ret = 1;
	input[y][x] = 1;
	for (int it = 0; it < X; it++) {
		scanf("%d %c", &xTime,&C);
		while (1) {
			if (ret == xTime+1) {//���� ��ȯ��
				if (C == 'D')dir++;//������ ��ȯ
				if (C == 'L')dir--;//���� ��ȯ
				if (dir == 4)dir = 0;
				else if (dir == -1)dir = 3;
				if(it!=X-1)break;// �Է��� ������ ��� �Ϸ�Ǹ� �ȵǹǷ�
			}
			int tail = ret - size;
			if (input[y][x] == -1) {//��� �Ծ�����
				size++;
			}
			else if ((size != 1 && input[y][x] >=tail) || iSafe(y, x)) {//������ ���
				while (it < X - 1) {//�Է��� ������ ���� ��� �Է� ��Ű��
					scanf("%d %c", &xTime, &C);
					it++;
				}
				break;//���� ����
			}
			input[y][x]=ret++;//�ʿ� ���
			y += dy[dir];
			x += dx[dir];

		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		playGame();
		//printf("#%d %d\n", tc, ret-1);
		printf("%d\n", ret-1);
	}
	return 0;
}
