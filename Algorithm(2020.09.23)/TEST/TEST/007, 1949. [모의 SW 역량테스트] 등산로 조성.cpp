#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define NSIZE 8 //입력으로 주어지는 배열 최대크기
int N, K;//지도 한 변의길이, 최대 공사 가능 깊이
int mountain[NSIZE][NSIZE];//입력으로 주어지는 배열
int ret;//최종 최대값 저장
int maxMT;//최고 봉우리
int maxCnt;//최대 갈수잇는 등산로
int visit[NSIZE][NSIZE];//탐색시 체크할 배열
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
bool safe(int y, int x) {//배열 넘어가는것 체크
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {//초기화
	N = K = 0;
	ret = maxMT=maxCnt = 0x80000000;
	memset(mountain, 0, sizeof(mountain));
	memset(visit, 0, sizeof(visit));
}
void dfs(int y, int x,int cnt) {//탐색 시작
	
	for (int dir = 0; dir < 4; dir++) {
		if (safe(y+dy[dir],x+dx[dir])&&visit[y+dy[dir]][x+dx[dir]]==0&&mountain[y][x] > mountain[y + dy[dir]][x + dx[dir]]) {//봉오리 낮은곳 찾기
			//범위 안넘어가거나 방문한적없거나 현재보다 낮은경우
			visit[y + dy[dir]][x + dx[dir]] = 1;
			maxCnt = max(maxCnt, cnt+1);
			dfs(y + dy[dir], x + dx[dir],cnt+1);
			visit[y + dy[dir]][x + dx[dir]] = 0;
		}
	}
}
void hiking() {//입력하고 알고리즘 시작
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++) {//입력하면서
		for (int j = 0; j < N; j++) {
			scanf("%d", &mountain[i][j]);
			if (maxMT < mountain[i][j]) {
				maxMT = max(maxMT, mountain[i][j]);//최대값 저장
			}
		}
	}
	for (int cy = 0; cy < N; cy++) {
		for (int cx = 0; cx < N; cx++) {
			if (mountain[cy][cx] == maxMT) {//최고 봉우리 찾기
				for (int y = 0; y < N; y++) {
					for (int x = 0; x < N; x++) {
						
						for (int k = 0; k <= K; k++) {//봉우리 줄여서 탐색하기
							memset(visit, 0, sizeof(visit));//방문 배열 초기화
							mountain[y][x] -= k;//봉우리 크기 1씩 줄이기
							dfs(cy, cx,1);
							ret = max(ret, maxCnt);
							mountain[y][x] += k;//다시 복구하기
						}//for k

					}//for x
				}//for y
			}
		}//for cx
	}//for cy
}
int main(int argc, char** argv)
{
	int T;
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case)
	{
		init();
		hiking();//등산 시작
		printf("#%d %d\n", test_case, ret);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}