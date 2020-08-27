#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
bool cmp(int a, int b) {
	return a > b;
}
int solution(vector<int> citations) {
	int answer = 0;
	sort(citations.begin(), citations.end(), cmp);
	int maxNum = citations[citations.size() - 1];
	for (int i = 0; i < citations.size(); i++) {
		if (citations[i] <= i) break;
			answer = i;
	}

	return answer;
}
int main(void) {
	cout << solution({ 1,7,0,1,6,4 });
	return 0;
}