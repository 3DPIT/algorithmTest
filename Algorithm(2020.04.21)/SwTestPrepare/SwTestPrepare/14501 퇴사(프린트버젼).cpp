#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using namespace std;
#define NS 16
struct Data {
	int Ti, Pi;
};
vector<Data>s;//스케쥴 저장
int N;
int Max = 0x80000000;
void print(string name,int num) {
	cout << name << endl;
	if (name == "N+1위치의sum 값") {
		cout << num << endl;
	}
	if (name == "idx순서") {
		cout << num << endl;
	}
}
struct Fire {
	Fire() {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int day, profit;
			scanf("%d %d", &day, &profit);
			s.push_back({ day,profit });
		}
		dfs(0, 0);
		printf("%d\n", Max);
	}
	void init() {
		s.clear();
		N = 0;
		Max = 0x80000000;
	}
	void dfs(int idx, int sum) {
		if (idx > N) return;
		if (idx == N ) {
			print("N+1위치의sum 값",sum);
			Max = Max < sum ? sum : Max;
			return;
		}
		print("idx순서",idx);
		dfs(idx+s[idx].Ti, sum + s[idx].Pi);
		dfs(idx + 1, sum);

	}
}Fire;
int main(void) {

	return 0;
}