#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<int>d;//������ �����Ѱ�
int chk[8];//���� �ߺ� üũ
int ret;// ������
int numChk[9999999];
bool primNum(int num) {
	if (numChk[num] == 1)return false;// ���� ���� ���� ��찡 �ִ°�� �ɷ��ֱ�
	if (numChk[num] == 0) numChk[num] = 1;
	if (num == 1||num==0)return false;
	for (int i = 2; i <num; i++) {// �Ҽ� �Ǻ�
		if (num%i == 0)return false;
	}
	return true;
}
void dfs(int idx,vector<int> &v ) {
	if (idx == v.size()) return;
	if(d.size()!=0) {
		int sum = 0;//������ �� ���Ǵ°�
		int ten = 1;//10�� ����
		for (int i = 0; i < d.size(); i++) {
			sum += d[i] * ten;
			ten *= 10;
		}
		if (primNum(sum)) {//�Ҽ� �Ǻ� 
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