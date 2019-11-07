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
		if (maxIdx <(int)a.size())maxIdx = (int)a.size();//최대 길이 뽑아내기 (int) 캐스팅해야 들어감 
	}

	for (int i = 0; i < maxIdx; i++) {
		for (int j = 0; j < 5; j++) {
			if ((int)v[j][0].size() <= i)continue; // 범위를 넘어서는 경우 넘김
			cout << v[j][0][i];
		}
	}


	return 0;// 리턴

}