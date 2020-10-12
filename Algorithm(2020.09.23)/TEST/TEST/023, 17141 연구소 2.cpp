#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
#define NS 51//연구소의 최대 크기
#define MS 11
int N, M, ret;//연구소의 크기, 바이러스 선정 개수, 결과값 저장 변수
int lab[NS][NS];//연구소 배열
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, cnt;
}virus[MS];
int vIdx;//바이러스 개수
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = vIdx=0;
	ret = 0x7fffffff;//최소값
	memset(lab, 0, sizeof(lab));
	memset(virus, 0, sizeof(virus));
	//초기 입력
	scanf("%d %d", &N, &M);//연구소 크기, 바이러스 개수
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &lab[i][j]);//연구소 상태 입력
			if (lab[i][j] == 2) {
				virus[vIdx].y = i; virus[vIdx].x = j; virus[vIdx].cnt = 0;
				vIdx++;//바이러스 정보 포집
			}
		}
	}
}
bool safe(int y, int x) {//배열의 범위 
	return 0 <= y && y < N && 0 <= x && x < N;
}
//1. M개의 바이러스 dfs를 이용하여 선정
void dfs(int idx, int c) {//바이러스 선정과, 선정한 수
	if (idx == vIdx+1)return;
	if (c == M) {
		queue<Data>q;//바이러스 전파 준비 큐
		int visit[NS][NS] = { 0, };//방문 체크
		for (int i = 0; i < vIdx; i++) {//바이러스 추출
			if (virus[i].cnt == 1) {
				q.push(virus[i]);
				visit[virus[i].y][virus[i].x] = 1;
			}
		}
		//2. BFS를 이용하여 바이러스 전파  cnt는 최대구해놓기
		int cnt = 0;//cnt 큐에서최대값 
		while (!q.empty()){
			Data c = q.front(); q.pop();
			cnt = c.cnt;
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];//다음 좌표
				n.cnt = c.cnt+1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0 && lab[n.y][n.x] != 1) {
					//적정 범위 안에있고 방문한적이 없으며 벽이 아닌경우 푸쉬
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}
		//3. 벽을 제외하고 0 인공간의 경우 있는지 체크하기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (lab[i][j] == 0 && visit[i][j] == 0)return;//이경우 적정한게 아님
			}
		}
		//4. cnt의 최소값 추출하기
		ret = min(ret, cnt-1);
		return;
	}
	virus[idx].cnt = 1;//바이러스 선택
	dfs(idx + 1, c + 1);
	virus[idx].cnt = 0;//바이러스 복귀
	dfs(idx + 1, c);
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		dfs(0, 0);
		if (0x7fffffff == ret)ret = -1;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}