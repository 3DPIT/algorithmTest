#include <string>
#include <vector>
#include <map>
#include<iostream>
using namespace std;
map<string, int>m;
vector<int> solution(vector<string> gems) {
	vector<int> answer;
	int cnt = 1;
	for (int i = 0; i < gems.size(); i++) {
		if (m[gems[i]] == 0) {
			m[gems[i]] = cnt++;
		}
	}
	int chk_cnt = 0;
	int mind = 0x7fffffff;
	cnt--;
	int y, x;
	int S = 0, E = 0;
	while (S != gems.size() && E != gems.size()) {
		int chk[100000] = { 0 };
		int cnt1 = 0;
		for (int i = S; i <= E; i++) {
			if (chk[m[gems[i]]] == 0) {
				chk[m[gems[i]]] = 1;
				cnt1++;
			}
		}
		if (E == gems.size()) {
			E = S;
			S++; E++;
		}
		if (cnt1 < cnt)E++;
		else if (cnt1 > cnt)S++;
		else if (cnt1 == cnt) {
			int d = E - S + 1;
			if (mind > d) {
				mind = d;
				y = S;
				x = E;
			}
			S++;
			//E = S;
		}

	}

	answer.push_back(y + 1);
	answer.push_back(x + 1);
	return answer;
}
int main(void) {
	vector<int>a= solution({ "DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA" });
	//for (int i = 0; i < a.size(); i++) {
	//	cout << a[i];
	//}
	//cout << endl;
	//a.clear();
	//vector<int>a = solution({ "AA", "AB", "AC", "AA", "AC" });
	//for (int i = 0; i < a.size(); i++) {
	//	cout << a[i];
	//}
	//cout << endl;
	//a.clear();

	//vector<int>a = solution({ "XYZ", "XYZ", "XYZ" });
	//for (int i = 0; i < a.size(); i++) {
	//	cout << a[i];
	//}
	//cout << endl;
	//a.clear();

	//vector<int>a = solution({ "ZZZ", "YYY", "NNNN", "YYY", "BBB" });
	for (int i = 0; i < a.size(); i++) {
		cout << a[i];
	}
	cout << endl;
	a.clear();

	return 0;

}
