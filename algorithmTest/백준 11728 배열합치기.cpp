#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>	
using namespace std;
int N, M;
vector<int>v;
void init() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		int a;
		scanf("%d", &a);
		v.push_back(a);
	}
	for (int j = 0; j < M; j++) {
		int a;
		scanf("%d", &a);
		v.push_back(a);
	}
	sort(v.begin(), v.end());//���� ����
	for (int i = 0; i < v.size(); i++) {
		printf("%d ", v[i]);// ���� ���

	}
	cout << endl;
}
int main(void)
{
	init();//�ʱ�ȭ �Է� ���ڸ��� ���
	return 0;
}