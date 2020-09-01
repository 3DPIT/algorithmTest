#include<stdio.h>
#include<iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
#define N_SIZE 20001
struct Data {
	int num, cnt;
};
int solution(int n, vector<vector<int>> edge) {
	int answer = 0;
	vector<int>G[N_SIZE];

	for (int i = 0; i < edge.size(); i++) {
		//양방향
		G[edge[i][0]].push_back(edge[i][1]);
		G[edge[i][1]].push_back(edge[i][0]);
	}
	queue<Data>q;
	int visit[N_SIZE] = { 0, };
	q.push({ 1,1 });
	visit[1] = 1;
	int cnt = 0;
	int cntArr[N_SIZE] = { 0, };	cntArr[1]++;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		for (int i = 0; i < G[c.num].size(); i++) {
			Data n;
			n.num = G[c.num][i]; n.cnt = c.cnt + 1;
			if (visit[n.num] == 0) {
				visit[n.num] = n.cnt;
				cntArr[n.cnt]++;//각 노드의 위치의 갯수 저장
				cnt = n.cnt;
				q.push(n);
			}
		}
	}
	answer = cntArr[cnt];//바로 찾기

	return answer;
}
int main(void) {
	cout << solution(6, { {3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2} });

	return 0;
}