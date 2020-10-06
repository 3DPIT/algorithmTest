#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>	
using namespace std;
#define NSIZE 21
int soil[NSIZE][NSIZE];//집이 위치하는 배열
int N, M;//맵의 크기와 한집당 비용
int ret = 0x80000000;//최대값
void init() {//변수 초기화
	N = M = 0;
	ret = 0x80000000;
	memset(soil, 0, sizeof(soil));
}
void searchHome() {//서비스 집 탐색
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {//집의 위치 입력 ( 집 : 1 )
		for (int j = 0; j < N; j++) {
			scanf("%d", &soil[i][j]);
		}//for j
	}// for i
	for (int cy = 0; cy < N; cy++) {//현재 확인 위치 선정
		for (int cx = 0; cx < N; cx++) {
			int D[NSIZE*NSIZE] = { 0, };//집의 정보 담기
			int maxDistance = 0x80000000;
			for (int hy = 0; hy < N; hy++) {// 집의 위치 
				for (int hx = 0; hx < N; hx++) {
					if (soil[hy][hx] == 1) {//집이라면 거리 측정하기
						int distance = abs(cy - hy) + abs(cx - hx);//거리 공식
						D[distance+1]++;
						maxDistance = max(maxDistance, distance + 1);//최대 거리값
					}
				}//for hx
			}//for hy
			
			//보안회사의 이익(2) = 서비스 제공받는 집들을 통해 얻는 수익(3*5) - 운영 비용(13)
			int home = 0;//집의 수
			for (int k = 1; k <= maxDistance;k++) {
				int manageCost=(k*k)+((k-1)*(k-1));//운영 비용
				//printf("k = %d , manageCost = %d\n", k, manageCost);//운영 비용 확인
				home += D[k];//집의 수
				int serviceHome = 0; 
				serviceHome = M * home;//서비스 제공받는 집들을 통해 얻는 수익
				int securityProfit = serviceHome - manageCost;//보안회사의 이익
				if (securityProfit >=0) {//손해가 아니면 인간의 최대수
 					ret = max(ret, home);//최종 최대의 집의 개수 저장 
				}
			}

		}//for cx
	}//for cy 
}
int main(void) {
	int T;//테스트 케이스 개수
	scanf("%d",&T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		searchHome();
		printf("#%d %d\n", tc, ret);//최종 출력 형식
	}
	return 0;
}