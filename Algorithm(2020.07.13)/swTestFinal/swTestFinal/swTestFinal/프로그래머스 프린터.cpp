#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
struct Data {
	int pri,idx;
};
int solution(vector<int> priorities, int location) {
	int answer = 0;
	int J = 0;
	vector<int>ret;//���� ������ ���� ����
	queue<Data>q;
	for (int i = 0; i < priorities.size(); i++) {
		q.push({ priorities[i],i });
	}
	while (!q.empty()) {
		Data J = q.front(); q.pop();// J����
		int size = q.size();//���� ť ������
		int flag = 0;//�켱���� ���� ���� �ִ��� üũ
		for (int i = 0; i < size; i++) {
			if (J.pri < q.front().pri) {
				flag = 1;
			}
				Data cJ = q.front(); q.pop();
				q.push(cJ);
	
		}
		if (flag==0) {
			ret.push_back(J.idx);// ��� ��Ű��
		}
		else {//�켱������ ������ ������ ���� �ڷ� ������
			q.push(J);
		}
	}
	for (int i = 0; i < ret.size(); i++) {
		if (ret[i] == location) { answer = i+1; break; }
	}
	return answer;
}
int main(void) {

	cout << solution({ 2,1,3,2},2)<<endl;
	cout << solution({ 1, 1, 9, 1, 1, 1},0)<<endl;
	return 0;
}