#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define NS 21
int member[NS];
int N, B;
int ret;
int Min = 0x7fffffff;
struct Seo {
	Seo() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			scanf("%d %d", &N, &B);
			for (int Ni = 0; Ni < N; Ni++) {
				scanf("%d", &member[Ni]);
			}
			dfs(0, 0);
			ret = Min;
			printf("#%d %d\n", t, ret);
		}
	}
	void init() {
		ret = 0;
		Min = 0x7fffffff;
		memset(member, 0, sizeof(member));
	}
	void dfs(int sum, int idx) {
		//if (Min < sum)return;
		if (idx == N) {
			if (sum >= B) {
				if (Min > (sum - B))Min = (sum - B);
			}
			return;
		}
		dfs(sum + member[idx], idx + 1);

		dfs(sum, idx + 1);
	}
}Seo;
int main(void) {
	return 0;
}