#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 101//배열 최대 크기
int N;//배열의 크기
int ret;//결과 값
int map[NS][NS];//드래곤 커브 확인 배열
int dy[] = { 0,-1,0,1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, dir, gen;//좌표, 방향, 세대
};
vector<Data>dragon;
void init_input(){//초기화 및 초기 입력
	//초기화
	N = ret = 0;
	memset(map, 0, sizeof(map));
	dragon.clear();
	//초기 입력
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		Data c;
		scanf("%d %d %d %d", &c.x, &c.y, &c.dir, &c.gen);
		dragon.push_back(c);//드래곤 정보 저장
	}
}
void dragonLevel() {//드래곤 커브 입력
	for (int i = 0; i < dragon.size(); i++) {
		//1. 드래곤 세대 경로 저장
		vector<int>dragonD;//드래곤 세대 저장
		dragonD.push_back(dragon[i].dir);
		for (int g = 1; g<=dragon[i].gen; g++) {
			for (int D = dragonD.size() - 1; D >= 0; D--) {
				dragonD.push_back((dragonD[D]+1) % 4);//경로 저장
			}
		}
		//2. 드래곤 세대 경로 배열 저장
		int y = dragon[i].y; int x = dragon[i].x;
		for (int di = 0; di < dragonD.size(); di++) {
			map[y][x] = 1;
			Data n; n.y = y + dy[dragonD[di]]; n.x = x + dx[dragonD[di]];
			map[n.y][n.x] = 1;
			y = n.y; x = n.x;
		}
	}
	//3. 확인
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1) {
				ret++;
			}
		}
	}
}
int main(void) {
	int T = 1;//테스트 케이스
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		dragonLevel();//드래곤 성장
		//출력
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}