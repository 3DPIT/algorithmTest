#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string.h>
using namespace std;
#define S 11
int N;
int num[S];
int visit[S];
int D[S];
int ret;
struct Data {
	int num, cnt;
};
struct elect {
	vector<int>G[S];
	elect() {
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &num[i]);
		}
		GraphMake();
		dfs(0);
		if (ret == 0x7fffffff)ret = -1;
		printf("%d\n", ret);
	}
	void init() {
		memset(num, 0, sizeof(num));
		memset(visit, 0, sizeof(visit));
		memset(D, 0, sizeof(D));
		N = 0;
		ret = 0x7fffffff;
	}
	bool search() {
		memset(visit,0,sizeof(visit));
		vector<int>A;
		vector<int>B;
		int cnt = 0, cnt1 = 0;
		for (int i = 0; i < N; i++) {// 선거구 나누기
			if (D[i] == 1)A.push_back(i+1);
			else B.push_back(i + 1);
		}
		if (A.size() == 0 || B.size() == 0) return false;
		for (int i = 0; i < A.size(); i++) {
			if (visit[A[i]] == 0) {
				visit[A[i]] == 1;
				cnt++;
				dfs(A[i], 1);
			}
		}
		for (int i = 0; i < B.size(); i++) {
			if (visit[B[i]] == 0) {
				visit[B[i]] == 1;
				cnt1++;
				dfs(B[i], 0);
			}
		}
		if (cnt+cnt1 != 2)return false;
		else return true;
		
	}
	void dfs(int idx, int cnt) {// 탐색
		for (int i = 0; i < G[idx].size(); i++) {
			if (visit[G[idx][i]] == 0&&D[G[idx][i]-1]==cnt) {
				visit[G[idx][i]] = 1+cnt;
				dfs(G[idx][i], cnt);
			}
		}
	}
	void dfs(int idx) {// 순열 
		if (idx == N)return;
		else {
			if (search()){
				int A, B;
				A = B = 0;
				for (int i = 0; i < N; i++) {
					if (D[i] == 1) {
						A += num[i];
					}
					else {
						B += num[i];
					}
				}
				if(ret>abs(A-B))ret=abs(A-B);
			}
		}
		D[idx] = 1;
		dfs(idx + 1);
		D[idx] = 0;
		dfs(idx + 1);

	}
	void GraphMake(){
		int n;
		for (int idx = 1; idx <= N; idx++) {
			scanf("%d", &n);
			for (int i = 0; i < n; i++) {
				int a;
				scanf("%d", &a);
				G[idx].push_back(a);
			}
		}
	}
}elect;
int main(void) {
	return 0;
}