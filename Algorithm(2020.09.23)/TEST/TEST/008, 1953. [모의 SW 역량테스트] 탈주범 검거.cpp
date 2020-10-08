#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define NSIZE 50
int tunnel[NSIZE][NSIZE];//터널의 정보입력 배열
int visitT[NSIZE][NSIZE];//터널의 이동경로 체크 배열
int N, M, R, C, L;//세로, 가로, 범인의 세로, 범인의 가로, 시간
int ret;//결과값 입력
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
//구조체 변수들
struct Data {//도둑의 이동경로 큐에 들어갈 데이터
	int y, x, cnt;//좌표와 현재 시간
};
void init() {//변수들 초기화
	N = M = R = C = L = ret;
	memset(tunnel, 0, sizeof(tunnel));
	memset(visitT, 0, sizeof(visitT));
}
bool dirNum(int dir, Data n) {//갈수  있는 위치라면 true,  아니면 false 반환
	if (dir == 0 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 2 || tunnel[n.y][n.x] == 5 || tunnel[n.y][n.x] == 6)) {
		return 1;
	}
	if (dir == 1 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 3 || tunnel[n.y][n.x] == 6 || tunnel[n.y][n.x] == 7)) {
		return 1;
	}
	if (dir == 2 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 2 || tunnel[n.y][n.x] == 4 || tunnel[n.y][n.x] == 7)) {
		return 1;
	}
	if (dir == 3 && (tunnel[n.y][n.x] == 1 || tunnel[n.y][n.x] == 3 || tunnel[n.y][n.x] == 4 || tunnel[n.y][n.x] == 5)) {
		return 1;
	}
	return 0;
}
void running() {
	queue<Data>q;//큐 선언
	q.push({ R,C,0 });//큐 푸쉬
	visitT[R][C] = 1;//큐 방문 체크
	ret = 1;//현재 도둑이 있을 수 있는 위치의 개수
	while (!q.empty()) {//큐가 빌때까지 돌기
		Data c = q.front(); q.pop();
		if (c.cnt == L - 1)break;//L정도 시간되면 종료
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = c.y + dy[dir]; n.x = c.x + dx[dir];// 다음위치 인덱스
			n.cnt = c.cnt + 1;//시간 측정
			if (tunnel[c.y][c.x] == 1 && visitT[n.y][n.x] == 0) {//현재의 위치가 1인 구조물일때 다음 위치가 1,2,5,6인데 방문 안한 경우
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 2 && visitT[n.y][n.x] == 0 && (dir == 0 || dir == 2)) {
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 3 && visitT[n.y][n.x] == 0 && (dir == 1 || dir == 3)) {
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 4 && visitT[n.y][n.x] == 0 && (dir == 0 || dir == 1)) {
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 5 && visitT[n.y][n.x] == 0 && (dir == 1 || dir == 2)) {
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 6 && visitT[n.y][n.x] == 0 && (dir == 2 || dir == 3)) {
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
			else if (tunnel[c.y][c.x] == 7 && visitT[n.y][n.x] == 0 && (dir == 0 || dir == 3)) {
				if (dirNum(dir, n)) {
					ret++;//도둑의 위치 증가
					visitT[n.y][n.x] = 1;
					q.push(n);
				}
			}
		}
	}
}
int main(void) {
	int T;//테스트케이스 개수
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		//입력값 입력
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &tunnel[i][j]);
			}
		}
		running();//도둑의 이동
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}