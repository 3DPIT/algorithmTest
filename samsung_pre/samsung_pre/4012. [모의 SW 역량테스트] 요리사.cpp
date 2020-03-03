#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 17
int map[NS][NS];
int D[NS];
int N;
int ret = 0x7fffffff;
struct cusine {
	cusine() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();

			scanf("%d", &N);
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					scanf("%d", &map[i][j]);
			dfs(0, 0);
			printf("#%d %d\n", t, ret);
		}
	}
	void dfs(int idx, int d) {
		if (idx == N)return;
		if (d == N / 2) {
			vector<int>A;
			vector<int>B;

			for (int i = 0; i < N; i++) {
				if (D[i] == 1)A.push_back(i);
				else B.push_back(i);
			}
			int mret = 0x7fffffff;
			int aSum, bSum;
			aSum = bSum = 0;
			for (int i = 0; i < A.size(); i++) {
		
				for (int j = 0; j < A.size(); j++) {
					//aSum = bSum = 0;
					//int flag1 = 0; int flag2 = 0;
					//aSum = bSum = 0;
					if (A[i] != A[j]) {
						//flag1 = 1;
						aSum += map[A[i]][A[j]];
					}
					if(B[i] != B[j]) {
						//flag2 = 1;
						bSum += map[B[i]][B[j]];
					}
					
				}
			}
			if (mret > abs(aSum - bSum))mret = abs(aSum - bSum);
			if (ret > abs(mret))ret = abs(mret);
			return;

		}
		D[idx] = 1;
		dfs(idx + 1, d + 1);
		D[idx] = 0;
		dfs(idx + 1, d);
	}
	void init() {
		ret = 0x7fffffff;
		memset(D, 0, sizeof(D));
		memset(map, 0, sizeof(map));
	}
}cusine;
int main(void) {

	return 0;
}