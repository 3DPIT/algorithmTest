#include<stdio.h>
#include<iostream>
#include <string>
#include <vector>
using namespace std;
int mathGiveUp[4][10] = { 
{0,},
{1,2,3,4,5,},//������ 1
{2,1,2,3,2,4,2,5},//������2
{3,3,1,1,2,2,4,4,5,5}//������3
};
int mathIdx[4] = {0,5,8,10 };//������ 1,2,3
vector<int> solution(vector<int> answers) {
	vector<int> answer;
	vector<int> correctCnt;
	correctCnt.push_back(0);//0�� ���� �����̶� ���� ����
	int max = 0x80000000;
	for (int i = 1; i <= 3; i++) {
		int idx = 0;
		int cnt = 0;
		for (int j = 0; j < answers.size(); j++) {
			if (idx == mathIdx[i])idx = 0;
			if (answers[j] == mathGiveUp[i][idx]) {// ���� ������ cnt  ����
				cnt++;
			}
			idx++;
		}
		correctCnt.push_back(cnt);//�� �����ڰ� ���� ���� ���� ����
		max = max < cnt ? cnt : max;//�ִ밪 ã��
	}
	for (int i = 1; i <= 3; i++) {
		if (max == correctCnt[i]) {
			answer.push_back(i);
		}
	}
	return answer;
}
int main(void) {
	vector<int> ret = solution({1,2,3,4,5});
	ret = solution({1,3,2,4,2});
	for (int i = 0; i <ret.size(); i++) {
		cout << ret[i] << " ";
	}
	cout << endl;
	return 0;
}
