#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int main(void) {
	//1 1
	//2 2
	//3 3 
	//4 4
	//홀수일때 1부터
	//짤수일때 그 수부터
	//14일때
	//13 1
	//11 2
	//8 3
	//4 4
// 일단 빼고 남은 것에서 계산해서 산출하기
	long long int X;
	cin >> X;
	int flag = 0;
	if (X == 1) {
		flag = 1;
	}

	int i = 1;//+1 더해서 사용해야하는 변수
	for (i = 1; i <= 100000; i++) {
		X -= i;
		if (X <=0) {//일단 최대한 근처로 가기
			X += i;
			break;
		}
	}
	if (i % 2 == 0) {//짝수

		//분자가 i
		int j = 1;
		for (; j < X; j++) {
			i--;
		}
		cout << j << '/' <<i << '\n';

	}
	else if(i%2==1) {//홀수

		//분모가 i
		int j = 1;
		for (; j <X; j++) {
			i--;
		}
		cout << i << '/' << j << '\n';
}
	return 0;
}