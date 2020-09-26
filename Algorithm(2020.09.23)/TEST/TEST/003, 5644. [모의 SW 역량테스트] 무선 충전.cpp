#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define MSIZE 105
#define ASIZE 10
struct Data {
	int Y, X, C, P;//유저의 위치값 Y,X, 충전범위, 성능
}BC[ASIZE];
int BCidx = 0;
int userMap[2][MSIZE];//유저들의 경로 저장 배열
int dy[] = { 0,-1,0,1,0 };//이동 안함, 상, 우, 하, 좌
int dx[] = { 0,0,1,0,-1 };
int M, A;//총이동시간, BC의 개수
int ret;//결과값 저장
int user0Y,user0X,user1Y,user1X;//유저의 초기 위치
vector<int>u1; vector<int>u2;//유저 BC접속 확인
void init() {
	//초기화
	u1.clear(), u2.clear();
	user0Y = 1, user0X = 1, user1Y = 10, user1X = 10;
	memset(userMap, 0, sizeof(userMap));
	memset(BC, 0, sizeof(BC));
	M = A = 0;
	ret = 0;
	
	//입력
	scanf("%d %d", &M, &A);
	//유저 경로 배열 저장
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &userMap[i][j]);
		}
	}
	//BC 정보 저장
	for (int i = 0; i < A; i++) {
		scanf("%d %d %d %d",&BC[i].X, &BC[i].Y, &BC[i].C, &BC[i].P);
	}
}
void chkBC() {
	for (int i = 0; i < A; i++) {//접속확인
		int D = abs(user0Y - BC[i].Y) + abs(user0X - BC[i].X);
		if (BC[i].C >= D) {//유저1이 범위에 들어가 있으면 저장
			u1.push_back(i);
		}
		D = abs(user1Y - BC[i].Y) + abs(user1X - BC[i].X);
		if (BC[i].C >= D) {//유저2가 범위에 들어가 있으면 저장
			u2.push_back(i);
		}
	}
}
void userConnect(int num) {//접속 최대값 구하기
	if (num == 1) {
		int Max = 0x80000000;
		for (int i = 0; i < u1.size(); i++) {// 유저1을 기준으로
			if (Max < BC[u1[i]].P)Max = BC[u1[i]].P;//최대 접속가능
		}
		ret += Max;//최댓값 저장
	}
	if (num == 2) {
		int Max = 0x80000000;
		for (int i = 0; i < u2.size(); i++) {//유저2를 기준으로
			if (Max < BC[u2[i]].P)Max = BC[u2[i]].P;//최대 접속가능
		}
		ret += Max;//최댓값 저장
	}
	if (num == 3) {
		int Max = 0x80000000;
		for (int i = 0; i < u1.size(); i++) {//두 유저가 접속가능한곳에서 
			for (int j = 0; j < u2.size(); j++) {
				if (u1[i] != u2[j]) {
					if (Max < BC[u1[i]].P + BC[u2[j]].P)Max = BC[u1[i]].P + BC[u2[j]].P;
				}
				else if (u1[i] == u2[j]) {
					if (Max < BC[u1[i]].P )Max = BC[u1[i]].P;
				}
			}
		}
		ret += Max;//최댓값 저장
	}
}
void Play() {
	chkBC();//접속 가능 BC확인
	if (u1.size() != 0 && u2.size() == 0) {//접속가능 유저1만 있는경우
		userConnect(1);//접속 최대값 구하기
	}
	else if (u1.size() != 0 && u2.size() != 0) {//둘다 접속가능한경우
		userConnect(3);//접속 최대값 구하기
	}
	else if (u1.size() == 0 && u2.size() != 0) {//접속가능 유저2만 있는경우
		userConnect(2);//접속 최대값 구하기
	}
}
void goUser() {
	Play();//시작전 확인
	for (int m = 0; m < M; m++) {//이동시작
		u1.clear(); u2.clear();
		user0X += dx[userMap[0][m]]; user0Y += dy[userMap[0][m]];
		user1X += dx[userMap[1][m]]; user1Y += dy[userMap[1][m]];
		Play();
	}
}
int main(void) {
	int T;//테스트케이스 개수
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();//초기화 및 입력
		goUser();//유저 출발
		printf("#%d %d\n", tc, ret);
	}

	return 0;
}