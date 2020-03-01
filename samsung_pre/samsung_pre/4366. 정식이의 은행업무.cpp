#include<stdio.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
int ret;
string n[4];
vector<int>v2;
vector<int>v3;
struct Bank {
	Bank() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			cin >> n[2] >> n[3];

			unsigned long long int tree = numToTen(3);
			twoChange();
			treeChange();
			sort(v2.begin(), v2.end());
			sort(v3.begin(), v3.end());
			for (int i = 0; i < v2.size(); i++) {
				for (int j = 0; j < v3.size(); j++) {
					if (v2[i] == v3[j]) {
						ret = v2[i];
						break;
					}
					if (ret != 0)break;
				}
			}
			printf("#%d %d\n", t, ret);
		}
	}
	void init() {
		for (int i = 2; i <= 3; i++) {
			n[i].clear();
		}
		v2.clear();
		v3.clear();
		ret=0;
	}
	void twoChange() {
		for (int i = 0; i < n[2].size(); i++) {
			char num1 = n[2][i];
			if (n[2][i] == '1') {
				n[2][i] = '0';
				unsigned long long int two = numToTen(2);
				v2.push_back(two);
			}
			else {
				n[2][i] = '1';
				unsigned long long int two = numToTen(2);
				v2.push_back(two);
			}
			n[2][i] = num1;
		}
	}
	void treeChange() {
		for (int i = 0; i < n[3].size(); i++) {
			char num1 = n[3][i];
			if (n[3][i] == '1') {
				n[3][i] = '0';
				unsigned long long int tree = numToTen(3);
				v3.push_back(tree);
				n[3][i] = '2';
				tree = numToTen(3);
				v3.push_back(tree);
			}

			else if (n[3][i] == '2') {
				n[3][i] = '0';
				unsigned long long int tree = numToTen(3);
				v3.push_back(tree);
				n[3][i] = '1';
				tree = numToTen(3);
				v3.push_back(tree);
			}
			else if (n[3][i] == '0') {
				n[3][i] = '1';
				unsigned long long int tree = numToTen(3);
				v3.push_back(tree);
				n[3][i] = '2';
				tree = numToTen(3);
				v3.push_back(tree);
			}
			n[3][i] = num1;
		}
	}
	unsigned long long int numToTen(int num) {
		unsigned long long int ten = 0;
		int idx = 0;
		for (int i = n[num].size() - 1; i >= 0; i--) {
			unsigned long long int num1 = n[num][i] - '0';
			unsigned long long int pownum = pow(num, idx++);

			ten += num1 * pownum;
		}
		return ten;
	}

}Bank;
int main(void) {

	return 0;
}