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
	int N;// �ܾ� ���� �Է�	
	cin >> N;
	vector<string> s(N);//���ڿ� ������ ����
	for (int i = 0; i < N; i++) {
		cin >> s[i];
	}
	sort(s.begin(), s.end(),cmp);//����
	s.erase(unique(s.begin(), s.end()),s.end());
	for (int i = 0; i < s.size(); i++) {
	//	if(s[i]!=s[i+1])
			cout << s[i] <<'\n' ;//���
	}
	return 0;
}