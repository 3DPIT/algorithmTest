#include <string>
#include <vector>
#include<iostream>
#include<algorithm>
using namespace std;
int cnt;
vector<int>d;
int dfsChk[4];
vector<int>dustks;
long long int max1 =-987654321;
void dfs(int idx,int d1, vector<long long >s) {
	if (d1 == cnt) {
		vector<long long >cs = s;
		while (cs.size()!=1) {
			for (int j = 0; j < d.size(); j++) {
				for (int i = 0; i < cs.size(); i++) {
					if(cs.size()==1)break;
					if (cs[i] == d[j]) {
						if (d[j] == -1) {
						cs[i-1]=cs[i - 1] + cs[i + 1];
						cs.erase(cs.begin() + i);
						cs.erase(cs.begin() + i);
						i--;
						}
						if (d[j] == -2) {
							cs[i-1] = cs[i - 1] - cs[i + 1];
							cs.erase(cs.begin() + i);
							cs.erase(cs.begin() + i);
							i--;
						}
						if (d[j] == -3) {
							cs[i-1] = cs[i - 1] * cs[i + 1];
							cs.erase(cs.begin()+i);
							cs.erase(cs.begin()+i);
							i --;

						}
					}
				}
			}
		}
		long long num = abs(cs[0]);
		if (max1 < num)max1 = num;
			return;
	}
	for (int i = 0; i < cnt;i++) {
		if (dfsChk[i] == 0) {
			dfsChk[i] = 1;
			d.push_back(dustks[i]);
			dfs(dustks[i],d1+1,s);
			d.pop_back();
			dfsChk[i] = 0;
		}
	}
}
long long solution(string expression) {
	long long answer = 0;
	cnt = 0;
	vector<long long >s;
	string a;
	int chk[4] = { 0, };
	for (int i = 0; i < expression.size(); i++) {
		if (expression[i] == '-' || expression[i] == '+' || expression[i] == '*') {
			if (chk[expression[i] - '*']==0) {
				chk[expression[i] -'*'] = 1;
				if (expression[i] == '*')dustks.push_back(-3);
				if (expression[i] == '-')dustks.push_back(-2);
				if (expression[i] == '+')dustks.push_back(-1);
				cnt++;
			}
			int num = atoi(a.c_str());;
			s.push_back(num);
			if(expression[i]=='+')s.push_back(-1);
			if (expression[i] == '-')s.push_back(-2);
			if (expression[i] == '*')s.push_back(-3);

			a.clear();
		}
		else
		a += expression[i];
	}
	sort(dustks.begin(), dustks.end());
	int num = atoi(a.c_str());;
	s.push_back(num);
	a.clear();

	dfs(0,0,s);

	return answer=max1;
}
int main(void) {
	//cout << solution("300+200*500+1-2");
	cout << solution("100-200*300-500+20");
//cout << solution("50*6-3*2");
	return 0;
}