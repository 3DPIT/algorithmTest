#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define MAP_SIZE 16 //맵최대 사이즈
int N, M, D;//열, 행, 거리
int castleMap[MAP_SIZE][MAP_SIZE];//사용할 맵
int copyCastleMap[MAP_SIZE][MAP_SIZE];//복사할 맵
int Max = 0x80000000;
void print(int pArr[MAP_SIZE][MAP_SIZE]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << pArr[i][j];
		}
		cout << endl;
	}
}
struct Data {
	int y, x;
};
void copy(int carr[MAP_SIZE][MAP_SIZE], int arr[MAP_SIZE][MAP_SIZE]) {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			carr[i][j] = arr[i][j];
		}
	}
}
void downArr() {
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			copyCastleMap[i + 1][j] = copyCastleMap[i][j];//한칸씩 내려가기
		}
	}
	for (int j = 0; j < M; j++) {//제일 윗줄 0으로 초기화 
		copyCastleMap[0][j] = 0;
	}
}
int emermyDie() {
	int enermyNum = 0;
	int MaxDownN = N;
	copy(copyCastleMap, castleMap);
	int cnt = 0;//궁수 3명인지 체크
	while (MaxDownN--) {//적들의 진행최대수
		vector<Data>Die;
		for (int i = 0; i < M; i++) {//궁수 찾기
			if (copyCastleMap[N][i] == 2) {//궁수 찾았으면 죽일 적 찾기
				
				int hunterY = N;// 궁수의 y,x 좌표 
				int hunterX = i;
				int minD = 0x7fffffff;//죽일 적의 거리 최소값
				int minY = 0x7fffffff;
				int minX = 0x7fffffff;				
				for (int y = 0; y < N; y++) {
					for (int x = 0; x < M; x++) {
						if (copyCastleMap[y][x] == 1) {// 적을 찾았으면
							int d = abs(hunterY - y) + abs(hunterX - x);
							//if (d <= D) {
							//	if (minD > d) {//최소범위의 적이면 그때의 y,x 저장하기위함
							//		minD = d;
							//		minY = y;
							//		minX = x;
							//	}
							//	if (minD == d) {
							//		if (minX > x) {
							//			minD = d;
							//			minY = y;
							//			minX = x;
							//		}
							//	}
							//}//
							if (d <= D) {
								if (minD > d || (minD == d && minX > x)) {
									minD = d;
									minY = y;
									minX = x;
								}
							}
						}
					}
				}
				if (minY != 0x7fffffff) {//죽일 적이 있었으면
					Die.push_back({ minY,minX });
				}
				else {
					Die.push_back({ -1,-1 });
				}
			}
		}
		//적죽이기
		for (int i = 0; i < 3; i++) {
			if (Die.size()!=0&&Die[i].y!=-1&&copyCastleMap[Die[i].y][Die[i].x] == 1) {
				copyCastleMap[Die[i].y][Die[i].x] = 0;
				enermyNum++;
			}
		}
		//Die.clear();//적 위치 초기화
		//cout << "죽인 적" << endl;
		//cout << enermyNum << endl;
		//cout << "적 죽인후" << endl;
		//print(copyCastleMap);
		//배열내리기
		downArr();
		//cout << "배열 내린후" << endl;
		//print(copyCastleMap);
	}
	return enermyNum;
}
void dfs(int idx, int d) {
	if (d == 3) {//궁수 위치 선정 후 시뮬 시작

		int num = emermyDie();//현재 위치에서 최대 죽인 적수
		Max = Max < num ? num : Max;//최종 최대죽인수 저장되는 변수
		return;
	}
	for (int i = idx; i < M; i++) {
		castleMap[N][i] = 2;//궁수 위치 잡기
		dfs(i + 1, d + 1);
		castleMap[N][i] = 0;
	}

}
void init() {
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {//맵에 적위치 표시
		for (int j = 0; j < M; j++) {
			scanf("%d", &castleMap[i][j]);
		}
	}
	dfs(0, 0);//궁수위치 선정
}
int main(void) {
	init();
	cout << Max << endl;

}
