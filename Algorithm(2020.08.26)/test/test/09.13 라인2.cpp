#include <string>
#include <vector>
#include <algorithm> 
#include <queue>
using namespace std;
int ballChk[300001];//���� ������ �;��ϴ°� üũ

vector<int> solution(vector<int> ball, vector<int> order) {
	vector<int> answer;
	int Max = *max_element(ball.begin(), ball.end());
	vector<int>v;//���� ���ø��� �� ����
	for (int i = 0; i < order.size(); i++) {//�ֹ� �ޱ� ����
		if (ball.front() == order[i]) {//ó������ �ֹ� ���� ���̶��
			answer.push_back(order[i]);
			ball.erase(ball.begin());//����
		}
		else if (ball.back()== order[i]) {//���������� �ֹ� ���� ���̶��
			answer.push_back(order[i]);
			ball.pop_back();
		}
		else {
			v.push_back(order[i]);
		}
		while (1) {//�����ִ� ��� ���� ��츦 ���� �ݺ�
			int flag = 0;
			for (int i = 0; i < v.size(); i++) {
				if (v.size() == 0)break;
				if (ball.front() == v[i]) {//�տ��ִ� ��컩��
					answer.push_back(v[i]);
					ball.erase(ball.begin());//����
					v.erase(v.begin() + i);
					flag = 1;
					break;
				}
				if (ball.back() == v[i]) {//�ڿ� �ִ� ��컩��
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