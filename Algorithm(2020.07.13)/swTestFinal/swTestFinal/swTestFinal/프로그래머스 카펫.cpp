#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(int brown, int yellow) {
	vector<int> answer;
	int sum = brown + yellow;
	int i = 3;
	int j = 0;
	for ( i = 3; i <= sum; i++) {//3이상의 크기부터 돌리기
		 j = sum / i;
		if (i <= j) {
			if (yellow == (i-2) * (j-2)) {
				answer.push_back(j);
				answer.push_back(i);
				break;
			}
		}
	}
	return answer;
}
int main(void) {
	vector<int> a;
	//a= solution(10, 2);
//	a= solution(8, 1);
	a= solution(24, 24);
	cout << a[0]<<" "<< a[1] << endl;
	return 0;
}