#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
bool cmp(string a, string b) {
	return a + b > b + a; //�ΰ��� ���϶� ū ������ ����
}
string solution(vector<int> numbers) {
	string answer = "";
	vector<string> copyNum;
	for (int i = 0; i < numbers.size(); i++) {
		copyNum.push_back(to_string(numbers[i]));//���� ���ڿ� ��ȯ
	}
	sort(copyNum.begin(), copyNum.end(), cmp);// ����
	for (int i = 0; i < copyNum.size(); i++) {//���� ū�� �����
		answer += copyNum[i];
	}
	if (answer.front() == '0')return "0"; //00000 �� 0���� ǥ��
	return answer;
}
int main(void) {
	string a = solution({ 6,10,2 });
	cout << a << '\n';
	a.clear();
	a = solution({ 3,30,34,5,9 });
	cout << a << '\n';
	a.clear();
	a = solution({ 0,0,0,0 });
	cout << a << '\n';

}
