#include <string>
#include <vector>
#include<iostream>
using namespace std;
#define COM_SIZE  201
int visit[COM_SIZE];
void dfs(int n,int idx, vector<vector<int>> com) {
	for (int i = 0; i < n; i++) {
		if (visit[i] == 0 && com[idx][i] == 1) {
			visit[i] = 1;
			dfs(n, i, com);
		}
	}
}
int solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	for (int i = 0; i < n; i++) {
		if (visit[i] == 0) {
			visit[i] = 1;
			answer++;
			dfs(n, i,computers);
		}
	}
	return answer;
}
int main(void) {
	cout << solution(3, {{1, 1, 0}, { 1, 1, 0}, { 0, 0, 1 }});
	return 0;
}