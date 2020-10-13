#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 51 //배열의 최대 크기
int N, M;//배열 크기, 뽑는 치킨집 수
int ret; //결과값 저장 변수
int B[NS][NS];
struct Data {
	int y, x;
};//좌표 구조체
vector<Data>C;//치킨집의 정보
vector<Data>H;//집들의 정보
vector<int>cC;
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = 0;
	ret = 0x7fffffff;//최소값 저장
	C.clear(); H.clear();
	cC.clear();
	//초기 입력
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &B[i][j]);
			// 1. 집의 정보 저장
			if (B[i][j] == 1) {//집인 경우
				H.push_back({ i,j });
			}
			//2. 치킨집의 정보 저장
			else if (B[i][j] == 2) {//치킨집인 경우
				C.push_back({ i,j });
			}
		}
	}
}
void dfs(int idx, int cnt) {//3. 조합 으로 M개의 치킨집 저장
	if (idx == C.size()+1)return;//
	if (cnt== M) {//M개의 치킨집 선별하기
		//4. return ; 부분에서 치킨거리 최소값 뽑기
		int sum = 0;//최소거리 저장
		for (int i = 0; i < H.size(); i++) {// 각각의 집에서 최소 거리인 치킨집 찾기
			int minD = 0x7fffffff;
			for (int j = 0; j < cC.size(); j++) {
				int D = abs(H[i].y - C[cC[j]].y) + abs(H[i].x - C[cC[j]].x);
					minD = min(minD, D);//최소 찾기
				}
				sum += minD;
		}
		//5. 최소값 도출
		ret = min(ret, sum);
		return;
	}
	cC.push_back(idx);
	dfs(idx + 1, cnt + 1);
	cC.pop_back();
	dfs(idx + 1, cnt);
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d",&T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		dfs(0, 0);
		//출력
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}