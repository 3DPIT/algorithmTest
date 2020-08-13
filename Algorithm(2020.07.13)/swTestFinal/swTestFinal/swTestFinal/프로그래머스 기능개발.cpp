#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	queue<int> q;
	for (int i = 0; i < progresses.size(); i++) {
		int A = 0;
		A = (100 - progresses[i]);
		for (int j = 1; j <= 100; j++) {
			if (A <= speeds[i] * j) {
				A = j;// A에 만들어지는 일자 저장
				break;
			}
		}
		if(q.empty())q.push(A);
		else {
			if (q.front() < A) {
				answer.push_back(q.size());//만들어지는 갯수 저장
				while (!q.empty())q.pop();
				q.push(A);
			}
			else q.push(A);//앞선것보다 먼저 만들어진것 출하 못함 저장
		}

	}
	if (q.size() != 0)answer.push_back(q.size());
	return answer;
}
int main(void) {
	vector<int> a = solution({ 93,30,55 }, { 1,30,5 });
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}