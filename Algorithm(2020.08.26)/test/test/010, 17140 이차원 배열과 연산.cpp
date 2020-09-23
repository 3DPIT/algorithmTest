#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define INPUT_SIZE 101
int input[INPUT_SIZE][INPUT_SIZE];//입력으로 주어지는 배열
int R, C;//연산을 적용하기위해 판별을 위한 변수
int r, c, k;// 입력으로 주어지는 행 ,열, 행열의 값
int ret;//결과값 저장
struct Data {
	int num, cnt;
};
bool cmp(Data a, Data b) {// 연산 정렬
	if (a.cnt == b.cnt)return a.num < b.num;//등장수 같으면 번호기준으로 오름차순
	else return a.cnt < b.cnt;//그런게 아니면 나온 횟수로 오름차순
}
void init() {
	memset(input, 0, sizeof(input));
	R = C = 3;
	ret = 0;
	scanf("%d %d %d", &r, &c, &k);
	for(int i=0;i<R;i++){
		for (int j = 0; j < C; j++) {
			scanf("%d", &input[i][j]);//입력
		}
	}
}
void rMath() {//R연산
	int MaxC = 0x80000000;
	for (int i = 0; i < R; i++) {
		Data D[INPUT_SIZE] = { 0, };//연산의 정렬을 위한 배열
		for (int j = 0; j < C; j++) {
			if (input[i][j] != 0) {//0은 무시
				D[input[i][j]].num = input[i][j]; D[input[i][j]].cnt++;//데이터 저장
				input[i][j] = 0;
			}
		}
		sort(D+0, D + 101, cmp);
		vector<int>a;//연산 완료 후 데이터 저장
		for (int i = 1; i <= 100; i++) {
			if (D[i].num != 0) {
				a.push_back(D[i].num);
				a.push_back(D[i].cnt);
			}
		}
		int size = a.size();
		MaxC = MaxC < size ? size : MaxC;// C의 최대값 찾기
		for (int j = 0; j < a.size(); j++) {//연산 결과 저장
			input[i][j] = a[j];
		}
	}
	C = MaxC;
	if (C > 100)C = 100;
}
void cMath() {//C연산
	int MaxR = 0x80000000;//R의 최대값 판별위함
	for (int j = 0; j < C; j++) {
		Data D[INPUT_SIZE] = { 0, };//연산 결과저장 
		for (int i = 0; i < R; i++) {
			if (input[i][j] != 0) {
				D[input[i][j]].num = input[i][j]; D[input[i][j]].cnt++;//데이터 저장
				input[i][j] = 0;//초기화
			}
		}
			sort(D + 0, D + 101, cmp);//정렬
			vector<int>a;//연산 결과 저장
			for (int i = 1; i <= 100; i++) {
				if (D[i].num != 0) {
					a.push_back(D[i].num); a.push_back(D[i].cnt);//연산 결과 저장
				}
			}
			int size = a.size();
			MaxR = MaxR < size ? size : MaxR;//최대 R값저장
			for (int i = 0; i < a.size(); i++) {
				input[i][j] = a[i];
			}
		
	}

	R = MaxR;
	if (R > 100)R = 100;
}
void play() {//연산 시작
	while (1) {
		if (ret > 100)break;
		if (input[r-1][c-1] == k)break;// 종료 조건
		if (R >= C) {
			rMath();//R연산
		}
		else if (R<C) {
			cMath();//C연산
		}

		ret++;
	}
}
int main(void) {
	int testCase = 1;
	scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();//초기값 입력
		play();//연산 시작
		//결과값 출력
		if (ret > 100) ret = -1;
		printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	 
	return 0;
}