#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
int main(void)
{
	vector<string> v[5];
	int maxIdx = 0x80000000;
	for (int i = 0; i < 5; i++) {
		string a;
		cin >> a;
		v[i].push_back(a);
		if (maxIdx <(int)a.size())maxIdx = (int)a.size();//�ִ� ���� �̾Ƴ��� (int) ĳ�����ؾ� �� 
	}

	for (int i = 0; i < maxIdx; i++) {
		for (int j = 0; j < 5; j++) {
			if ((int)v[j][0].size() <= i)continue; // ������ �Ѿ�� ��� �ѱ�
			cout << v[j][0][i];
		}
	}


	return 0;// ����

}