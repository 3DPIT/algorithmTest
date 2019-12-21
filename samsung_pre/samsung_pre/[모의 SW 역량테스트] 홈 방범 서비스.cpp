#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define NS 21
int kArr[NS * 2 - 1];
int input[NS][NS];
int N,M;
int houseMax = 0x80000000;
void houseSafe() {
	for (int ys = 0; ys < N; ys++) {
		for (int xs = 0; xs < N; xs++) {
			memset(kArr, 0, sizeof(kArr));
			for (int ye = 0; ye < N; ye++) {
				for (int xe = 0; xe < N;xe++) {
					if (input[ye][xe] == 1) {
						int k = abs(ys - ye) + abs(xs - xe)+1;
						kArr[k]++;
					}
				}
			}
			int houseCnt=0;
			// 계산해봅시다.
			for (int k = 1; k <= N * 2 - 1; k++) {
				houseCnt = kArr[k];
				int cost = k * k + (k - 1)*(k - 1);
				if (((M*houseCnt) - cost) >= 0) {
					houseMax = houseMax < houseCnt ? houseCnt : houseMax;
				}
			}
		}
	}
}
void init() {
	houseMax = 0x80000000;
	cin >> N>>M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input[i][j];
		}
	}
	houseSafe();
}
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		cout << '#' << tc << " " << houseMax << endl;
	}

	return 0;
}