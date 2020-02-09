#include<stdio.h>
#include<string.h>
#include<vector>
#include<iostream>
using namespace std;
#define NS 21
int N;
int A[NS][NS];
int chk[NS][NS];

int flag;
struct Data {
	int y, x;
};
void areaWrite(int y, int x, int d1, int d2) {// 성공 문제
	flag = 0;
	memset(chk, 0, sizeof(chk));
	vector<Data>v;
	vector<Data>v1;
	//one
	for (int i = y, j = x; i <= y + d1 && j >= x - d1; i++, j--) {
		if (i<1 || i>N || j<1 || j>N) {
			flag = 1; return;
		}
		v.push_back({ i,j });
		chk[i][j] = 5;
	}
	//three
	for (int i = y + d1 + 1, j = x - d1 + 1; i <= y + d1 + d2 && j <= x - d1 + d2; i++, j++) {
		if (i<1 || i>N || j<1 || j>N) {
			flag = 1; return;
		}
		v.push_back({ i,j });
		chk[i][j] = 5;
	}
	if (flag == 1)return;
	if (flag == 1)return;
	//two
	for (int i = y, j = x; i <= y + d2 && j <= x + d2; i++, j++) {
		if (i<1 || i>N || j<1 || j>N) {
			flag = 1; return;
		}
		v1.push_back({ i,j });
		chk[i][j] = 5;
	}
	if (flag == 1)return;

	//four
	for (int i = y + d2 + 1, j = x + d2 - 1; i <= y + d2 + d1 && j >= x + d2 - d1; i++, j--) {
		if (i<1 || i>N || j<1 || j>N) {
			flag = 1; return;
		}
		v1.push_back({ i,j });
		chk[i][j] = 5;
	}

	for (int i = 0; i < v.size(); i++) {
		for (int ii = v[i].y; ii <= v1[i].y; ii++) {
			for (int jj = v[i].x; jj <= v1[i].x; jj++) {
				chk[ii][jj] = 5;
			}
		}
	}
}
int flag2 = 0;
void fourArea(int y, int x, int d1, int d2) {
	flag2 = 0;
	for (int i = 1; i < y + d1; i++) {
		for (int j = 1; j <= x; j++) {
			if (chk[i][j] == 0)
				chk[i][j] = 1;
			if (flag2 == 0)
				flag2++;
		}
	}
	for (int i = 1; i <= y + d2; i++) {
		for (int j = x + 1; j <= N; j++) {
			if (chk[i][j] == 0)
				chk[i][j] = 2;
			if (flag2 == 1)
				flag2++;
		}
	}
	for (int i = y + d1; i <= N; i++) {
		for (int j = 1; j < x - d1 + d2; j++) {
			if (chk[i][j] == 0)
				chk[i][j] = 3;
			if (flag2 == 2)
				flag2++;
		}
	}
	for (int i = y + d2 + 1; i <= N; i++) {
		for (int j = x - d1 + d2; j <= N; j++) {
			if (chk[i][j] == 0)
				chk[i][j] = 4;
			if (flag2 == 3)
				flag2++;
		}
	}
}void search() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (chk[y][x] == 0) {

			}

		}
	}
}
int Min = 0x7fffffff;
void sparateArea() {

	for (int d1 = 1; d1 <= N; d1++) {
		for (int d2 = 1; d2 <= N; d2++) {
			for (int y = 1; y <= N; y++) {
				for (int x = 1; x <= N; x++) {
					areaWrite(y, x, d1, d2);
					if (flag == 1)continue;
					search();
					fourArea(y, x, d1, d2);
					if (flag2 != 4)continue;
					int sum[6] = { 0, };
					for (int i = 1; i <= N; i++) {
						for (int j = 1; j <= N; j++) {
							sum[chk[i][j]] += A[i][j];
							// printf("%2d", chk[i][j]);
						}
						//  printf("\n");
					}
					// printf("\n");
					int max = 0x80000000; int min = 0x7fffffff;

					for (int m = 1; m <= 5; m++) {
						if (max < sum[m])max = sum[m];
						if (min > sum[m])min = sum[m];
					}
					if (Min > max - min)Min = max - min;
				}
			}
		}
	}
}
void init() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	sparateArea();
	cout << Min << endl;
}
int main(void) {
	init();
	return 0;
}