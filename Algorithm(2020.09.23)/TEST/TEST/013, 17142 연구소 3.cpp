#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
#define NSIZE 50//맵의 크기
#define MSIZE 10//바이러스 최대수
int D[MSIZE];//활성바이러스 저장
int lab[NSIZE][NSIZE];//연구소 상황 저장
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int N, M;//연구소의크기, 바이러스의 개수
int ret;//결과값 저장
struct Data
{
	int y, x,cnt;//위치 y,x,초
};//바이러스의 정보 담기
Data virus[MSIZE];
int v_idx;//바이러스 개수
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = v_idx=0;
	ret = 0x7fffffff;//최소값 구하기 
	memset(lab, 0, sizeof(lab));
	memset(virus, 0, sizeof(virus));
	memset(D, 0, sizeof(D));
	//초기 입력
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &lab[i][j]);
			if (lab[i][j] == 2) {//바이러스 정보 저장
				virus[v_idx].y = i; virus[v_idx].x = j;
				v_idx++;
			}
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
void dfs(int idx, int cnt) {
	if (cnt == M) {//M개 만큼 바이러스 뽑기
		int visit[NSIZE][NSIZE] = { 0, };//방문 체크
		queue<Data>q;
		for (int i = 0; i < v_idx; i++) {
			if (D[i] == 1) {
				q.push({ virus[i].y,virus[i].x,1 });//큐에 넣기
				visit[virus[i].y][virus[i].x] = 1;
			}
		}
		while (!q.empty()) {//바이러스 퍼치기
			Data c = q.front(); q.pop();//큐데이터 뽑고 팝
			for (int dir = 0; dir < 4; dir++) {
				Data n;//다음 위치 저장
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0
					&& lab[n.y][n.x] != 1) {//벽이 아니기만 하면 넘기기
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}
		int cnt = 0x80000000;//현재 최대 시간 확인
		for (int y = 0; y < N; y++) {//최소 시간 확인
			for (int x = 0; x < N; x++) {
				if (lab[y][x] != 1 && lab[y][x] != 2) {//바이러스있는곳이아니고 벽이아닌경우
					cnt = max(cnt, visit[y][x]);
				}
				if (lab[y][x] == 0 && visit[y][x] == 0) {//빈공간인데 바이러스 없으면 탈
					return;
				}
			}
		}
		if (cnt == 0x80000000)cnt = 0;
		ret = min(ret, cnt);
		return;
	}
	for (int i = idx; i < v_idx; i++) {
		D[i] = 1;
		dfs(i+1, cnt + 1);
		D[i] = 0;
	}
}
int main(void) {
	int T = 1;//테스트케이스
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		dfs(0, 0);//바이러스 전파시작
		if (0x7fffffff == ret)ret = -1;//바이러스 다 못채우는 경우
		//출력
		else if(ret!=-1&&ret!=0) ret--;
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}