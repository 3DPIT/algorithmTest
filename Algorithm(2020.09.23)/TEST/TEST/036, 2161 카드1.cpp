#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int main(void) {
	int N;
	scanf("%d", &N);
	vector<int>card;
	vector<int>trash;
	for (int i = 1; i <= N; i++) {
		card.push_back({ i });
	}
	while (1) {
		if (card.size() == 1) {//ī�尡 ���� ������ ����� �Ѵ�.
			for (int i = 0; i < trash.size(); i++) {
				cout << trash[i] << " ";
			}
			cout << card[0] << endl;
			break;//����ϰ� ���� ��Ű��
		}
		trash.push_back(card[0]);//���� ī��� ������.
		card.erase(card.begin());
		int num = card.front();
		card.push_back(num);//���� ī�带 �ڷ� �ִ´�.
		card.erase(card.begin());


	}
	return 0;
}