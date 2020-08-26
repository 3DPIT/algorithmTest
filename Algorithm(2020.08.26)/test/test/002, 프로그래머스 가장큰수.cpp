#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
bool cmp(string a, string b) {
	return a + b > b + a; //두개를 붙일때 큰 순으로 정렬
}
string solution(vector<int> numbers) {
	string answer = "";
	vector<string> copyNum;
	for (int i = 0; i < numbers.size(); i++) {
		copyNum.push_back(to_string(numbers[i]));//정수 문자열 변환
	}
	sort(copyNum.begin(), copyNum.end(), cmp);// 정렬
	for (int i = 0; i < copyNum.size(); i++) {//가장 큰수 만들기
		answer += copyNum[i];
	}
	if (answer.front() == '0')return "0"; //00000 을 0으로 표시
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
