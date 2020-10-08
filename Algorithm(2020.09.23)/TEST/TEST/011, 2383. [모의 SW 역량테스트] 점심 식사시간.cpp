#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NSIZE 10//방의 한 변의 길이
#define HSIZE 10//사람의 최대 수
int N;//방의 한 변의 길이
int H;//사람의 수
int ret;//최종 최소값 저장 변수
int map[NSIZE][NSIZE];//맵 배열
int D[HSIZE];//사람들의 계단 선택을 위한 배열
struct Data {
	int y, x, downTime, stairNum, flag;
};//사람과 계단의 정보저장
vector<Data>human;//사람의 정보
vector<Data>stair;//계단의 정보
void initAndInput() {//초기화 및 초기 입력
	//초기화
	H = N = 0;
	ret = 0x7fffffff;
	memset(map, 0, sizeof(map));
	human.clear(); stair.clear();
	//초기 입력
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] > 1) {//계단의 정보

				stair.push_back({ i,j,0,map[i][j],0 });
			}
			else if (map[i][j] == 1) {//사람의 정보
				human.push_back({ i,j,-2,0,0 });
			}
		}
	}
}
void dfs(int idx, int cnt) {//순열로 계단 선정하기
	if (cnt == human.size()) {//다뽑은 경우
		//cout << "사람이 선택한 계단 출력" << endl;
		//for (int i = 0; i < human.size(); i++) {
		//	cout << D[i] << " ";
		//}
		vector<Data>v;//인간들의 정보 
		//순열로 뽑은거에서 1번계단과 2번계단 사람 나누기
		for (int i = 0; i < human.size(); i++) {//
			v.push_back({ human[i].y,human[i].x,0,D[i] });
			//사람의 좌표값 y, x, 0, 그사람이 선택한 계단
		}
		int Time = 0;// 시간 재기
		vector<int>one;
		vector<int>two;
		vector<int>oneStay;
		vector<int>twoStay;
		int finishCnt = 0;//종료 조건
		while (finishCnt != human.size()) {//사람들 다 내려갈때 까지 돌리기
			++Time;//초 증가
			for (int i = 0; i < v.size(); i++) {//초증가함에 따라서 flag 1인것 시간 감소					
				if (v[i].flag == 1) {
					v[i].downTime--;
					if (v[i].downTime == 0 && v[i].flag != 3) {//끝나는 타임
						//백터 제거 하면서 각 계단에서도 제거
						if (v[i].stairNum == 1) {
							one.pop_back();//1계단 비우기
						}
						else if (v[i].stairNum == 2) {
							two.pop_back();//2계단 비우기
						}
						v[i].flag = 3;
						finishCnt++;
					}
				}
			}
			if (finishCnt == human.size())break;
			for (int i = 0; i < v.size(); i++) {//계단에 올리는 곳
				//계단의 위치
				int sy = stair[v[i].stairNum - 1].y; int sx = stair[v[i].stairNum - 1].x;
				//사람의 위치
				int hy = v[i].y; int hx = v[i].x;
				//거리 재기
				int distance = abs(sy - hy) + abs(sx - hx);
				if (distance == Time || (v[i].flag == 2 && oneStay.size() != 0 && oneStay.front() == i) || (v[i].flag == 2 && twoStay.size() != 0 && twoStay.front() == i)) {//이경우 계단에 도착한 경우
					if (v[i].stairNum == 1 && one.size() != 3) {//최대 들어갈 수 있는 계단
						if (v[i].flag == 2)oneStay.erase(oneStay.begin());//대기순대로 넣어주기
						one.push_back(i);
						v[i].downTime = stair[0].stairNum;//계단에 있다는 표시
						v[i].flag = 1;//현재 계단에 있는걸 표시
					}
					else if (v[i].stairNum == 2 && two.size() != 3) {
						if (v[i].flag == 2)twoStay.erase(twoStay.begin());//대기순대로 넣어주기
						two.push_back(i);
						v[i].downTime = stair[1].stairNum;//계단에 있다는 표시
						v[i].flag = 1;//현재 계단에 있는걸 표시
					}
					else {
						if (v[i].flag != 2 && v[i].stairNum == 1)oneStay.push_back(i);
						if (v[i].flag != 2 && v[i].stairNum == 2)twoStay.push_back(i);
						v[i].flag = 2;//대기 중인 것들
					}
				}
			}
			//순서대로 계단으로 이동시키기
		}
		ret = min(ret, Time);
		return;
	}
	D[idx] = 1;//1번 계단 선택
	dfs(idx + 1, cnt + 1);
	D[idx] = 2;//2번 계단 선택
	dfs(idx + 1, cnt + 1);
	D[idx] = 0;//계단 선택 안함
}
int main(void) {
	int T;//테스트 케이스
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		initAndInput();//초기화 및 초기 입력
		dfs(0, 0);//사람들의 계단 선정
		printf("#%d %d\n", tc, ret+1);
	}

	return 0;
}