#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> prices) {
	vector<int> answer;
	for (int i = 0; i < prices.size(); i++) {// 반복
		int time = 0;
		for (int j = i+1; j < prices.size(); j++) {
			++time;// 증가
			if (prices[i] >prices[j])break;
		}
		answer.push_back(time);
	}
	return answer;
}
vector<int> solution1(vector<int> prices) {
	vector<int> answer(prices.size());
	stack<int>s;
	for (int i = 0; i < prices.size(); i++) {
		while (!s.empty() && prices[s.top()] > prices[i]) {
			answer[s.top()] = i - s.top();
			s.pop();
		}
		s.push(i);//제일 위에꺼만 비교가능
	}

	while (!s.empty()) {
		answer[s.top()] = prices.size() - s.top() - 1;
		s.pop();
	}
	return answer;
}

int main(void) {
	vector<int>a = solution1({ 1,2,3,2,3 });
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
}