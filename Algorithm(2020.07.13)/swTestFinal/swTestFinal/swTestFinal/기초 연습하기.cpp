#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
map <string, int>res = {
{"black",0},
{"brown",1},
{"red",2},
{"orange",3},
{"yellow",4},
{"green",5},
{"blue",6},
{"violet",7},
{"grey",8},
{"white",9},
};
int main(void) {
	string color1, color2, color3;
	cin >> color1 >> color2 >> color3; //���� ����
	long long int ans = (res[color1] * 10) + res[color2]; //�̸� ���
	for (int i = 0; i < res[color3]; i++) { //10�� ������ ����ϱ�
		ans *= 10;
	}
	cout << ans;// �������
	return 0;
}