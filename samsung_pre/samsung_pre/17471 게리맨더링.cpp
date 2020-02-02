#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 21
int D[NS];
int N,sumMax;
int Min = 0x7fffffff;
int humanNum[NS][2];//구역별 인간수와 선거구
vector<int>G[NS];
int v[NS];
void Gdfs(int idx) {
	for (int i = 0; i < G[idx].size(); i++) {
		if (D[idx] == D[G[idx][i]] && 0 == v[G[idx][i]]) {
			v[G[idx][i]] = 1;
			Gdfs(G[idx][i]);
			}
	}
}
void dfs(int sum,int idx) {
	if (idx == N+1) {
		memset(v, 0, sizeof(v));
		int cnt = 0;
		for (int i = 1; i <= N; i++) {//탐색
			if (v[i] == 0) {
				v[i] = 1;
				cnt++;
				Gdfs(i);
			}
		}
		if (cnt == 2) {
			//cout << sum << " " << sumMax - sum << endl;
			if (abs((sumMax - sum) - sum) < Min) {
				Min = abs((sumMax - sum) - sum);// 최소값//
			}
		}
		return;
	}
	D[idx] = 1;
	dfs(sum,idx + 1);
	D[idx] = 0;
	dfs(sum + humanNum[idx][0], idx + 1);
}
void init() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &humanNum[i][0]);
		sumMax += humanNum[i][0];
	}
	//그래프 
	for (int i = 1; i <= N; i++) {
		int gNum;
		scanf("%d", &gNum);
		for (int j = 0; j < gNum; j++) {
			int num;
			scanf("%d", &num);
			G[i].push_back(num);
		}
	}
	dfs(0, 1);
}
int main(void) {
	init();
	if (0x7fffffff==Min) cout << -1 << endl;
	else cout << Min;
	return 0;
}