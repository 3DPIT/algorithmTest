#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define NS 10
int ret;
int N;
vector<int>map;
int chk[NS] = { 0, };
void init() {
	N = 0;
	ret = 0x80000000;
	map.clear();
	scanf("%d",&N);
	for (int i = 0; i < N; i++) {
		int a;
		scanf("%d", &a);
		map.push_back(a);
	}
}
void dfs(int cn, int sum) {
	if (cn == 1) {//에너지 다모은후
		if (ret < sum)ret = sum;
		return;
	}
	vector<int>cmap;
	for (int i = 1; i < cn; i++) {
		cmap = map;
			int s = (map[i - 1] * map[i + 1]);
			map.erase(map.begin() + i);
			dfs(cn- 1, sum + s);
			map.insert(map.begin() + i, cmap[i]);
		map = cmap;

	}


}
int main(void) {
	int T=1;
	//scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		dfs(N-1, 0);

		//printf("#%d %d\n", t, ret);
		printf("%d\n", ret);

	}
	return 0;
}