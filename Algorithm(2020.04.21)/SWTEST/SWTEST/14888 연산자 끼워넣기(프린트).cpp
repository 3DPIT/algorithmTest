#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using namespace std;
#define NS 12
int N;
int num[NS];
int p, m, mm, d;
int Min = 0xfffffff;
int Max = 0x80000000;
void init() {
	N = 0;
	Min = 0x7fffffff;
	Max = 0x80000000;
	p = m = mm = d;
	memset(num, 0, sizeof(num));
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
	scanf("%d %d %d %d", &p, &m, &mm, &d);

}
void dfs(int idx, int plu, int min, int mul, int div, int sum) {
	if (idx == N-1) {
		cout << idx;
		printf("sum %d\n", sum);
		Max = Max < sum ? sum : Max;
		Min = Min > sum ? sum : Min;
		return;
	}
	if (plu)dfs(idx + 1, plu-1, min, mul, div, sum + num[idx + 1]);
	if (min)dfs(idx + 1, plu, min-1, mul, div, sum - num[idx+ 1]);
	if (mul)dfs(idx + 1, plu, min, mul-1, div, sum*num[idx + 1]);
	if (div)dfs(idx + 1, plu, min, mul, div-1, sum / num[idx + 1]);
}
int main(void) {
	int T = 3;
	for (int t = 1; t <= T; t++) {
		init();
		dfs(0, p, m, mm, d, num[0]);
		printf("#%d %d %d\n", t, Max, Min);
	}
	return 0;
}