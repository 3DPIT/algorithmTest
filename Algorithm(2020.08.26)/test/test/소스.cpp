#include <iostream>
#include <vector>
#include <map>
using namespace std;
vector<int> solution(vector<vector<int> > v) {
	vector<int> ans;
	vector<int>a;
	map<long long int, int>chk;
	for (int i = 0; i < v.size(); i++) {
				chk[v[i][0]]++;
	}
	for (auto it = chk.begin(); it != chk.end(); it++) {
		if (chk[it->first] == 1)ans.push_back(it->first);
	}
	chk.clear();
	for (int i = 0; i < v.size(); i++) {
		chk[v[i][1]]++;
	}
	for (auto it = chk.begin(); it != chk.end(); it++) {
		if (chk[it->first] == 1)ans.push_back(it->first);
	}
	return ans;
}
int main(void) {
	solution({ {1, 4
}, { 3, 4
}, { 3, 10
} });
	return 0;
 }