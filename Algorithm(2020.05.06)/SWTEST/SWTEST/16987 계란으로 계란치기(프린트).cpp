#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
int ret = 0x80000000;
struct Data {
	int S, W;
};
vector<Data>egg;
int N;
void init() {
	ret = 0x80000000;
	egg.clear();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int s, w;
		scanf("%d %d", &s, &w);
		egg.push_back({ s,w });
	}
}
void dfs(int idx) {
	if (idx == N) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			if (egg[i].S <= 0)cnt++;
		}
		ret = ret < cnt ? cnt : ret;
		return;
	}
	if (egg[idx].S <= 0)dfs(idx + 1);
	else {
		int flag = 0;
		for (int i = 0; i < N; i++) {
			if (i == idx || egg[i].S <= 0)continue;
			egg[idx].S = egg[idx].S - egg[i].W;
			egg[i].S = egg[i].S - egg[idx].W;
			flag = 1;
			dfs(idx + 1);

			egg[idx].S = egg[idx].S + egg[i].W;
			egg[i].S = egg[i].S + egg[idx].W;
		}
		if (flag == 0)dfs(N);
	}

}
int main(void) {
	int T = 1;
	//scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		dfs(0);
		cout << ret << endl;
	}
	return 0;
}