#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int main(void) {
	//1 1
	//2 2
	//3 3 
	//4 4
	//Ȧ���϶� 1����
	//©���϶� �� ������
	//14�϶�
	//13 1
	//11 2
	//8 3
	//4 4
// �ϴ� ���� ���� �Ϳ��� ����ؼ� �����ϱ�
	long long int X;
	cin >> X;
	int flag = 0;
	if (X == 1) {
		flag = 1;
	}

	int i = 1;//+1 ���ؼ� ����ؾ��ϴ� ����
	for (i = 1; i <= 100000; i++) {
		X -= i;
		if (X <=0) {//�ϴ� �ִ��� ��ó�� ����
			X += i;
			break;
		}
	}
	if (i % 2 == 0) {//¦��

		//���ڰ� i
		int j = 1;
		for (; j < X; j++) {
			i--;
		}
		cout << j << '/' <<i << '\n';

	}
	else if(i%2==1) {//Ȧ��

		//�и� i
		int j = 1;
		for (; j <X; j++) {
			i--;
		}
		cout << i << '/' << j << '\n';
}
	return 0;
}