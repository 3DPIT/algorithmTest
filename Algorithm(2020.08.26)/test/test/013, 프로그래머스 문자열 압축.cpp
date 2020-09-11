#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
	int ret = 0x7fffffff;
	int answer = 0;
	
	for (int c = 1; c <= s.size(); c++) {
		int idx = 0;
		string copyS[1001];
		answer = 0;
		for (int i = 0; i < s.size();) {
			int C = c;
			while (C--) {
				if (i == (s.size()))break;
				copyS[idx].push_back(s[i++]);
			}
			idx++;
		}
		for (int i = 0; i < idx;) {
			int cnt = 1;
			int ci = 0;
			for (int j = i + 1; j < idx; j++) {
				if (copyS[i] == copyS[j]) {//압축 가능한경우
					cnt++;
				}
				else {
					if (cnt != 1) {//개수 포함 저장
						answer+=to_string(cnt).size();
						answer += copyS[i].size();
					}
					else if (cnt == 1) {//1은 제외 하고 저장
					 answer += copyS[i].size();
					}
					i = j;
					if (i == idx - 1) {
						answer += copyS[i].size();
						i++;
					}
					break;
				}
				ci = j;
			 }
			if (ci == idx - 1) {
				i = idx;
				if (cnt != 1) {//개수 포함 저장
					answer += to_string(cnt).size();
					answer += copyS[i-1].size();
				}
				else if (cnt == 1) {//1은 제외 하고 저장
					answer += copyS[i-1].size();
				}
			}
		}
		
		ret = ret > answer ? answer : ret;
	}
	return ret;
}
int main(void) {
	cout << solution("aaaaaaaaaa");
	return 0;
}