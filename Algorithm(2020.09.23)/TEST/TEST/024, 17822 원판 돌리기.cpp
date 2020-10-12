
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
using namespace std;
#define NMS 51//가로 세로 최대 크기
int N, M, T;//가로, 세로 크기 , 시간
int ret;//결과 값
int circle[NMS][NMS];// 원판 배열
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int visit[NMS][NMS];//방문 체크
int flag;//제거 체크

struct Data {
	int num, dir, cnt;//숫자, 방향, 개수
};
struct Data1 {
	int y, x;
};

vector<Data>order;//주문 확인
void init_input() {//초기화 및 초기 입력
	//초기화 
	order.clear();
	N = M = T = flag = ret = 0;
	memset(visit, 0, sizeof(visit));
	memset(circle, 0, sizeof(circle));
	//초기 입력
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &circle[i][j]);//초기 원판 상태 입력
		}//for j
	}//for i
	for (int t = 1; t <= T; t++) {
		int num, dir, cnt;
		scanf("%d %d %d", &num, &dir, &cnt);//명령 저장
		order.push_back({ num,dir,cnt%M });
	}
}
void clockTurn(int num, int cnt) {//시계방향 턴
	for (int i = 0; i < N; i++) {
		if ((i + 1) % num == 0) {//배수인경우
			for (int c = 0; c < cnt; c++) {
				int cnum = circle[i][M - 1];//가장 끝값 저장
				for (int j = M - 1; j >= 1; j--) {
					circle[i][j] = circle[i][j - 1];
				}
				circle[i][0] = cnum;
			}
		}
	}
}
void reclockTurn(int num, int cnt) {//반시계방향 턴
	for (int i = 0; i < N; i++) {
		if ((i + 1) % num == 0) {//배수인경우
			for (int c = 0; c < cnt; c++) {
				int cnum = circle[i][0];//가장 끝값 저장
				for (int j = 0; j < M - 1; j++) {
					circle[i][j] = circle[i][j + 1];
				}
				circle[i][M - 1] = cnum;
			}
		}
	}
}
void dfs(int y, int x, int num) {//같은 수 제거 dfs
	//넘겨 줄수 있는 것 x==-1 -> x=M-1 
	// x==M -> x=0;
	//넘어가면 안되는 범위
	//y==-1, y==N+1
	for (int dir = 0; dir < 4; dir++) {
		Data1 n;
		n.y = y + dy[dir]; n.x = x + dx[dir];
		if (n.y != -1 && n.x != N + 1) {
			if (n.x == -1) {
				n.x = M - 1;
			}
			if (n.x == M) {
				n.x = 0;
			}
		}
		if (visit[n.y][n.x] == 0 && circle[n.y][n.x] == num) {
			circle[n.y][n.x] = 0;
			visit[n.y][n.x] = 1;
			flag = 1;
			dfs(n.y, n.x, num);
		}

	}
}
void DFS() {//같은수 제거하기 위함
	memset(visit, 0, sizeof(visit));
	int f = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (circle[i][j] != 0) {
				visit[i][j] = 1;
				dfs(i, j, circle[i][j]);
				if (flag) {
					f = 1;
					circle[i][j] = 0;
					visit[i][j] = 1;
					flag = 0;
				}
			}
		}
	}
	flag = f;
}
void chkNum() {//최종 남은것의 합
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret += circle[i][j];
		}
	}
}
void circleTurn() {
	for (int t = 0; t < T; t++) {
		//번호가 xi의 배수인 원판을 di방향으로 ki칸 회전시킨다.di가 0인 경우는 시계 방향, 1인 경우는 반시계 방향이다.
		if (order[t].dir == 0) {//시계 이동
			clockTurn(order[t].num, order[t].cnt);
		}
		if (order[t].dir == 1) {//반시계 이동
			reclockTurn(order[t].num, order[t].cnt);
		}
		flag = 0;//플래그 초기화
		//그러한 수가 있는 경우에는 원판에서 인접하면서 같은 수를 모두 지운다.
		DFS();//현재 상태에서 인접한 수 제거
		if (flag == 0) {//제거할것이 없는 경우
			//없는 경우에는 원판에 적힌 수의 평균을 구하고, 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다.
			double num = 0; int numcnt = 0;;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (circle[i][j] != 0) {
						num += circle[i][j];
						numcnt++;
					}
				}
			}
			//평균 구하기
			num = num / numcnt;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (circle[i][j] != 0) {
						if (circle[i][j] > num) {//평균보다 큰수
							circle[i][j]--;
						}
						else if (circle[i][j] < num) {//평균보다 작은수
							circle[i][j]++;
						}
					}// if circle
				}//for j
			}//for i
		}//if flag
	}//for t
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret += circle[i][j];
		}
	}
}
int main(void) {
	int testCase = 1;//테스트 케이스 개수
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init_input();//초기화 및 초기 입력
		circleTurn();//원판 돌리기
		//출력
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}