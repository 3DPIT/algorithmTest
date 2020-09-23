#include <string>
#include <iostream>
#include <vector>
#include<algorithm>
#include<string.h>
using namespace std;
int D[26] = { 0, };//���� �̱� ���� �迭
int alph[26] = { 0, };//���ĺ� ����
int Max = 0x80000000;//�ִ� ��Ʈ �޴� ����°� ����
string s;
void dfs(int idx, int d, int N, int maxidx, vector<string> orders, vector<string> v[26]) {
	if (maxidx < idx)return;
	if (d == N) {
		int cnt = 0;
		int ret = 0;
		for (int i = 0; i < orders.size(); i++) {
			cnt = 0;
			for (int j = 0; j < s.size(); j++) {
				if (orders[i].size() < s.size())continue;
				if (std::find(orders[i].begin(), orders[i].end(), s[j]) != orders[i].end()) {
					cnt++;
				}		
				if (cnt == N)break;
			}
			if (cnt == N)ret++;
		}
		if (ret < 2)return;
		if (ret >= 2 && Max <= ret) {
			Max = ret;
			v[Max].push_back(s);//��� �� ����
		}
		return;
		//���� �̰� 2�� �̻��̵Ǵ� �� Ȯ��
	}
	D[idx] = 1;
	s += alph[idx] + 'A';
	dfs(idx + 1, d + 1, N, maxidx, orders, v);//�̴� ���
	D[idx] = 0;
	s.pop_back();
	dfs(idx + 1, d, N, maxidx, orders, v);//�Ȼ̴� ���

}
vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;
	int idx = 0;
	int alphabet[26] = { 0, };
	for (int i = 0; i < orders.size(); i++) {
		for (int j = 0; j < orders[i].size(); j++) {
			if (alphabet[orders[i][j]-'A'] != 0)continue;
			alphabet[orders[i][j] - 'A'] = 1;
			alph[idx++] = orders[i][j] - 'A';
		}
	}
	sort(alph + 0, alph + idx);
	for (int i = 0; i < course.size(); i++) {
		vector<string>v[26];//����� �����س���
		int cnt = 0;
		for (int j = 0; j < orders.size(); j++) {
			if (course[i] <= orders[j].size())cnt++;
		}
		if (cnt < 2)break;
		dfs(0, 0, course[i], idx, orders, v);//�ε�������, ���� ��������, �迭�Ѱܳ���,�ִ�̴¼�,�ִ� �ε�����
		if (Max == 0x80000000)break;
		for (int i = 0; i < v[Max].size(); i++) {
			answer.push_back(v[Max][i]);
		}
		Max = 0x80000000;

	}
	sort(answer.begin(), answer.end());
	return answer;

}
int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	solution({ "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" }, { 2,3,4 });
	return 0;
}
