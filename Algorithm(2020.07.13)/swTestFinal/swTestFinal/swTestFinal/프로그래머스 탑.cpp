#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> heights) {
	vector<int> answer;
	stack<int>s; //데이터 거꾸로 담기
	for (int i = heights.size()-1; i >= 1; i--) {
		int flag = 0;// 수신 받는곳 없는거 체크 변수
		for (int j = i - 1; j >= 0; j--) {
			if (heights[i] < heights[j]) {
				s.push(j+1);
				flag = 1;// 들어간거 체크 
				break;
			}
		}
		if (flag==0) {
			s.push(0);
		}
	}
	s.push(0);
	while (!s.empty()) {
		answer.push_back(s.top()); s.pop();
	}
	return answer;
}

int main(void) {
	vector <int>a;
	//a = solution({ 6,9,5,7,4 });
	//a=solution({ 3,9,9,3,5,7,2 });
	a=solution({ 1,5,3,6,7,6,5 });
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}