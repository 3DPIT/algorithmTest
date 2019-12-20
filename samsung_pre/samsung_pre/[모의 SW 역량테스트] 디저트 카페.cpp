#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define NS 21
int N;
int input[NS][NS];
int cnt;
int ret = 0x80000000;
int dy[] = { -1,1,1,-1};
int dx[] = { -1,-1,1,1};
bool safe(int y, int x) {
	if (0 <= y && y < N && 0 <= x && x < N) return true;
	else return false;
}
bool chk(int rotY,int rotX,int sy,int sx) {
	int numFood[101] = { 0, };// 음식 중복체크//
	cnt = 0;//먹은 디저트수
	int y = sy; int x = sx;
	for (int dir = 0; dir < 4; dir++) {
		if (dir == 0 || dir == 2) {
			for (int i = 0; i < rotY; i++) {
				y += dy[dir]; x += dx[dir];
				if(safe(y,x)&&numFood[input[y][x]]==0){
					numFood[input[y][x]] = 1;
					cnt++;
				}
				else return false;
			}
		}
		else {
			for (int i = 0; i < rotX; i++) {
				y += dy[dir]; x += dx[dir];
				if (safe(y, x) && numFood[input[y][x]] == 0) {
					numFood[input[y][x]] = 1;
					cnt++;
				}
				else return false;
			}
		}
	}
	return true;
}
void eatFood() {
	for (int rotY = 1; rotY <= N - 1; rotY++) {
		for (int rotX = 1; rotX <= N - 1; rotX++) {
			for (int y = 0; y < N; y++) {
				for (int x = 0; x < N; x++) {
					if (chk(rotY,rotX,y,x)) {
						ret = ret < cnt ? cnt : ret;
					}
				}
			}
		}
	}
}
void init() {
	ret = 0x80000000;
	memset(input, 0, sizeof(input));
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input[i][j];
		}
	}
	eatFood();
}
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		if (ret == 0x80000000)ret = -1;
		cout << '#' << tc << " " << ret << endl;
	}
	return 0;
}