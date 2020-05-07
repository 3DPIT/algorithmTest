#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;

int N;
int v[11] = { 0, };
vector<int>a;
void dfs(int d) {
	if (d == N-1) {
		for (int i = 0; i < a.size(); i++) {
			cout << a[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 2; i <= N; i++) {
		if (v[i] == 0) {
			v[i] = 1;
			a.push_back(i);
			dfs(d + 1);
			a.pop_back();
			v[i] = 0;
		}

	}
}
void init() {
	scanf("%d", &N);
	dfs(0);

}
int main(void) {
	init();
	return 0;
}