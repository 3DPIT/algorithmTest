#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<int>d;//순열값 저장한곳
int chk[8];//순열 중복 체크
int ret;// 최종값
int numChk[9999999];
bool primNum(int num) {
	if (numChk[num] == 1)return false;// 같은 값을 가진 경우가 있는경우 걸러주기
	if (numChk[num] == 0) numChk[num] = 1;
	if (num == 1||num==0)return false;
	for (int i = 2; i <num; i++) {// 소수 판별
		if (num%i == 0)return false;
	}
	return true;
}
void dfs(int idx,vector<int> &v ) {
	if (idx == v.size()) return;
	if(d.size()!=0) {
		int sum = 0;//정수형 값 계산되는곳
		int ten = 1;//10씩 증가
		for (int i = 0; i < d.size(); i++) {
			sum += d[i] * ten;
			ten *= 10;
		}
		if (primNum(sum)) {//소수 판별 
			ret++;
		}
		//cout << sum<<endl;
	}
	for (int i = 0; i < v.size(); i++) {
		if (chk[i] == 0) {
			chk[i] = 1;
			d.push_back(v[i]-48);
			dfs(i, v);
			d.pop_back();
			chk[i] = 0;
		}
	}

	
}
int solution(string numbers) {
	int answer = 0;
	vector<int>v;
	for (int i = 0; i < numbers.size(); i++) {
		v.push_back(numbers[i]);
	}
	dfs(0, v);

	return answer=ret;
}
int main(void) {
	//cout << solution("17");
	cout << solution("011");
	//cout << solution("123");
	return 0;
}