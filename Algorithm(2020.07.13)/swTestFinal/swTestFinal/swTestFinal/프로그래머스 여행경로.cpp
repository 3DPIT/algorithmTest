#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include<queue>
#include<map>
using namespace std;
int visit[10001];
void dfs(string startC, vector<vector<string>> &tickets, vector<string> &answer) {
	answer.push_back(startC);//��� ����
	for (int i = 0; i < tickets.size(); i++) {
		if (startC == tickets[i][0] && visit[i] == 0) {//������� ã�Ƽ� �迭 üũ 
			visit[i] = 1;
			dfs(tickets[i][1], tickets, answer);
		}
	}
}
vector<string> solution(vector<vector<string>> tickets) {
	vector<string> answer;
	int endCnt = 0;//��ü �迭 �湮�ϸ� ���� ���� ����
	sort(tickets.begin(), tickets.end());
	dfs("ICN", tickets,answer);//��� ��ġ, ������ ����, ���� ��� 



	return answer;
}
int main(void) {
	vector<string> a;
	//a = solution({ {"ICN", "JFK"},{"HND", "IAD"},{"JFK", "HND"} });
	a = solution({ {"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL", "SFO"}});
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}