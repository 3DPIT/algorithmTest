#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MS 101
#define AS 9
int ret;
int M, A;
int user1Y=1, user1X=1, user2Y=10, user2X=10;
typedef struct Data {
	int y, x,C,P;
};
int userDir[2][MS];
Data AP[AS];
int dy[] = { 0,-1,0,1,0 };
int dx[] = { 0,0,1,0,-1 };
void chargeChk() {
	vector<int>aUser;
	vector<int>bUser;
	for (int i = 0; i < A; i++) {//A의 접속
		int d = abs(user1Y - AP[i].y) + abs(user1X - AP[i].x);
		if (d <= AP[i].C) {//충전 영역에 있으면
			aUser.push_back(1);
		}
		else {
			aUser.push_back(0);
		}
	}
	for (int i = 0; i < A; i++) {//B의 접속
		int d = abs(user2Y - AP[i].y) + abs(user2X - AP[i].x);
		if (d <= AP[i].C) {//충전 영역에 있으면
			bUser.push_back(1);
		}
		else {
			bUser.push_back(0);
		}
	}
	int sum = 0x80000000;
	for (int i = 0; i < aUser.size(); i++) {
		for (int j = 0; j < bUser.size(); j++) {
			int num = 0;
			if (i!=j&&aUser[i] == 1 && bUser[j] == 1) {
			num+=(AP[i].P)+(AP[j].P);
			}
			if (i == j && aUser[i] == 1 && bUser[j] == 1) {
				num += (AP[i].P)/2;
			}
			if(aUser[i] == 1 && bUser[j] == 0) {
			num+=(sum,AP[i].P);
			}
			 if (aUser[i] == 0 && bUser[j] == 1) {
			num+=(sum, AP[j].P);
			}
			 sum = max(sum, num);
		}
	}
	if (sum != 0x80000000) {
		ret += sum;
	}
}
void move() {
	for (int i = 0; i <M; i++) {
		user1Y += dy[userDir[0][i]]; user1X += dx[userDir[0][i]];
		user2Y += dy[userDir[1][i]]; user2X += dx[userDir[1][i]];
		chargeChk();
	}
}
void playCharge() {
	chargeChk();//처음위치에서도 충전가능한 경우 있어서 먼저 선언
	move();
}
void init() {
	ret = 0;
	user1Y = 1; user1X = 1; user2Y = 10; user2X = 10;
	cin >> M >> A;
	for (int userIdx = 0; userIdx < 2; userIdx++) {
		for (int i = 0; i < M; i++) {
			cin >> userDir[userIdx][i];
		}
	}
	for (int aIdx = 0; aIdx < A; aIdx++) {
		cin >> AP[aIdx].x >> AP[aIdx].y >> AP[aIdx].C >> AP[aIdx].P;
	}
	playCharge();
}
int main(void)
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		cout << "#" << tc << " " << ret << endl;
	}
	return 0;
}