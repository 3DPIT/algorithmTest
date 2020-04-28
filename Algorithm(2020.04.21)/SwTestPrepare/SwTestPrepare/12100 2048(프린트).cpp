#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define NS 21
int N, ret;
int map[NS][NS];
int Max;
struct BoardGame {
	BoardGame() {
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		dfs(0);
		printf("%d\n", Max);
	}
	void init() {
		ret = N = 0;
		Max = 0x80000000;
		memset(map, 0, sizeof(map));
	}
	void copy(int map[NS][NS], int cmap[NS][NS]) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cmap[i][j] = map[i][j];
			}
		}
	}
	void arrRot() {
		int cmap[NS][NS] = { 0, };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cmap[i][j] = map[j][N-1 - i];
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				map[i][j] = cmap[i][j];
			}
		}
	}
	int numMax() {
		int mMax = 0x80000000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				mMax = mMax < map[i][j] ? map[i][j] : mMax;
			}
		}
		return mMax;
	}
	void downArr() {
		queue<int>q;
		for (int j = 0; j < N; j++) {// 맵 내리기
			for (int i = N-1; i >=0; i--) {
				if (map[i][j] != 0) {
					q.push(map[i][j]);
					map[i][j] = 0;
				}
			}
			for (int i = N - 1; q.size() != 0; i--) {
				map[i][j] = q.front();
					q.pop();
				}
		}
		//print("맵내리고 출력", 0);
		for (int j = 0; j < N; j++) {// 맵 내리기
			for (int i = N - 1; i >= 1; i--) {
				if (map[i][j] == map[i - 1][j] && map[i][j] != 0) {
					map[i][j] += map[i - 1][j];
					map[i - 1][j] = 0;
				}
			}
		}
		//print("맵 더하고 출력", 0);
		for (int j = 0; j < N; j++) {// 맵 내리기
			for (int i = N - 1; i >= 0; i--) {
				if (map[i][j] != 0) {
					q.push(map[i][j]);
					map[i][j] = 0;
				}
			}
			for (int i = N - 1; q.size()!=0; i--) {
				map[i][j] = q.front();
				q.pop();
			}
		}
		//print("맵내리고 출력", 0);

	}
	void dfs(int idx) {
		if (idx == 4) {
			print("맵출력fin", 0);
			ret = numMax();//함수 - 맵최대값 찾고
			Max = Max < ret ? ret : Max;//최대값 최신화
			return;
		}
		int cmap[NS][NS] = { 0, };
		copy(map, cmap);//함수 - 카피
		downArr();//함수 - 아래로 내리기
		print("맵출력", 0);
		dfs(idx + 1);
		copy(cmap, map);//함수 - 복원

		arrRot();//함수 - 회전
		print("맵회전출력", 0);
		copy(map, cmap);//함수 - 카피
		downArr();//함수 - 아래로 내리기
		print("맵출력", 0);
		dfs(idx + 1);
		copy(cmap, map);//함수 - 복원

		arrRot();//함수 - 회전
		copy(map, cmap);//함수 - 카피
		print("맵회전출력", 0);
		downArr();//함수 - 아래로 내리기
		print("맵출력", 0);
		dfs(idx + 1);
		copy(cmap, map);//함수 - 복원

		arrRot();//함수 - 회전
		print("맵회전출력", 0);
		copy(map, cmap);//함수 - 카피
		downArr();//함수 - 아래로 내리기
		print("맵출력", 0);
		dfs(idx + 1);
		copy(cmap, map);//함수 - 복원
	}
	void print(string name, int num) {
		cout << name << endl;
		if (num == 0) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					printf("%3d", map[i][j]);
				}
				cout << endl;
			}
		}
	}

}BoardGame;

int main(void) {

	return 0;
}