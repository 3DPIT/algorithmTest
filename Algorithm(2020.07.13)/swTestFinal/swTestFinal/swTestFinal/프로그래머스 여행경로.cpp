#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include<queue>
#include<map>
using namespace std;
int visit[10001];
int flag = 0;
int dfs(string startC, vector<vector<string>> &tickets, vector<string> &temp, vector<string> &answer,int cnt) {
	temp.push_back(startC);
	if (cnt == tickets.size())
	{
		answer = temp;
		return 1;
	}
	for (int i = 0; i < tickets.size(); i++) {
		if (startC == tickets[i][0] && visit[i] == 0) {//출발점을 찾아서 배열 체크 
			visit[i] = 1;
			int a= dfs(tickets[i][1], tickets,temp, answer,cnt+1);
			if (a == 1) return 1;
			visit[i] = 0;
		}
	}
	temp.pop_back();
	return 0;
}
vector<string> solution(vector<vector<string>> tickets) {
	vector<string> answer,temp;
	int endCnt = 0;//전체 배열 방문하면 종료 위한 변수
	sort(tickets.begin(), tickets.end());

	dfs("ICN", tickets,temp,answer,0);//출발 위치, 여행지 정보, 여행 경로 




	return answer;
}
int main(void) {
	vector<string> a;
	//a = solution({ {"ICN", "JFK"},{"HND", "IAD"},{"JFK", "HND"} });
	//a = solution({ {"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL", "SFO"}});
	a = solution({ {"ICN","C"},{"C","L"},{"L","D"},{"D","S"},{"S","C"} });
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}