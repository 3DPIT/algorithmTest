#include<stdio.h>
#include<iostream>
#include <string>
#include <vector>
using namespace std;
int mathGiveUp[4][10] = { 
{0,},
{1,2,3,4,5,},//수포자 1
{2,1,2,3,2,4,2,5},//수포자2
{3,3,1,1,2,2,4,4,5,5}//수포자3
};
int mathIdx[4] = {0,5,8,10 };//수포자 1,2,3
vector<int> solution(vector<int> answers) {
	vector<int> answer;
	vector<int> correctCnt;
	correctCnt.push_back(0);//0번 부터 시작이라 먼저 넣음
	int max = 0x80000000;
	for (int i = 1; i <= 3; i++) {
		int idx = 0;
		int cnt = 0;
		for (int j = 0; j < answers.size(); j++) {
			if (idx == mathIdx[i])idx = 0;
			if (answers[j] == mathGiveUp[i][idx]) {// 답이 맞으면 cnt  증가
				cnt++;
			}
			idx++;
		}
		correctCnt.push_back(cnt);//각 수포자가 맞은 문제 갯수 저장
		max = max < cnt ? cnt : max;//최대값 찾기
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
