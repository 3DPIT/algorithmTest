#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>

using namespace std;
map<int, int>m;
vector<int>num;
int main(void) {
	int cnt = 0;
	int N = 0;
	printf("�Է��� ���� ���� �Է��ϼ��� ���Ḧ ���ҽ� -1 �Է�: \n");
	while(1){
		int a;
		scanf("%d", &a);
		if (a == -1)break;
		num.push_back(a);
	}
	int M = 0;
	printf("�� ��Ʈ ���� �Է��ϼ��� : ");
	cin >> M;
	while (M--) {
		cnt = 0;
		while (1) {
			int a = (rand() % num.size()-1) + 1;
			if (m[a] == 0) {
				m[a] = 1;
				cnt++;
			}
			if (cnt == 6)break;
		}
		vector<int>b;
		int cc = 0;
		for (auto it = m.begin(); it != m.end(); it++) {
			if (num[it->first] / 10 == 0)cc++;
			b.push_back(num[it->first]);
			if (cc == 1)break;	
		}
		if (cc == 1) {
			M++;
			b.clear();
		}
		else {
			for (int i = 0; i < b.size(); i++) {
				cout << b[i] << " ";
			}
			cout << endl;
		}
		m.clear();
	}

	return 0;
}