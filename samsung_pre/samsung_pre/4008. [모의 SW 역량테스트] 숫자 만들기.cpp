#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define NS 13
long long int ret;

struct mathS {
	int ret = 0;
	int Max = 0x80000000;
	int Min = 0x7fffffff;
	int D[5] = { 0, };
	int num[NS] = { 0, };
	int C = 0;
	int N;
	mathS() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			scanf("%d", &N);
			for (int i = 0; i < 4; i++) {
				scanf("%d", &D[i]);
				C += D[i];
			}
			for (int i = 0; i < N; i++) {
				scanf("%d", &num[i]);
			}
			dfs(0, num[0], D[0], D[1], D[2], D[3]);
			ret = Max - Min;
			printf("#%d %lld\n", t, ret);
		}
	}
	void init() {
		N = 0;
		ret = 0;
		Max = 0x80000000;
		Min = 0x7fffffff;
		memset(D, 0, sizeof(D));
		memset(num, 0, sizeof(num));
		C = 0;
	}
	void dfs(int idx,int sum, int plus,int minus, int mul,int div) {
		if (idx == N-1) {
			if (Max < sum)Max = sum;
			if (Min > sum)Min = sum;
			return;
		}
		if (plus)dfs(idx + 1, sum + num[idx + 1], plus-1, minus, mul, div);
		if (minus)dfs(idx + 1, sum - num[idx + 1], plus, minus-1, mul, div);
		if (mul)dfs(idx + 1, sum * num[idx + 1], plus, minus, mul-1, div);
		if (div)dfs(idx + 1, sum / num[idx + 1], plus, minus, mul, div-1);
	}
}mathS;
int main(void) {

	return 0;
}