#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define S 51
int N, M;
char Board[S][S];
int Min = 0x7fffffff;
char realChess[2][S][S] = {
	{//0
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'}
	},
	{//1
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'},
		{'B','W','B','W','B','W','B','W'},
		{'W','B','W','B','W','B','W','B'}
	}
};
struct Chess {
	Chess() {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf(" %1c", &Board[i][j]);
			}
		}
		play();
		printf("%d", Min);
		init();
	}
	void play() {
		for (int i = 0; i < N - 7; i++) {
			for (int j = 0; j < M - 7; j++) {
				int cnt = 0;
				int cnt1 = 0;
				for (int y = i; y < +i + 8; y++) {
					for (int x = j; x < +j + 8; x++) {
						if (safe(y, x)) {
							if (Board[y][x] != realChess[0][y - i][x - j]) {
								cnt++;
							}
							if (Board[y][x] != realChess[1][y - i][x - j]) {
								cnt1++;
							}
						}
						else {
							cnt1 = 0;
							cnt = 0;
						}
					}
				}//
				if (cnt1 <= cnt) {
					if (Min > cnt1)Min = cnt1;
				}
				if (cnt1 > cnt) {
					if (Min > cnt)Min = cnt;
				}

			}
		}//
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
	void init() {
		Min = 0x7fffffff;
		memset(Board, 0, sizeof(Board));
		N = M = 0;
	}
}Chess;
int main(void) {
	return 0;
}