
#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
#define BLANC 9999
int cntMax = 0;
int visit[51] = { 0, };
vector<int>d;
void dfs(int num, int idx) {
	if (idx == cntMax) {
		return;
	}
	for (int i = 0; i < 19; i++) {
		if (visit[i] == num) {
			d.push_back(i);
			dfs(num + 1, idx + 1);
			d.pop_back();
		}
	}
}

int soul(vector<vector<int>>D) {
	//int size = v.size();
	//vector<vector<int> >pyramid (v.size(),vector<int>(v.size(), BLANC));
	//for (int i = 0; i < v.size(); i++) {
	//	pyramid[i][v[i][0]] = v[i][1];
	//}
	//vector<int> answer;
	//int cnt = 0;
	//for (int i = 0; i < pyramid.size(); i++) {
	//	for (int j = 0; j <= i; j++) {
	//			if (pyramid[i][j] == BLANC)cnt++;
	//			cout << i<<" "<< j << endl;
	//	}
	//}
	//while (cnt != 0) {
	//	for (int i = 0; i < pyramid.size() - 1; i++) {
	//		for (int j = 0; j <= i; j++) {
	//			if (cnt == 0)break;
	//			int a = pyramid[i][j];
	//			int b = pyramid[i + 1][j];
	//			int c = pyramid[i + 1][j + 1];
	//			if (a == BLANC && b != BLANC && c != BLANC) {
	//				pyramid[i][j] = b + c;
	//				cnt--;
	//			}
	//			if (b == BLANC && a != BLANC && c != BLANC) {
	//				pyramid[i+1][j] = a - c;
	//				cnt--;
	//			}
	//			if (c == BLANC && b != BLANC && a != BLANC) {
	//				pyramid[i+1][j+1] = a - b;
	//				cnt--;
	//			}
	//						
	//		}
	//	}
	//}
	//return 1;
	vector<int>G[50];

	for (int i = 0; i < 50; i++) {
		G[i].clear();
	}//그래프 초기화
	int sum = 0;
	for (int i = 0; i < D.size(); i++) {
		G[D[i][0]].push_back(D[i][1]);//그래프 연결
	}
	struct data {
		int n, cnt;
	};
	queue<data>q;
	q.push({ 0,0 });
		visit[0] = 1;

		while (!q.empty()) {
		data c = q.front(); q.pop();
		cntMax = c.cnt;
		for (int i = 0; i < G[c.n].size(); i++) {
			data n;
			n.n = G[c.n][i];
			n.cnt = c.cnt + 1;
			if (visit[n.n] == 0) {
				visit[n.n] = n.cnt;
				q.push(n);
			}
		}
	}
		dfs(1, 0);
	return 1;
}
int main(int argc, char** argv)
{
	soul({ {0, 1},
	{0, 2},
	{0, 3},
	{1, 4},
	{1, 5},
	{2, 6},{3, 7},
	{3, 8},
	{3, 9},
	{4, 10},
	{4, 11},
	{5, 12},
	{5, 13},
	{6, 14},
	{6, 15},{6, 16},{8, 17},{8, 18} });

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}