#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using namespace std;
#define NS 101
int N, L, ret;
int map[NS][NS];
void init() {
	N = L = ret=0;
	memset(map, 0, sizeof(map));
}
void rotArr() {
	int cmap[NS][NS];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cmap[i][j] = map[j][N - 1 - i];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = cmap[i][j];
		}
	}
}
void makeLoad() {
	for (int i = 0; i < N-1; i++) {
		int j = 0;
		int loadChk[NS] = { 0, };
		for (j = 0; j < N-1; j++) {
			if (map[i][j] - map[i][j + 1] == 1) {
				int cLen = 1;
				for (int cj = j +1 ; cj <= j + L; cj++) {
					if (map[i][cj] == map[i][cj+1]&&loadChk[cj]==0&&loadChk[cj+1]==0) {
						cLen++;
					}
					else break;
				}
				if (cLen == L) {
					for (int cj = j + 1; cj <= j+1 + L; cj++) {
						//다리 건설 체크
						loadChk[cj] = 1;
					}
					j += L;
					j--;
				}
				else break;
			}// 차이가 1인경우//내리막 설치
			else if (map[i][j] - map[i][j + 1] == 0) {
				continue;
			}// 차이가 0인경우// 전진
			else if (map[i][j] - map[i][j + 1] == -1) {
				int cLen = 1;
				for (int cj = j ; cj >= j + 2 - L&&cj>=0; cj--) {
					if (map[i][cj] == map[i][cj - 1]&&
						loadChk[cj]==0&&loadChk[cj-1]==0) cLen++;
					else break;
				}
				if (cLen == L) {
					for (int cj = j; cj >= j + 1 - L && cj >= 0; cj--) {
						loadChk[cj] = 1;
					}
				}
				else break;
			}// 차이가 -1인경우//오르막 설치
		}
		if (j == N-1) {//도달했으면
			ret++;
		}
	}
}
int main(void) {
	int T;
	scanf("%d", &T);
	for (int ti = 1; ti <= T; ti++) {
		init();
		scanf("%d %d", &N, &L);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		makeLoad();
		rotArr();
		makeLoad();
		printf("#%d %d\n", ti, ret);
	}
	return 0;
}