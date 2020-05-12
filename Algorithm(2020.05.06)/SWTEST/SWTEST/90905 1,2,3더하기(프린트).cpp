#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
int N;
int n;
int ret;
void init()
{
	N = n=0;
	scanf("%d", &N);
}
void dfs(int idx, int sum) {
	if (idx > n) return;//범위 넘어가는경우
	if (sum > n)return;
	if (sum == n) {
		ret++;
		return;
	}
	dfs(idx + 1, sum + 1);
	dfs(idx + 1, sum + 2);
	dfs(idx + 1, sum + 3);
}
int main(void) {
	init();
	for (int i = 0; i < N; i++) {
		ret = 0;
		scanf("%d", &n);
		dfs(0, 0);
		cout << ret<<endl;
	}
	return 0;
}