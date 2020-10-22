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
		if (card.size() == 1) {//카드가 한장 남으면 출력을 한다.
			for (int i = 0; i < trash.size(); i++) {
				cout << trash[i] << " ";
			}
			cout << card[0] << endl;
			break;//출력하고 종료 시키기
		}
		trash.push_back(card[0]);//위에 카드는 버린다.
		card.erase(card.begin());
		int num = card.front();
		card.push_back(num);//위에 카드를 뒤로 넣는다.
		card.erase(card.begin());


	}
	return 0;
}