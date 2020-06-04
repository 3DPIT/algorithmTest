#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int ret = 0x7fffffff;
int D[1000001];
int dfs(int n, int d) {

	if (n == 1) {
		return 0;
	}
	if (D[n] != -1)return D[n];
	if (n - 1 > 0) {
		int	temp = dfs(n - 1, d) + 1;
		D[n] = temp;
	}
	if (n % 2 == 0) {
		int	temp = dfs(n / 2, d) + 1;
		if (D[n] > temp)	D[n] = temp;
	}
	if (n % 3 == 0) {
		int temp = dfs(n / 3, d) + 1;
		if (D[n] > temp)	D[n] = temp;
	}


	return D[n];
}
int main(void) {
	int n;
	scanf("%d", &n);
	memset(D, -1, sizeof(D));
	//cout << dfs(n, 0) << endl;
	D[1] = 0;

	for (int i = 2; i <= n; i++) {
		D[i] = D[i - 1] + 1;
		if (i % 2 == 0 && D[i] > D[i / 2] + 1) {
			D[i] = D[i / 2] + 1;
		}
		if (i % 3 == 0 && D[i] > D[i / 3] + 1) {
			D[i] = D[i / 3] + 1;
		}
	}
	cout << D[n] << endl;
	//cout << ret << endl;
	return 0;
}