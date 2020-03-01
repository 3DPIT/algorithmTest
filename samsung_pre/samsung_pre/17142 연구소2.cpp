#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define S 51
int N, M;
int virusMap[S][S];
int chk[S][S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int Min = 0x7fffffff;
vector<int>v;
struct Lab {
	struct Data {
		int y, x, cnt;
	};

	vector<Data>virusInfo;
	Lab() {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &virusMap[i][j]);
				if (virusMap[i][j] == 2) {
					virusInfo.push_back({ i,j,1 });
				}
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < N;
	}
	int mapChk(int chk1[S][S]) {
		int num = 0;
		int Max = 0x80000000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (virusMap[i][j] != 1 && chk1[i][j] == 0)return 0;
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (virusMap[i][j] != 1 && chk1[i][j] != 0) {
					if (Max < chk1[i][j])Max = chk1[i][j];
				}
			}
		}
		return Max;
	}
	void dfs(int idx, int d) {//조합 뽑아내기
		if (idx == M) {//뽑아낸 것에 대해서 
			queue<Data>vq;
			memset(chk, 0, sizeof(chk));
			for (int i = 0; i < v.size(); i++) {
				vq.push(virusInfo[v[i]]);
				chk[virusInfo[v[i]].y][virusInfo[v[i]].x] = 1;
			}
			while (!vq.empty()) {
				Data c = vq.front(); vq.pop();
				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir]; n.x = c.x + dx[dir]; n.cnt = c.cnt + 1;
					if (safe(n.y, n.x) && virusMap[n.y][n.x] != 1 && chk[n.y][n.x] == 0) {
						chk[n.y][n.x] = n.cnt;
						vq.push(n);
					}
				}
			}
			int num = mapChk(chk);
			if (num != 0) {
				if (Min > num)Min = num;
				return;
			}
		}
		for (int i = d; i < virusInfo.size(); i++) {
			v.push_back(i);
			dfs(idx + 1, i + 1);
			v.pop_back();

		}
	}
}lab;
int main(void) {
	lab.dfs(0, 0);

	if (Min == 0x7fffffff)cout << -1 << endl;
	else {
		if (Min != 0)Min--;


		cout << Min << endl;
	}
	return 0;
}