#include <string>
#include <vector>
#include <iostream>
#include<stdio.h>
using namespace std;
vector<int>a;
bool chk(vector<vector<int>> &baseball,vector<int> &num) {// 조건이 맞는지 체크
	int cnt = 0;
	for (int i = 0; i < baseball.size(); i++) {// 행 만큼 반복
		int strike = 0, ball = 0;
		int n100 = 0;
		int n10 = 0;
		int n1 = 0;
		n100 = baseball[i][0] / 100;
		n10 = (baseball[i][0] % 100)/10;
		n1 = (baseball[i][0] % 100) % 10;
		//스트라이크 판별
		if (num[0] ==n100) {
			strike++;
		}
		if (num[1] == n10) {
			strike++;
		}
		if (num[2] == n1) {
			strike++;
		}
		//볼 판별
		if (num[0] == n10||num[0]==n1) {
			ball++;
		}
		if (num[1] ==n100||num[1]==n1) {
			ball++;
		}
		if (num[2] == n100||num[2]==n10 ) {
			ball++;
		}
		if (baseball[i][1] == strike && baseball[i][2] == ball) {
			cnt++;
		}
	}
	if (cnt == baseball.size()) { return true; }
	else return false;
}
void dfs(int idx,int num_chk[10],vector<vector<int>> &baseball,int &answer) {
	if (idx== 3) {
		//여기서 판별 같은 것인지
		//for (int i = 0; i < 3; i++) {
		//	cout << a[i];
		//}
		cout << endl;
		if (chk(baseball,a)) {
			answer++;
		}
		return;
	}
	for (int i = 1; i <= 9; i++) {
		if (num_chk[i] == 0) {
			num_chk[i] = 1;
			a.push_back(i);
			dfs(idx + 1, num_chk, baseball, answer);
			a.pop_back();
			num_chk[i] = 0;
		}
	}
}
int solution(vector<vector<int>> baseball) {
	int answer = 0;
	int num_chk[10] = { 0, }; // 순열시 중복 체크
	dfs(0, num_chk,baseball,answer);
	
	return answer;
}
int main(void) {

	cout << solution({ {123, 1, 1 }, { 356, 1, 0 }, { 327, 2, 0 }, { 489, 0, 1 } });
	return 0;
}