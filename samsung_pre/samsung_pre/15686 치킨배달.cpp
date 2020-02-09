#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define S 51
int N, M;
int mapInfo[S][S];
int Min = 0x7fffffff;
struct Data {
	int y, x;
};
vector<Data>home, chicken;
vector<int>v;
struct DataStore {
	DataStore() {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &mapInfo[i][j]);
				if (mapInfo[i][j] == 1) {
					home.push_back({i,j});
				}
				else if (mapInfo[i][j] == 2) {
					chicken.push_back({ i,j });
				}
			}
		}
	}
	void dfs(int idx,int cnt) {
		if (idx > chicken.size())return;
		if (cnt == M) {
			int sum = 0;
			for (int i = 0; i < home.size(); i++) {
				int sumMin = 0x7fffffff;
				for (int j = 0; j < v.size(); j++) {
					int d = abs(home[i].y - chicken[v[j]].y) + abs(home[i].x - chicken[v[j]].x);
					if (sumMin > d)sumMin = d;
				}
				sum += sumMin;
			}
			if (Min > sum)Min = sum;
			return;
		}
		v.push_back(idx);
		dfs(idx + 1, cnt + 1);
		v.pop_back();
		dfs(idx + 1, cnt);
	}
}C;
int main(void){
	C.dfs(0, 0);
	printf("%d\n", Min);
	return 0;
}