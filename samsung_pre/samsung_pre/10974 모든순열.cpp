#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int N;
int d[9];
vector<int>v;
void dfs(int idx, int cnt) {
	if (cnt == N + 1) {
		for (int i = 0; i < v.size(); i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (d[i] == 0) {
			d[i] = 1;
			v.push_back(i);
			dfs(i + 1, cnt + 1);
			v.pop_back();
			d[i] = 0;
		}
	}
}
void init() {
	cin >> N;
	dfs(1, 1);
}
int main(void) {
	init();
	return 0;
}