#include<algorithm>
#include<vector>
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
bool cmp(const string &u, const string &v) {
	if (u.size() == v.size())return u < v;
	else return u.size() < v.size();
}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;// 단어 개수 입력	
	cin >> N;
	vector<string> s(N);//문자열 저장할 백터
	for (int i = 0; i < N; i++) {
		cin >> s[i];
	}
	sort(s.begin(), s.end(),cmp);//정렬
	s.erase(unique(s.begin(), s.end()),s.end());
	for (int i = 0; i < s.size(); i++) {
	//	if(s[i]!=s[i+1])
			cout << s[i] <<'\n' ;//출력
	}
	return 0;
}