#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define S 101//최대 숫자와 배열 크기
int r, c, k;//첫째 주어지는 값
int ret;//결과 값
int B[S][S];//초기 배열
int Fr, Fc;//최종 행과 열값
struct Data {
	int num; int cnt;
};
void init_input() {//초기화 및 초기 입력
	//초기화
	r = c = k = ret = 0;
	Fr = Fc = 3;
	memset(B, 0, sizeof(B));
	//초기 입력
	scanf("%d %d %d", &r, &c, &k);//초기 입력 변수
	for (int y = 1; y <= 3; y++) {
		for (int x = 1; x <= 3; x++) {
			scanf("%d", &B[y][x]);//초기 입력 배열
		}
	}
}
//수의 등장 횟수가 커지는 순으로, 그러한 것이 여러가지면 수가 커지는 순으로 정렬
bool cmp(Data a, Data b) {
	if (a.cnt == b.cnt)return a.num < b.num;
	else return a.cnt < b.cnt;
}
void R() {//R연산
	int MaxC = 0x80000000;//최대 나오는 행값

	for (int y = 1; y <= Fr; y++) {
		Data D[S] = { 0, };//개수 저장 
		vector<Data>v;
		for (int x = 1; x <= Fc; x++) {
			if (B[y][x] != 0) {//0은 제외
				D[B[y][x]].num = B[y][x];//숫자 
				D[B[y][x]].cnt++;//개수  저장
				B[y][x] = 0;
			}
		}
		for (int i = 1; i <= 100; i++) {
			if (D[i].num != 0)v.push_back({ D[i].num,D[i].cnt });//정렬하기전 
		}
		sort(v.begin(), v.end(), cmp);
		int size = v.size();//행의 개수
		MaxC = max(MaxC, size*2);
		//재입력
		int vidx = 0;//백터 추출 인덱스
		for (int x = 0;vidx<size;) {
			B[y][++x] = v[vidx].num;
			B[y][++x] = v[vidx].cnt;
			vidx++;
		}
	}
	Fc = (MaxC) % 100;

}
void C() {//C연산
	int MaxR = 0x80000000;//최대 나오는 행값

	for (int x = 1; x <= Fc; x++) {
		Data D[S] = { 0, };//개수 저장 
		vector<Data>v;
		for (int y = 1; y <= Fc; y++) {
			if (B[y][x] != 0) {//0은 제외
				D[B[y][x]].num = B[y][x];//숫자 
				D[B[y][x]].cnt++;//개수  저장
				B[y][x] = 0;
			}
		}
		for (int i = 1; i <= 100; i++) {
			if (D[i].num != 0)v.push_back({ D[i].num,D[i].cnt });//정렬하기전 
		}
		sort(v.begin(), v.end(), cmp);
		int size = v.size();//행의 개수
		MaxR = max(MaxR, size * 2);
		//재입력
		int vidx = 0;//백터 추출 인덱스
		for (int y = 0; vidx < size;) {
			B[++y][x] = v[vidx].num;
			B[++y][x] = v[vidx].cnt;
			vidx++;
		}
	}
	Fr = (MaxR % 100);

}
void Play() {//시뮬시작
	while (1) {
		if (ret == 101)break;
		if (B[r][c] == k)break;
		//1.R 연산 : 배열 A의 모든 행에 대해서 정렬을 수행한다.행의 개수 ≥ 열의 개수인 경우에 적용된다.
		if(Fr>=Fc) R();
		//2.C 연산: 배열 A의 모든 열에 대해서 정렬을 수행한다. 행의 개수 < 열의 개수인 경우에 적용된다.
		else if(Fr<Fc) C();
		ret++;
	}
	if (ret == 101)ret = -1;//연산 못찾으면 -1 출력
}
int main(void) {
	int T = 1;//테스트 케이스 개수
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//초기화 및 초기 입력
		Play();
		//출력
		printf("%d\n", ret); //printf("#%d %d\n", tc, ret);
	}
	return 0;
}