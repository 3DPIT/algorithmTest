#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define NMS 102
int N, M, K;//가로,세로,상어 수
int ret;//결과값
int sea[NMS][NMS];//바다 배열
int dy[] = { 0,-1,1,0,0 };
int dx[] = {0,0,0,1,-1 };
struct Data {
	int y, x, s, d, z;//위치 y, 위치 x, 스피드, 방향, 크기
};
vector<Data>shark;
bool cmp(Data a, Data b) {//오름 차순 정렬
	if (a.y == b.y)return a.x < b.x;
	return a.y < b.y;
}
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = K = ret = 0;
	memset(sea, 0, sizeof(sea));
	//초기 입력
	scanf("%d %d %d", &N, &M, &K);//가로 세로 크기 상어의 수
	for (int k = 0; k < K; k++) {//초기 입력
		Data c;
		scanf("%d %d %d %d %d", &c.y, &c.x, &c.s, &c.d, &c.z);
			if (c.d == 1 || c.d == 2) {
				//위아래 경우 스피드 줄이기
				c.s = (c.s % ((N*2)-2));//(N-1)*2;
			}
			else if (c.d == 3 || c.d == 4) {//(M-1)*2
				c.s = (c.s% ((M * 2) - 2));
			}
		shark.push_back(c);//상어 정보 입력
	}
}
bool safe(int y, int x) {
	return 1<= y && y <= N && 1 <= x && x <= M;
}
void fishing() {
	for (int j = 1; j <= M; j++) {//순차적으로 낚시 시작
		sort(shark.begin(), shark.end(),cmp);
		//낚시를 하는 경우
		for (int s = 0; s < shark.size(); s++) {
			if (shark.size() == 0)break;
			if (shark[s].x == j) {//상어 낚시성공
				ret += shark[s].z;//상어 저장
				shark.erase(shark.begin() + s);
				break;//한마리만 잡아야함 규칙임
			}
		}
		//상어의 이동
		for (int i = 0; i < shark.size(); i++) {
			Data n; Data c = shark[i];
			for (int s = 0; s < c.s; s++) {//스피드 만큼 이동
				n.y = c.y + dy[c.d];
				n.x = c.x + dx[c.d];
				if (safe(n.y, n.x)) {//이동 가능한 공간이면 이동
					c.y = n.y; c.x = n.x;
					shark[i].y = c.y; shark[i].x = c.x;
				}
				else {//벗어나는 경우
					//방향 전환
					if (c.d == 1)c.d = 2;
					else if (c.d == 2)c.d = 1;
					else if (c.d == 3)c.d = 4;
					else if (c.d == 4)c.d = 3;
					//한칸이동시키기
					shark[i].d = c.d;
					c.y = c.y + dy[c.d]; c.x = c.x + dx[c.d];//이동
					shark[i].y = c.y; shark[i].x = c.x;
				}
			}
		}//for i
		sort(shark.begin(), shark.end(),cmp);//한번더 정렬
		//같은 위치의 상어 제거하기
		for (int a = 0; a < shark.size() - 1; a++) {
			if (shark.size() == 0)break;
			int cnt = 0;//현재 몇개가 같은지 체크
			int maxSize = shark[a].z;
			Data cM;//맥스값 저장
			cM = shark[a];
			for (int b = a+1; b < shark.size(); b++) {
				if (shark[a].y == shark[b].y&&shark[a].x == shark[b].x) {//같으면 종료
					if (maxSize < shark[b].z) {//가장큰 개체 선별하기
						maxSize = shark[b].z;
						cM = shark[b];
					}
					cnt++;
				}
				else break;//같지 않으면 종료
			}
			if (cnt != 0) {
				shark.erase(shark.begin() + a+1, shark.begin() +a+ cnt+1);//상어 먹고
				shark[a] = cM;//제일 큰놈으로 대체
			}
		}
	}//for j
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();// 초기화 및 초기 입력
		fishing();//낚시 시작
		//출력
		printf("%d\n", ret);
	//	printf("#%d %d\n", tc, ret);
	}
	return 0;
}