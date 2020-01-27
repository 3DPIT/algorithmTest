#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define NS 26
char apt[NS][NS];
int v[NS][NS];
int home[630];
int N;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int Cnt=1;
int aptCnt;
vector<int>aptC;
void dfs(int y, int x, int cnt) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if ('1' == apt[ny][nx] && 0 == v[ny][nx]) {
			v[ny][nx] = 1;
			Cnt++;
			dfs(ny, nx, Cnt);
		}
	}
}
void aptSearch() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ('1' == apt[i][j]&&0==v[i][j]) {
				v[i][j] = 1;
				dfs(i, j, 0);
				home[Cnt] = 1;		
				aptC.push_back(Cnt);
				Cnt = 1;
				aptCnt++;
			}
		}
	}
}
void lastPrint() {
	sort(aptC.begin(), aptC.end());
	for (int i = 0; i < aptC.size();i++) {
		cout << aptC[i] << endl;
	}
}
void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> apt[i];
	}
	aptSearch();
}
int main(void) {
	init();
	cout << aptCnt<<endl;
	lastPrint();
	return 0;
}