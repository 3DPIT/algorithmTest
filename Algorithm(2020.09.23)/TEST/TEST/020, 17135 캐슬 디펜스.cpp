#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
#define NMS 16//가로 세로 최대 크기
int N, M, D;//가로, 세로, 거리
int C[NMS+1][NMS];//캐슬
int ret;//결과값 저장
struct Data {
	int y, x;
};
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = D = 0;
	ret = 0x80000000;//최대값
	//초기 입력
	scanf("%d %d %d", &N, &M, &D);//가로 , 세로, 거리 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &C[i][j]);//배열 적의 정보 입력
		}
	}
}
void copy(int c[NMS][NMS], int cc[NMS][NMS]) {//배열 복사
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			c[i][j] = cc[i][j];
		}
	}
}
void downEnemy() {//적 진군 하기
	for (int y = N - 1; y >= 1; y--) {
		for (int x = 0; x < M; x++) {
			C[y][x] = C[y - 1][x];//한칸 내리기
		}
	}
	for (int x = 0; x < M; x++) {//윗칸 비워주기
		C[0][x] = 0;
	}
}

//1. 궁수 위치 찾기
void dfs(int idx, int cnt) {
	if (idx == M+1)return;
	if (cnt == 3) {//궁수 위치 선정 완료
		int cC[NMS][NMS] = { 0, };//복사 배열
		copy(cC, C);//배열 백업
		int enemy = 0;//죽은 적의 수
		Data sniper[3]; int sIdx = 0;
		for (int j = 0; j < M; j++) {
			if (C[N][j] == 1) {//스나이퍼 위치 저장
				sniper[sIdx].y = N; sniper[sIdx++].x = j;
			}
		}
		for (int time = 0; time < N; time++) {//적이 진군하는 수
			queue<Data>enemyDie;//죽을 적 저장
			for (int s = 0; s < sIdx; s++) {//스나이퍼 한명씩 적 저격하기
				int minD = 0x7fffffff; int minY = 0x7fffffff; int minX = 0x7fffffff;//최소 거리를 가지는 좌표

				for (int y = N - 1; y >= 0; y--) {
					for (int x = 0; x < M; x++) {
						if (C[y][x] != 0) {
							//2. D안에 들어오는 왼쪽 끝에 있는 적찾기
							int distance = abs(y - sniper[s].y) + abs(x - sniper[s].x);
							if (distance <= D) {//범위 안에 있는거라면 찾는거 성공
								if (minD >=distance){
									if (minD == distance&&minX>x) {
										minY = y; minX = x;
									}
									else if(minD>distance){
										minD = distance;
										minY = y; minX = x;
									}
								}
							}
						}
					}
				}
				if (minD != 0x7fffffff&&minY!=0x7fffffff&&minX!=0x7fffffff) {
					enemyDie.push({ minY, minX });
				}
			}
			//3. 시야에 들어온 적 죽이기
			while (!enemyDie.empty()) {
				Data c = enemyDie.front(); enemyDie.pop();
				if (1 == C[c.y][c.x]) {//죽을 적이면 죽이고 cnt ++
					C[c.y][c.x] = 0; enemy++;
				}
			}
			//4. 배열 내리기
			downEnemy();
		}
		// 5. 적들이 다 내려왔으면 죽인 적의 최대값 갱신하기
		copy(C, cC);//배열 복원
		ret = max(ret, enemy);//최대값 산출
		return;
	}
	C[N][idx] = 1;
	dfs(idx + 1, cnt + 1);//궁수 뽑은 경우
	C[N][idx] = 0;
	dfs(idx + 1, cnt);//궁수 안뽑은 경우

}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);//테스트 케이스 입력
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		dfs(0, 0);
		//출력
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}