#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
#define N_SIZE 51
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int N, M;//연구소 크기, 바이러스 개수
int virusMap[N_SIZE][N_SIZE];//입력되는 맵
int ret;//최종값 저장
vector<int>D;//바이러스 선정 백터
struct Data {
	int y, x,cnt;
};
vector<Data>v;//바이러스 검출
bool safe(int y, int x) {//범위 체크 함수
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {
	N = M = 0;
	ret = 0x7fffffff;//초기화
	memset(virusMap, 0, sizeof(virusMap));
	D.clear();
	v.clear();
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &virusMap[i][j]);// 입력 
			if (virusMap[i][j] == 2) {//바이러스 검출
				v.push_back({ i,j,0});
			}
		}
	}
}

void dfs(int idx, int d) {
	if (idx > v.size())return;// 범위 넘어가는것 체크
	if (d == M) {// 바이러스 검사 시작
		int cnt = 0x80000000;//최대값 찾기
		queue<Data>q;
		int visit[N_SIZE][N_SIZE] = { 0, };//방문 체크
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < M; i++) {
			int y = v[D[i]].y; int x = v[D[i]].x;
			q.push({ y,x,1 });
			visit[y][x] = 1;
		}
		while (!q.empty()) {// 바이러스 공격 개시
			Data c = q.front(); q.pop();
		//if(virusMap[c.y][c.x]==0)  cnt = cnt < c.cnt ? c.cnt : cnt;// 최대값 산출
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (visit[n.y][n.x] == 0 && safe(n.y, n.x) && virusMap[n.y][n.x] != 1) {
						visit[n.y][n.x] = n.cnt; //방문체크
						q.push(n);
				}
			}
		}
		//빈칸 확인 하기
		int flag = 0;// 모든칸 바이러스 퍼뜨릴수 없는 경우
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (virusMap[i][j]==0&& visit[i][j] ==0) {
					flag = 1;
					break;
				}
			 else if(virusMap[i][j] == 0)cnt = cnt < visit[i][j] ? visit[i][j] : cnt;// 최대값 산출

			}
			if (flag)break;
		}

		if (flag == 0) {
			ret = ret > cnt ? cnt : ret;//최소값 산출
		}
		return;
	}

	D.push_back(idx);//바이러스 저장
	dfs(idx + 1, d + 1);//바이러스 뽑고
	D.pop_back();
	dfs(idx+1, d);//바이러스 안뽑고
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0, 0);
		if (0x7fffffff == ret)ret = -1;// 바이러스 전부 잠식 못시키는 경우
		else if (0x80000000 == ret)ret = 0;
		else ret -= 1;
		//출력 위치
	//	printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}