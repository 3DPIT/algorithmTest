#include <string>
#include <vector>
#include <iostream>
#include<queue>
using namespace std;
int visit[51] = { 0, };// 중복 방지를 위한 배열
int flag = 0;
struct Data {
	string word;
	int cnt;
};
int solution(string begin, string target, vector<string> words) {
	int answer = 0;
	for (int i = 0; i < words.size(); i++) {// target값이 만약에 words에 없으면 바로 0리턴
		if (target == words[i]) {
			flag = 1;
		}
	}
	if (flag == 0)return 0;
	flag = 0;

	queue<Data>q;
	q.push({begin, 0});

	while (q.size()!=0) {//전체 탐색시작
		Data c = q.front(); q.pop();
		if (c.word == target) {
			answer = c.cnt;
			break;
		}
		for (int i = 0; i < words.size(); i++) {
			Data n=c;
			int wordSameCnt = 0;
			for (int j = 0; j < words[i].size(); j++) {//몇개의 알파벳이 다른지 검사
				if (c.word[j] != words[i][j]) {
					wordSameCnt++;
				}
			}
			if (wordSameCnt == 1) {//단어에서 알파벳 한개가 다른경우 푸시
				if (visit[i] == 0) {
					visit[i] = 1;
					n.word = words[i];
					n.cnt++;
					q.push(n);
				}

			}
		}
		
	}
	
	return answer;
}
int main(void) {
	//cout<<solution("hit", "cog", { "hot","dot","dog","lot","log","cog" })<<endl;
	cout<<solution("hit", "cog", { "hot", "dot", "dog", "lot", "log" });
	return 0;
}