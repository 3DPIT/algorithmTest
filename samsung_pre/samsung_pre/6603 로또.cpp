#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define S 14
int N;
int num[S];
int ret;
vector<int>v;
struct Lotte {
	Lotte() {
		while (scanf("%d", &N)&&N!=0 ) {
			for (int i = 0; i < N; i++) {
				scanf("%d", &num[i]);
			}
			dfs(0, 0);
			printf("\n");//
		}
		//return;
	}
	void dfs(int d, int cnt) {
		if (cnt == 6) {
			for (int i = 0; i < v.size(); i++) {
				printf("%d ", v[i]);
			}
			printf("\n");
			return;
		}
		for (int i = d; i < N; i++) {
			v.push_back(num[i]);
			dfs(i + 1, cnt + 1);
			v.pop_back();
		}
	}
}L;
int main(void) {
	return 0;
}