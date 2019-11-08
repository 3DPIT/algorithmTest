#include <string>
#include <vector>
#include<iostream>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
	vector<string> answer;
	for (int i = 0; i < n; i++) {
		int num = (arr1[i] | arr2[i]);
		string a;
		int cnt = 0;
		while (cnt!=n) {
			cnt++;
			if (num % 2 == 0)a.push_back(' ');
			else a.push_back('#');
			num /= 2;
	}
		string b;
		for (int i = a.size()-1; i >=0; i--) {
			b.push_back(a[i]);
		}
		answer.push_back(b);
	}
	return answer;
}
int main(void) {

	vector<string> b = solution(6, { 46, 33, 33 ,22, 31, 50 }, { 27 ,56, 19, 14, 14, 10 });
	for (int i = 0; i < 6; i++) {
		cout << b[i] << endl;
	}
	return 0;
}