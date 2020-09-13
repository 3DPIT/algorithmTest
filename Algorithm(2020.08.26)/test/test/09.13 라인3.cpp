#include <string>
#include <vector>
#include<iostream>
using namespace std;
int ret = 0x7fffffff;
int retNum = 0x7fffffff;
int num[10] = { 0,1,10,100,1000,10000,100000,1000000,10000000,100000000, };
void dfs(int idx, string num,int cnt) {
	if (num.size()==1) {//한자리 수인경우
		if (ret > cnt) {
			ret = cnt;
			if (retNum > stoi(num)) {
				retNum = stoi(num);
			}
		}
		return;
	}
	
	for (int i = 0; i < num.size()-1; i++) {
		string a, b;
		for (int j = 0; j <= i; j++) {
			a += num[j];
		}
		for (int j = i+1; j <num.size(); j++) {//숫자 분리
			b += num[j];
		}
		if(a[0]=='0'||b[0]=='0')continue;
		int n = stoi(a) + stoi(b);
		cout << n<<endl;
		dfs(i, to_string(n), cnt + 1);
	}
}
vector<int> solution(int n) {
	vector<int> answer;
	dfs(0,to_string(n), 0);
	answer.push_back(ret);
	answer.push_back(retNum);
	return answer;
}
int main(void) {
	solution(73425);
	return 0;
}