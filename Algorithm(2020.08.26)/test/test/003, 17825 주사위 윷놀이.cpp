#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
int cubeNum[11];//주사위 수 저장 배열
int D[33];//말의 순서 저장 배열
int ret;//최댓값 저장
struct Data {
	int idx,nextIdx,visitPreIdx;//현재 인덱스,다음 인덱스
}horse[4];//말
int board[33] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,
			13,16,19,25,
			22,24,
			28,27,26,
			30,35 };//맵 구성요소
void init() {
	ret = 0x80000000;
	memset(horse, 0, sizeof(horse));
	memset(cubeNum, 0, sizeof(cubeNum));//초기화
	memset(D, 0, sizeof(D));//초기화
	for (int i = 0; i < 10; i++) {
		scanf("%d", &cubeNum[i]);
	}
}
bool playGame(int &sum) {
	sum = 0;
	memset(horse, 0, sizeof(horse));
	int visit[33] = { 0, };//방문체크
	//마지막 인덱스가 이곳이면 다음 넘어갈곳
	/*5-22
	  25-31
	  27-25
	  30-25
	  32-20
	  20-21
	*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < cubeNum[i]; j++) {
			if (horse[D[i]].nextIdx == -1|| horse[D[i]].nextIdx == -2)break;//범위 넘어가는 경우 종료
			if (horse[D[i]].nextIdx != 0) {//파란원 부분인경우 그 범위로 이동 시키기
				horse[D[i]].idx = horse[D[i]].nextIdx;
				horse[D[i]].nextIdx = 0;
			}
			else  horse[D[i]].idx++;
			if (horse[D[i]].idx == 25)horse[D[i]].nextIdx = 31;//25점에서 30점가는 구간
			if(horse[D[i]].idx == 27|| horse[D[i]].idx == 30)horse[D[i]].nextIdx = 25;
			//19점에서 25점
			//24점에서 25점
			//26점에서 25점 가는 구간
			if (horse[D[i]].idx == 32)horse[D[i]].nextIdx = 20;//35점에서 40점 가는 구간
			if (horse[D[i]].idx == 20)horse[D[i]].nextIdx = 21;
			if (horse[D[i]].idx == 21) {
				horse[D[i]].nextIdx = -1;//도착구역 간것 체크
				break;
			}
		}
		if (horse[D[i]].idx == 5)horse[D[i]].nextIdx = 22;
		if (horse[D[i]].idx == 10)horse[D[i]].nextIdx = 26;
		if (horse[D[i]].idx == 15)horse[D[i]].nextIdx = 28;
		if (horse[D[i]].idx == 25)horse[D[i]].nextIdx = 31;
		if (horse[D[i]].idx == 27|| horse[D[i]].idx == 30)horse[D[i]].nextIdx = 25;
		if (horse[D[i]].idx == 32)horse[D[i]].nextIdx = 20;
		if (horse[D[i]].idx == 20)horse[D[i]].nextIdx = 21;


		if (visit[horse[D[i]].idx] == 0) {//현재 칸에 말이 있는지 확인
			if (horse[D[i]].idx == 21 && horse[D[i]].nextIdx == -1) {
				sum += board[horse[D[i]].idx];//이동 한 후 마지막칸의 값 저장
				if (horse[D[i]].visitPreIdx != 0) {//이전의 칸의 방문 지우기 위한 조건
					visit[horse[D[i]].visitPreIdx] = 0;
					horse[D[i]].visitPreIdx = 0;
				}
				horse[D[i]].nextIdx = -2;
			}
			if(horse[D[i]].idx != 21){
				sum += board[horse[D[i]].idx];//이동 한 후 마지막칸의 값 저장
				if (horse[D[i]].visitPreIdx != 0) {//이전의 칸의 방문 지우기 위한 조건
					visit[horse[D[i]].visitPreIdx] = 0;
					horse[D[i]].visitPreIdx = 0;
				}
				horse[D[i]].visitPreIdx = horse[D[i]].idx;//이전 인덱스 기록
				visit[horse[D[i]].idx] = 1;//방문 체크
			}
		}
		else return false;//놓은 칸에 말이 있는경우 제외 
	}
	return true;
}
void dfs(int idx,int d) {//순열 뽑아내기
	if (idx == 10) {//말의 순서 10개 뽑기
		int sum = 0;
		if (!playGame(sum)) return;
		ret = ret < sum ? sum : ret;
		return;
	}
	for (int i = 0; i < 4; i++) {
		D[idx] = i;
		dfs(idx + 1,d++);
		D[idx] = 0;
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0,0);
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}