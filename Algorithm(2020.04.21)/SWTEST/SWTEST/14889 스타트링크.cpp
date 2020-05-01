#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define NS 21
int N, ret;
int map[NS][NS];
int v[NS];
int Min = 0x7fffffff;
void print(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < N; i++) {
			cout << "  " << v[i];
		}
		cout << endl;
	}
}
void dfs(int idx, int cnt) {
	if (idx > N)return;
	if (cnt == N / 2) {
		//print("vÀÇ°ª", 0);
		vector<int>v1;
		vector<int>v2;
		for (int i = 0; i < N; i++) {
			if (v[i] == 0)v1.push_back(i);
			else v2.push_back(i);
		}
		int sum = 0;
		int sum1 = 0;
		for (int i = 0; i < v1.size(); i++) {
			for (int j = 0; j < v1.size(); j++) {
				if (v1[i] == v1[j])continue;
				sum += map[v1[i]][v1[j]];
			}
		}
		for (int i = 0; i < v2.size(); i++) {
			for (int j = 0; j < v2.size(); j++) {
				if (v2[i] == v2[j])continue;
				sum1 += map[v2[i]][v2[j]];
			}
		}
		sum = abs(sum - sum1);
		if (Min > sum)Min = sum;
		return;
	}
	v[idx] = 1;
	dfs(idx + 1, cnt + 1);
	v[idx] = 0;
	dfs(idx + 1, cnt);
}
void init() {
	N = ret = 0;
	Min = 0x7fffffff;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		dfs(0, 0);
		printf("%d\n", Min);
		//printf("#%d %d\n", t, Min);
	}
	return 0;
}