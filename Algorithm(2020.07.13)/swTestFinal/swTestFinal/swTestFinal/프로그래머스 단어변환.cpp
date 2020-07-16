#include <string>
#include <vector>
#include <iostream>
#include<queue>
using namespace std;
int visit[51] = { 0, };// �ߺ� ������ ���� �迭
int flag = 0;
struct Data {
	string word;
	int cnt;
};
int solution(string begin, string target, vector<string> words) {
	int answer = 0;
	for (int i = 0; i < words.size(); i++) {// target���� ���࿡ words�� ������ �ٷ� 0����
		if (target == words[i]) {
			flag = 1;
		}
	}
	if (flag == 0)return 0;
	flag = 0;

	queue<Data>q;
	q.push({begin, 0});

	while (q.size()!=0) {//��ü Ž������
		Data c = q.front(); q.pop();
		if (c.word == target) {
			answer = c.cnt;
			break;
		}
		for (int i = 0; i < words.size(); i++) {
			Data n=c;
			int wordSameCnt = 0;
			for (int j = 0; j < words[i].size(); j++) {//��� ���ĺ��� �ٸ��� �˻�
				if (c.word[j] != words[i][j]) {
					wordSameCnt++;
				}
			}
			if (wordSameCnt == 1) {//�ܾ�� ���ĺ� �Ѱ��� �ٸ���� Ǫ��
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