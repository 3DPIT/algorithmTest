#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 51//배열의 최대 크기
int N, L, R;//배열의 크기, 인구차이L이상, 인구차이 R이하
int SUM; int SIDX;//국경 공유하는 나라의 합과 개수
struct Data {
	int sum, cnt, ret;//dfs에서 나오는 결과값 산출
}dfsNum[NS*NS];
struct Data1 {
	int y, x, cnt;
};
int flag = 0;//인구이동 했는지 파악
int S[NS][NS];// 땅에 입력되는 배열
int ret;//결과값
int visit[NS][NS];//방문 체크
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
void init_input() {//초기화 및 초기 입력
	//초기화
	N = L = R = ret = SUM = SIDX = 0;
	memset(dfsNum, 0, sizeof(dfsNum));
	memset(S, 0, sizeof(S));
	memset(visit, 0, sizeof(visit));
	//초기 입력
	scanf("%d %d %d", &N, &L, &R);//배열의 크기, 도시의차이 이상 이하 값
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &S[i][j]);//배열 초기 입력
		}
	}
}
bool safe(Data1 c) {
	return 0 <= c.y&&c.y < N && 0 <= c.x&&c.x < N;
}
void dfs(int y, int x, int cnt) {

	for (int dir = 0; dir < 4; dir++) {
		Data1 n;
		n.y = y + dy[dir]; n.x = x + dx[dir];
		int iSum = abs(S[y][x] - S[n.y][n.x]);
		if (safe(n) && visit[n.y][n.x] == 0 && L <= iSum && iSum <= R) {
			//범위를 안넘어가고 방문한적 없으며, 차이가 L이상 R이하인경우
			visit[n.y][n.x] = cnt;
			SUM += S[n.y][n.x];
			SIDX++;
			flag = 1;
			dfs(n.y, n.x, cnt);
		}
	}
}
bool DFS() {
	flag = 0;
	memset(dfsNum, 0, sizeof(dfsNum));
	memset(visit, 0, sizeof(visit));
	int cnt = 1;//각 국경 나누기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == 0) {
				SUM = S[i][j];
				SIDX = 1;
				visit[i][j] = cnt;
				dfs(i, j, cnt);//현재 좌표값 y,x,번호,합,합의 개수
				dfsNum[cnt].sum = SUM;
				dfsNum[cnt].cnt = SIDX;
				dfsNum[cnt].ret = SUM / SIDX;
				cnt++;
			}
		}
	}
	if(flag==0)return true;//인구이동 완료
	//인구 이동 결과 저장
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			S[i][j] = dfsNum[visit[i][j]].ret;
		}
	}
	return false;//인구 이동했으면 거짓
}
void humanMove() {
	while (++ret) {
		if (DFS())break;
	}
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		humanMove();//인구 이동 시작
		//출력
		printf("%d\n", ret - 1); //printf("#%d %d\n", tc, ret-1);

	}
	return 0;
}