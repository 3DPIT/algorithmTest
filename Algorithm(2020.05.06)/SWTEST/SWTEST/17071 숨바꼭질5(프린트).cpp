#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<queue>
#include<set>
#include<map>
using namespace std;
const int S = 5e5 + 5;
int N, K;
int ret;
int chk[S][2];
struct Data {
	int num;
};
void init() {
	N = K = ret = 0;
	scanf("%d %d", &N, &K);
}
int BFS() {
	if (N == K) {
		return 0;
	}
	else {
		queue<int>q;
		q.push(N);
		int time = 1;
		int TT = K;
		chk[N][0] = 1;
		while (int size = q.size()) {
			TT += time;
			if (TT > 500000) {
				return -1;
			}



			while (size--) {
				int c = q.front(); q.pop();
				for (int i = 0; i < 3; i++) {
					int n = c;
					if (i == 0)n -= 1;
					if (i == 1)n += 1;
					if (i == 2)n *= 2;
					if (0 <= n && n <= 500000 && !chk[n][time % 2]) {
						chk[n][time % 2] = 1;
						q.push(n);
					}
				}
			}
			if (chk[TT][time % 2]) {
				return time;
			}
			time++;
		}
	}

}
int main(void) {
	int T = 1;
	init();
	int a = BFS();

	cout << a << endl;
	return 0;
}