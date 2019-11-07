#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>	
using namespace std;
int N, M;
vector<int>v;
void init() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		int a;
		scanf("%d", &a);
		v.push_back(a);
	}
	for (int j = 0; j < M; j++) {
		int a;
		scanf("%d", &a);
		v.push_back(a);
	}
	sort(v.begin(), v.end());//벡터 정렬
	for (int i = 0; i < v.size(); i++) {
		printf("%d ", v[i]);// 벡터 출력

	}
	cout << endl;
}
int main(void)
{
	init();//초기화 입력 하자마자 출력
	return 0;
}