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
	N = L = ret = 0;
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
void print(string num, int idx, int arr[NS]) {
	cout << num << idx << endl;
	if (idx != 100) {
		for (int i = 0; i < N; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	if (idx == 100) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}
	}

}
void makeLoad() {
	for (int i = 0; i < N; i++) {
		int j = 0;
		int loadChk[NS] = { 0, };
		for (j = 0; j < N - 1; j++) {
			if (map[i][j] - map[i][j + 1] == 1) {
				int cLen = 1;
				for (int cj = j + 1; cj <= j + L - 1; cj++) {
					if (map[i][cj] == map[i][cj + 1] && loadChk[cj] == 0 && loadChk[cj + 1] == 0) {
						cLen++;
					}
					else break;
				}
				if (cLen == L) {
					int flag = 0;
					for (int cj = j + 1; cj <= j + L; cj++) {
						//다리 건설 체크
						if (loadChk[cj] == 0)
							loadChk[cj] = 1;
						else {
							flag = 1;
						}
					}
					if (flag == 1)break;
					if (L != 1) {
						j += L;
						j--;
					}
				}
				else break;
			}// 차이가 1인경우//내리막 설치
			else if (map[i][j] - map[i][j + 1] == 0) {
				continue;
			}// 차이가 0인경우// 전진
			else if (map[i][j] - map[i][j + 1] == -1) {
				int cLen = 1;
				for (int cj = j; cj >= j + 2 - L && cj >= 0; cj--) {
					if (map[i][cj] == map[i][cj - 1] &&
						loadChk[cj] == 0 && loadChk[cj - 1] == 0) cLen++;
					else break;
				}

				if (cLen == L) {
					int flag = 0;
					for (int cj = j; cj >= j + 1 - L && cj >= 0; cj--) {
						if (loadChk[cj] == 0)loadChk[cj] = 1;
						else flag = 1;
					}
					if (flag)break;
				}
				else break;
			}// 차이가 -1인경우//오르막 설치
			else break;
		}
		if (j == N - 1) {//도달했으면
			//print("다리건설현황", i, loadChk);
			ret++;
		}
	}
}
int main(void) {
	int T=1;
	//scanf("%d", &T);
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
		//print("맵출력", 100, map[0]);
		makeLoad();
		printf("%d\n", ret);
	}
	return 0;
}