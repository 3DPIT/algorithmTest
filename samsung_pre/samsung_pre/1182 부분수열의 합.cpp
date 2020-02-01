#include<stdio.h>
#include<iostream>
using namespace std;
int N, S;
int D[21];
int input[21];
int v[21];
int ret = 0;
void dfs(int sum,int idx) {
	if (idx == N) {
		if (sum == S) {
			ret++;
		}
		return;
	}

	dfs(sum, idx + 1);
	dfs(sum + input[idx], idx + 1);
}
int main(void) {
	cin >> N;
	cin >> S;
	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}
	dfs(0, 0);
	if (S == 0)ret--;
	cout << ret << endl;
	return 0;
}