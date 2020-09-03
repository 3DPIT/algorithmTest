#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define N_SIZE 21
int A[N_SIZE][N_SIZE];//�α��� ���� �迭
int N;//�迭�� ũ��
int ret;//�α����� ������ �ּҰ� ���� ����
int D[N_SIZE][N_SIZE];//������ ������ �迭
bool safe(int y, int x) {
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void P(int a[N_SIZE][N_SIZE]) {//�迭 ����Ȯ��
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
}
void init() {//�ʱ�ȭ �� �Է� �Լ�
	//�ʱ�ȭ
	N = 0; ret = 0x7fffffff;
	memset(A, 0, sizeof(A));
	memset(D, 0, sizeof(D));
	//�Է�
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}
}
void five(int X, int Y, int d1, int d2) {

	//(x, y), (x + 1, y - 1), (x + d1, y - d1)
	vector<int>sx;//x���� ����
	vector<int>ex;//x�� ����
	vector<int>sy;//y���� ����
	vector<int>ey;//y�� ����
	for (int x = X, y = Y; x < X + d1, y > Y - d1; x++, y--) {
		D[x][y] = 5;
		sx.push_back(x);
		sy.push_back(y);//
	}
	//(x, y), (x + 1, y + 1),(x + d2, y + d2)
	for (int x = X, y = Y; x < X + d2, y < Y + d2; x++, y++) {
		D[x][y] = 5;
		ex.push_back(x);
		ey.push_back(y);
	}
	//(x + d1, y - d1), (x + d1 + 1, y - d1 + 1),(x + d1 + d2, y - d1 + d2)
	for (int x = X + d1, y = Y - d1; x <= X + d1 + d2, y <= Y - d1 + d2; x++, y++) {
		D[x][y] = 5;
		sx.push_back(x);
		sy.push_back(y);//
	}
	//x + d2, y + d2), (x + d2 + 1, y + d2 - 1),(x + d2 + d1, y + d2 - d1)
	for (int x = X + d2, y = Y + d2; x <= X + d2 + d1, y >= Y + d2 - d1; x++, y--) {
		D[x][y] = 5;
		ex.push_back(x);
		ey.push_back(y);
	}
	
	for (int i = 0; i < sx.size(); i++) {
		for (int x = sx[i]; x <= ex[i]; x++) {
			for (int y = sy[i]; y <= ey[i]; y++) {
				if(safe(x, y)) {
					D[x][y] = 5;
				}
			}
		}
	}


}
void one(int X, int Y, int d1, int d2) {
	//1�� ���ű� : 1 �� r < x + d1, 1 �� c �� y
	for (int r = 1; r < X + d1; r++) {
		for (int c = 1; c <= Y; c++) {
			if(D[r][c]==0)D[r][c] = 1;
		}
	}
}
void two(int X, int Y, int d1, int d2) {
	//2�� ���ű� : 1 �� r �� x + d2, y < c �� N
	for (int r = 1; r <= X + d2; r++) {
		for (int c = Y + 1; c <= N; c++) {
			if (D[r][c] == 0)D[r][c] = 2;
		}
	}
}
void three(int X, int Y, int d1, int d2) {
	//3�� ���ű� : x + d1 �� r �� N, 1 �� c < y - d1 + d2
	for (int r = X + d1; r <= N; r++) {
		for (int c = 1; c < Y - d1 + d2; c++) {
			if (D[r][c] == 0)D[r][c] = 3;
		}
	}
}
void four(int X, int Y, int d1, int d2) {
	//4�� ���ű� : x + d2 < r �� N, y - d1 + d2 �� c �� N
	for (int r = X + d2 + 1; r <= N; r++) {
		for (int c = Y - d1 + d2; c <= N; c++) {
			if (D[r][c] == 0)D[r][c] = 4;
		}
	}
}
int chkNum5() {
	int chk[6] = { 0, };
	int cnt = 0;//���� 5�� �� �������� Ȯ��
	for (int i =1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (chk[D[i][j]] == 0) {
				chk[D[i][j]] = 1;
				cnt++;
			}
		}
	}
	if (cnt == 5)return 1;
	else return 0;
}
int numCnt() {
	int num[6] = { 0, };
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			num[D[i][j]] += A[i][j];
		}
	}
	int Max = 0x80000000;
	int Min = 0x7fffffff;
	for (int i = 1; i <= 5; i++) {
		Max = Max < num[i] ? num[i] : Max;
		Min = Min > num[i] ? num[i] : Min;
	}
	return ret > (Max - Min) ? (Max - Min) : ret;
}
void PLAY() {
	//��輱 �� ���ű� �����
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			for (int d1 = 1; d1 <= N; d1++) {
				for (int d2 = 1; d2 <= N; d2++) {
					//������(x, y)�� ����� ���� d1, d2�� ���Ѵ�. 
					//(d1, d2 �� 1, 1 �� x < x + d1 + d2 �� N, 1 �� y - d1 < y < y + d2 �� N)
					if (x + d1 + d2 <= N && y - d1 < y&&y + d2 <= N) {
						memset(D, 0, sizeof(D));
						five(x, y, d1, d2);
						one(x, y, d1, d2);
						two(x, y, d1, d2);
						three(x, y, d1, d2);
						four(x, y, d1, d2);
						if (chkNum5()) {
							//�α��� ����ϱ�
							ret =numCnt();
						}
					}
				}//���� d2 ��
			}//���� d1 ��
		}//���� y ��
	}//���� x ��




}


int main(void) {
	int testCase = 1;//�׽�Ʈ���̽� ��
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		PLAY();
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}

	return 0;
}