#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define S 22
int N;
int input[S][S];
int chk[S][S];
//int x, y, d1, d2;
int ret = 0x7fffffff;
struct Data {
	int x, y;
};
vector<Data>v1;
vector<Data>v2;
struct elect2 {
	elect2() {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &input[i][j]);
			}
		}

				for (int d1 = 1; d1 <= N; d1++) {
					for (int d2 = 1; d2 <= N; d2++) {
						for (int x = 1; x <= N; x++) {
							for (int y = 1; y <= N; y++) {
						//x = 2, y = 4, d1 = 2, d2 = 2;
						memset(chk, 0, sizeof(chk));
						fiveLine(x, y, d1, d2);
						fiveMake();
						otherSelect(x,y,d1,d2);
						clac();
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	void clac() {
		int num[6] = { 0, };
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				num[chk[i][j]] += input[i][j];
			}
		}
		int min = 0x7fffffff; int max = 0x80000000;
		for (int i = 0; i <=5; i++) {
			if (i == 0 & num[i] != 0)return;
			if (i!=0&&num[i] == 0)return;
		}
		for (int i = 1; i <= 5; i++) {
			if (min > num[i])min = num[i];
			if (max < num[i])max = num[i];
		}
		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= N; j++) {
		//		cout << chk[i][j];
		//	}
		//	cout << endl;
		//}
		//cout << max - min << endl;
		if (ret > max - min)ret = max - min;
	}
	void init() {
		N = 0;
		ret = 0x7fffffff;
		memset(input, 0, sizeof(input));
		memset(chk, 0, sizeof(chk));
	}
	void memsetArr(int Arr[S][S]) {
		memset(Arr, 0, sizeof(Arr));
	}
	void fiveLine(int x, int y, int d1, int d2) {
		int cx = x, cy = y, cd1 = d1, cd2 = d2;
		//1. (x, y), (x+1, y-1), ..., (x+d1, y-d1)
		for (; cx < x + cd1, cy > y - cd1; cx++, cy--) {
			v1.push_back({ cx, cy });
		}
		cx = x, cy = y;
		//2. (x, y), (x+1, y+1), ..., (x+d2, y+d2)
		for (; cx < x + cd2, cy < y + cd2; cx++, cy++) {
			v2.push_back({ cx, cy });
		}
		cx = x + d1, cy = y - d1;
		//3. (x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
		for (; cx <= x + cd1 + cd2, cy <= y - cd1 + cd2; cx++, cy++) {
			v1.push_back({ cx, cy });
		}
		cx = x + cd2, cy = y + cd2;
		//4. (x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
		for (; cx <= x + cd2 + cd1, cy >= y + cd2 - cd1; cx++, cy--) {
			v2.push_back({ cx, cy });
		}
	}
	void fiveMake() {

		for (int i = 0; i < v1.size(); i++) {
			for (int x = v1[i].x; x <= v2[i].x; x++) {
				for (int y = v1[i].y; y <= v2[i].y; y++) {
					if (safe(x, y))
					chk[x][y] = 5;
				}
			}

		}
		v1.clear();
		v2.clear();
	}
	void otherSelect(int x, int y, int d1, int d2) {
		oneSelect(x, y, d1, d2);
		twoSelect(x, y, d1, d2);
		threeSelect(x, y, d1, d2);
		fourSelect(x, y, d1, d2);
	}
	void oneSelect(int x, int y, int d1, int d2) {
		for (int i = 1; i < x + d1; i++) {
			for (int j = 1; j <= y; j++) {
				if(chk[i][j]!=5&&safe(i,j))
				chk[i][j] = 1;
			}
		}
	}
	void twoSelect(int x, int y, int d1, int d2) {
		for (int i = 1; i <= x + d2; i++) {
			for (int j = y+1; j <= N; j++) {
				if(chk[i][j]!=5&&safe(i,j))
				chk[i][j] = 2;
			}
		}
	}
	void threeSelect(int x, int y, int d1, int d2) {
		for (int i = x+d1; i <= N; i++) {
			for (int j = 1; j < y - d1+d2; j++) {
				if(chk[i][j]!=5&&safe(i,j))
				chk[i][j] = 3;
			}
		}
	}
	void fourSelect(int x, int y, int d1, int d2) {
		for (int i = x+d2+1; i <= N; i++) {
			for (int j = y - d1 + d2; j <=N ; j++) {
				if(chk[i][j]!=5&&safe(i,j))
				chk[i][j] = 4;
			}
		}
	}
	bool safe(int x, int y) {
		return 1 <= x && x <= N && 1 <= y && y <= N;
	}
}elect;
int main(void) {
	return 0;
}