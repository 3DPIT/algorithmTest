#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define N_SIZE 21
int N;// 공간의 사이즈
int seaMap[N_SIZE][N_SIZE];//아기상어와 물고기 정보 배열
int visit[N_SIZE][N_SIZE];//아기상어 방문 체크 배열
int ret = 0;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {//큐에 쓰일 자료형
	int y, x, cnt;
};
queue<Data>q;// 큐생성
bool safe(int y, int x) {//배열 범위 체크 함수
	return 0 <= y && y < N && 0 <= x && x < N;
}

void init() {
	//초기화 
	N = ret = 0;
	memset(seaMap, 0, sizeof(seaMap));
	memset(visit, 0, sizeof(visit));
	while (!q.empty())q.pop();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {// 데이터 입력
		for (int j = 0; j < N; j++) {
			scanf("%d", &seaMap[i][j]);
			if (seaMap[i][j] == 9) {// 아기상어 위치 찾기
				q.push({ i,j,0 });
				visit[i][j] = 1;
				seaMap[i][j] = 0;
			}
		}
	}
}
void BFS() {// 시뮬레이션 진행 함수
	int sharkSize = 2;//상어 크기
	int fishEat = 0;//상어가 물고기 먹은것 
	while (1) {//아기상어가 엄마 찾을때 까지 반복
		int minY, minX, minCnt;//최소 y,x,최소거리 변수
		minY = minX = minCnt = 0x7fffffff;
		while (!q.empty()) {//큐가 빌때까지 반복 진행
			Data c = q.front(); q.pop();
			if (minCnt < c.cnt)break;
			if (seaMap[c.y][c.x] != 0 && seaMap[c.y][c.x] < sharkSize&&minCnt >= c.cnt) {//먹을 수있는 상어라면
				minCnt = c.cnt;
				if (minY > c.y || ((minY == c.y && (minX > c.x)))) {
					minY = c.y;
					minX = c.x;//사실상 x값만 최소로 갱신
				}
			}// 조건 확인 끝 최소값 갱신

			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0 && seaMap[n.y][n.x] <= sharkSize) {
					//범위 넘지 않고  방문 한곳이 아니고 상어보다 작거나 같은 경우
					visit[n.y][n.x] = 1;
					q.push(n);
				}
			}

		}//큐끝 부분
		if (0x7fffffff == minY) {//먹은 물고기 가 없으면 종료
			break;
		}
		else {
			ret += minCnt;//최소거리 저장
			fishEat++;
			if (fishEat == sharkSize) {//상어크기 만큼 먹은 경우 크기 +1
				fishEat = 0;
				sharkSize++;
			}
			while (!q.empty())q.pop();//일단 초기화
			q.push({ minY,minX,0 });
			memset(visit, 0, sizeof(visit));
			visit[minY][minX] = 1;
			seaMap[minY][minX] = 0;

		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		BFS();
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}