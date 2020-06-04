#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define S 11
int n, k;
int visit[S][S];
int a[S];
int J, K, M;
int input[S][S];
vector<int>kyoung;
vector<int>min1;
int main(void) {
	scanf("%d %d", &n,&k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	for (int i = 0; i < 20; i++) {
		int a;
		scanf("%d", &a);
		kyoung.push_back(a);
	}
	for (int i = 0; i < 20; i++) {
		int a;
		scanf("%d", &a);
		min1.push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		a[i] = i;
	}
	do {
		J = K = M = 0;
		int ji = 0; int ki = 0; int mi = 0;
		int c = 0;
		for (int i = 1; i <=20; i++) {
			if (ji == n+1) {

				break;
			}
			if (J >= 3) {
				cout << 1 << endl;
				exit(0);
			}
			if (M >= 3) {
				break;
			}
			if (K >= 3) {
				break;
			}
			if (c == 0) {
				if (input[a[ji]][kyoung[i]] == 2) {
					ji++;
					J++;
				}
				else if (input[a[ji]][kyoung[i]] == 1) {
					ji++;
					K++;
				}
				else {
					K++;
					ji++;
				}
				c++;
			}
			else if (c == 1) {
				if (input[a[kyoung[i]]][min1[i]] == 2) {
					K++;
				}
				else if (input[a[kyoung[i]]][min1[i]] == 1) {
					M++;
				}
				else {
					M++;
				}
				c++;
			}
			else if (c == 2) {
				if (input[min1[i]][a[ji]] == 2) {
					ji++;
					M++;
				}
				else if (input[min1[i]][a[ji++]] == 1) {
					ji++;
					M++;
				}
				else {
					J++;
					ji++;
				}
				c = 0;
			}
		}
	} while (next_permutation(a + 1, a + 1 + n));
	cout << 0 << endl;
	return 0;
}
