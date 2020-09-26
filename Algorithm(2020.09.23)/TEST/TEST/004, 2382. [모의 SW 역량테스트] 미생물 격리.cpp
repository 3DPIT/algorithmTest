#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
struct Data {
	int y, x, k, dir;//위치y,x,군집 수, 방향
};
int dy[] = { 0,-1,1,0,0 };//상 하 좌 우
int dx[] = { 0,0,0,-1,1 };
vector<Data>MS;//미생물의 정보 담는곳
int N, K, M;//셀의 개수, 미생물 군집의 개수, 격리시간
int ret;//결과 값(남은 미생물의 수)
bool safeZone(int y, int x) {
	return y == 0 || x == 0 || y == N - 1 || x == N - 1;
}
bool cmp(Data a, Data b) {//정렬 조건
	if (a.y == b.y)return a.x < b.x;
	else return a.y < b.y;
}
void init() {
	//초기화
	MS.clear();
	N = K = M = ret = 0;

	//입력
	scanf("%d %d %d", &N, &M, &K);
	for (int k = 0; k < K; k++) {//미생물 정보 입력
		Data c;

		scanf("%d %d %d %d", &c.y, &c.x, &c.k, &c.dir);
		MS.push_back(c);//입력
	}
	return;
}
void play() {
	for (int m = 0; m < M; m++) {//격리시간
		if (MS.size() == 0)break;//탈출
		for (int k = 0; k < MS.size(); k++) {//미생물 이동시키기
			if (MS.size() == 0)break;//탈출
			Data n, c;//다음위치, 현재위치 저장 변수
			c = MS[k];

			n.y = c.y + dy[c.dir]; n.x = c.x + dx[c.dir];//위치 이동
			n.k = c.k; n.dir = c.dir;
			if (safeZone(n.y, n.x)) {//빨간 영역에 들어오면
				//미생물 수 반 감소 후 방향 반대로 변경
				if (c.k == 1) {//미생물이 이제 0되는 경우사라짐
					MS.erase(MS.begin() + k);
					k--;
				}
				else {
					//미생물 수 감소
					n.k = c.k / 2;
					//방향 전환
					if (c.dir == 1)n.dir = 2;
					else if (c.dir == 2)n.dir = 1;
					else if (c.dir == 3)n.dir = 4;
					else if (c.dir == 4)n.dir = 3;
					MS[k] = n;//위치 변경
				}
			}//if 끝(빨간 영역 검사)
			else MS[k] = n;
		}//for문 끝
		sort(MS.begin(), MS.end(), cmp);//정렬
		// 중복 위치 애들 처리하기
		for (int i = 0; i < MS.size() - 1; i++) {
			if (MS.size() == 0)break;
			int cnt = 0;//중복 개수 확인
			int Max = MS[i].k;//중복되는것중 최대값
			int MaxDir = MS[i].dir;//중복되는것중의 최대의 방향
			int sum = MS[i].k;
			for (int j = i + 1; j < MS.size(); j++) {
				if (MS.size() == 0)break;
				if (MS[i].y == MS[j].y&&MS[i].x == MS[j].x) {
					cnt++;
					sum += MS[j].k;//미생물 군집 더하기
					if (Max < MS[j].k) {//최대를 가진 것의 방향 정하기
						Max = MS[j].k;
						MaxDir = MS[j].dir;
					}
				}
				else break;//중복값이 없으면 종료
			}
			if (cnt != 0) {//같은 위치에 있는 것이 있으면
				MS.erase(MS.begin() + i + 1, MS.begin() + i + cnt + 1);
				MS[i].k = sum;//군집 저장
				MS[i].dir = MaxDir;//최대의 방향 으로 진행
			}
		}
	}//for문 끝 격리시간
	for (int i = 0; i < MS.size(); i++) {
		ret += MS[i].k;
	}
	return;
}
int main(void) {
	int T;//테스트 케이스
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}