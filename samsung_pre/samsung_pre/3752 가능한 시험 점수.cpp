#include<stdio.h>
#include<iostream>
using namespace std;
int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		int n[101] = { 0, };
		int D[10001] = { 0, };
		int sum = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &n[i]);
			sum += n[i];
		}
		D[0] = 1;
		for (int i = 0; i < N; i++) {
			for (int j = sum; j >= 0; j--) {
				if (D[j]) {
					D[j + n[i]] = 1;
				}
			}
		}

		int cnt=0;
		for (int i = 0; i < 10001; i++) {
			if (D[i])cnt++;
		}
		printf("#%d %d\n",t,cnt);
	}
	return 0;
}