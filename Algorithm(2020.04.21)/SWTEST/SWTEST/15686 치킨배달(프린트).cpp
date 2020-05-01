#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define NS 51
int map[NS][NS];
int N, M,ret;
struct Data {
	int y, x;
};
vector<Data>chichken;
vector<Data>home;
vector<int>D[NS];
vector<int>v;
void init() {
	memset(map, 0, sizeof(map));
	chichken.clear();
	home.clear();
	for (int i = 0; i < NS; i++)D[i].clear();
	N = M = ret=0;
	ret = 0x7fffffff;
	scanf("%d %d", &N,&M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)home.push_back({ i,j });
			else if (map[i][j] == 2)chichken.push_back({ i,j });
		}
	}
	for (int i = 0; i < home.size(); i++) {
		for (int j = 0; j < chichken.size(); j++) {
			int d = abs(home[i].y - chichken[j].y)
				+ abs(home[i].x - chichken[j].x);
			D[i].push_back(d);//거리 저장
		}
	}
}
void print(string num, int idx) {
	cout << num << endl;
	if (idx == 0) {
		for (int i = 0; i < v.size(); i++) {
			cout<<" "<<v[i];
		}
		cout << endl;
	}
}
void dfs(int idx, int cnt) {
	if (idx >chichken.size())return;
	if (cnt == M) {
		//함수- 뽑힌 결과의최소 구하기
		int sum = 0;
		print("뽑힌값들", 0);
		for (int i = 0; i < home.size(); i++) {
			int Min = 0x7fffffff;
			for (int j = 0; j < v.size(); j++) {
				if (Min > D[i][v[j]])Min = D[i][v[j]];
			}
			sum += Min;
		}
		ret = ret > sum ? sum : ret;
		return;
	}
	v.push_back(idx);
	dfs(idx + 1, cnt + 1);
	v.pop_back();
	dfs(idx + 1, cnt);

}
int main(void) {
	int T = 4;
	for (int t = 1; t <=T; t++) {
		init();
		dfs(0, 0);
		printf("#%d %d\n", t, ret);
		//printf("%d\n", ret);
	}
	
	return 0;
}