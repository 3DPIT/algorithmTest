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
	vector<int>ret;//최종 나오는 순서 저장
	queue<Data>q;
	for (int i = 0; i < priorities.size(); i++) {
		q.push({ priorities[i],i });
	}
	while (!q.empty()) {
		Data J = q.front(); q.pop();// J문서
		int size = q.size();//현재 큐 사이즈
		int flag = 0;//우선순위 높은 문서 있는지 체크
		for (int i = 0; i < size; i++) {
			if (J.pri < q.front().pri) {
				flag = 1;
			}
				Data cJ = q.front(); q.pop();
				q.push(cJ);
	
		}
		if (flag==0) {
			ret.push_back(J.idx);// 출력 시키기
		}
		else {//우선순위가 높은게 있으면 제일 뒤로 보내기
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