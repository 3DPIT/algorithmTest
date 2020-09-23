#include <string>
#include <vector>
#include <algorithm> 
#include <queue>
using namespace std;
int ballChk[300001];//공의 나오고 싶어하는것 체크

vector<int> solution(vector<int> ball, vector<int> order) {
	vector<int> answer;
	int Max = *max_element(ball.begin(), ball.end());
	vector<int>v;//현재 나올만한 것 저장
	for (int i = 0; i < order.size(); i++) {//주문 받기 시작
		if (ball.front() == order[i]) {//처음값이 주문 받은 값이라면
			answer.push_back(order[i]);
			ball.erase(ball.begin());//빼기
		}
		else if (ball.back()== order[i]) {//마지막값이 주문 받은 값이라면
			answer.push_back(order[i]);
			ball.pop_back();
		}
		else {
			v.push_back(order[i]);
		}
		while (1) {//뺄수있는 경우 남은 경우를 위한 반복
			int flag = 0;
			for (int i = 0; i < v.size(); i++) {
				if (v.size() == 0)break;
				if (ball.front() == v[i]) {//앞에있는 경우빼기
					answer.push_back(v[i]);
					ball.erase(ball.begin());//빼기
					v.erase(v.begin() + i);
					flag = 1;
					break;
				}
				if (ball.back() == v[i]) {//뒤에 있는 경우빼기
					answer.push_back(v[i]);
					v.erase(v.begin() + i);
					ball.pop_back();
					flag = 1;
					break;
				}
			}
			if (flag == 0)break;
		}
	}

	return answer;
}
int main(void) {
	solution({ 11, 2, 9, 13, 24 }, { 9, 2, 13, 24, 11 });
	return 0;
}