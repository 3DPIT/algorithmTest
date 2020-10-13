#include<stdio.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
#define NS 21
int N;//바다의 크기
int sea[NS][NS];//초기 입력 배열 바다 정보
int ret;//결과값
int dy1[4] = { 0,1,0,-1 };
int dx1[4] = { 1,0,-1,0 };
struct Data {
	int y, x,cnt;
};
queue<Data>q;//상어의 이동 경로 저장 큐
int init_input(){//초기화 및 초기 입력
	//초기화
	N = ret = 0;
	memset(sea, 0, sizeof(sea));
	//초기 입력
	scanf("%d",&N);//바다의 크기 입력
	int cnt = 0;//현재 물고기 없는지 파악
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &sea[i][j]);// 초기 입력
			if (sea[i][j] == 9) {
				q.push({ i,j });
				sea[i][j] = 0;//위치 제거
			}
			if (sea[i][j] != 0)cnt++;
		}
	}
	if (cnt == 0)return 0;
	return 1;
}
bool safe(Data c) {//범위 확인
	return 0 <= c.y && c.y < N && 0 <= c.x && c.x < N;
}
void eatFish() {//먹이 사냥 시작
	int sharkSize = 2;//상어 크기
	int eat = 0;//먹은 개수
	while (1) {
		int visit[NS][NS] = { 0, };//방문 체크
		visit[q.front().y][q.front().x] = 1;
		int dy = 0x7fffffff; int dx = 0x7fffffff; int dd = 0x7fffffff;//가장 가깝고 가장 왼쪽 뽑기 위함
		while (!q.empty()) {
			Data c = q.front(); q.pop();
			//먹을 수 있는 물고기가 1마리보다 많다면, 거리가 가장 가까운 물고기를 먹으러 간다.
			if (sea[c.y][c.x]!=0&&sea[c.y][c.x]<sharkSize&dd >= c.cnt) {
				//거리가 가까운 물고기가 많다면, 가장 위에 있는 물고기, 그러한 물고기가 여러마리라면,
				//가장 왼쪽에 있는 물고기를 먹는다.
				if (dd == c.cnt) {
					dd = c.cnt;
					if (dy>c.y||(dy==c.y&&dx>c.x)) {
						dy = c.y; dx = c.x;
					}
				}
				else if (dd > c.cnt) {
					dd = c.cnt;
					dy = c.y; dx = c.x;
				}
			}
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy1[dir]; n.x = c.x + dx1[dir];
				n.cnt = c.cnt + 1;//다음 좌표값
				if (safe(n) && visit[n.y][n.x] == 0 && 0 <= sea[n.y][n.x] && sea[n.y][n.x] <= sharkSize) {
					//안전 거리에 있고, 방문한적이 없으며, 자기크키보다 작거나 같은 경우에만 푸쉬
					visit[n.y][n.x] = n.cnt;
					q.push(n);
				}
			}
		}//while !q.empty()
		if (dd != 0x7fffffff) {//먹을 고기가 있는 경우
			eat++;
			if (eat == sharkSize) {//크기 만큼 먹은 경우 성장
				sharkSize++;
				eat = 0;
			}
			ret += dd;//걸린 시간
			sea[dy][dx] = 0;
			q.push({ dy,dx,0 });
		}
		else if (dd == 0x7fffffff) {
		//더 이상 먹을 수 있는 물고기가 공간에 없다면 아기 상어는 엄마 상어에게 도움을 요청한다.
			break;
		}
	}//while 1
}
int main(void) {
	int T = 1;//테스트 케이스
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		if(init_input()){//초기화 및 초기 입력
			eatFish();// 물고기 사냥 시작
			//출력
			printf("%d\n", ret); printf("#%d %d\n", tc, ret);
		}
		else {//물고기 없는 경우
			//출력
			printf("%d\n", ret); printf("#%d %d\n", tc, ret);
		}
	}
	return 0;
}

//거리는 아기 상어가 있는 칸에서 물고기가 있는 칸으로 이동할 때, 지나야하는 칸의 개수의 최솟값이다.
