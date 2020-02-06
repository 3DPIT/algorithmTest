#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define NS 21
int D[NS];
int Min = 0x7fffffff;
int N;
int field[NS][NS];
struct StartLink {
	StartLink() {
		scanf("%d", &N);
		for (int i =1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &field[i][j]);
			}
		}
	}
	void dfs(int idx, int cnt) {
		if (idx > N + 1)return;
		if (N / 2 == cnt) {
			//for (int i = 1; i <= N; i++) {
			//	cout << D[i] << " ";
			//}
			//cout << endl;
			vector<int>startTeam;//½ºÅ¸Æ®ÆÀ
			vector<int>linkTeam;//¸µÅ©ÆÀ
			int startsum=0;
			int linksum=0;
			for (int i = 1; i <= N; i++) {
				if (D[i] == 1)startTeam.push_back(i);
				else linkTeam.push_back(i);
			}
			for (int i = 0; i < startTeam.size(); i++) {
				for (int j = 0; j < startTeam.size(); j++) {
					if (i == j)continue;
					startsum += field[startTeam[i]][startTeam[j]];
					linksum += field[linkTeam[i]][linkTeam[j]];
				}
			}

			if (Min > abs(startsum - linksum)) {
				Min = abs(startsum - linksum);
			}
			return;
		}
		D[idx] = 1;
		dfs(idx + 1, cnt + 1);
		D[idx] = 0;
		dfs(idx+1, cnt);
	}
}Sports;
int main(void) {
	Sports.dfs(1, 0);

	cout << Min << endl;
	return 0;
}