#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
vector<int>v;
int map[11];

struct Data {
	int num, plus,dir;

};
Data Hchk[41];
vector<Data>H[5];
void copy(vector<Data>CA[5], vector<Data>A[5]) {
	for (int i = 1; i <= 4; i++) {
		CA[i] = A[i];
	}
}
int ret;

void print(int idx, int num1) {
	
	for (int i = 1; i <= map[num1]; i++) {
		if (H[idx].front().num >= 40)continue;
		H[idx].front().num += H[idx].front().plus;

		if (H[idx].front().num == 19 && i <= map[num1]) {//넘어가는 경우{
			if (H[idx].front().plus == 3) H[idx].front().plus = 6;
			/////
		}
		if (H[idx].front().num == 24 && i <= map[num1]&& H[idx].front().dir==1) {//넘어가는 경우
			if (H[idx].front().plus == 2) H[idx].front().plus = 1;

		}
		if (H[idx].front().num == 25 && i <= map[num1]) {//넘어가는 경우
		 if (H[idx].front().plus == 6)H[idx].front().plus = 5;
			else if (H[idx].front().plus == 1)H[idx].front().plus = 5;
			else if (H[idx].front().plus == -1)H[idx].front().plus = 5;
		}
	}
	if (Hchk[H[idx].front().num].num == H[idx].front().num&&Hchk[H[idx].front().num].plus == H[idx].front().plus) {
		//cout << 111 << endl;
		return;
	}

	if (H[idx].front().num == 10) H[idx].front().plus = 3;
	if (H[idx].front().num == 20) {
		H[idx].front().plus = 2;
		H[idx].front().dir = 1;
	}
	if (H[idx].front().num == 25) H[idx].front().plus = 5;
 	if (H[idx].front().num == 30&&H[idx].front().plus==5) H[idx].front().plus = 5;
	if (H[idx].front().num == 30 && H[idx].front().plus == 2) H[idx].front().plus =-2;
	if (H[idx].front().num == 40) H[idx].front().plus = 0;
		Hchk[H[idx].front().num].num = H[idx].front().num;
		Hchk[H[idx].front().num].plus = H[idx].front().plus;

}
int max = 0x80000000;
void dfs(int idx) {
	if (v.size() == 10) {
		/*if (ret == 102) {
			for (int i = 0; i < v.size(); i++)
				cout << v[i];
			cout << endl;
		}
*/
		//for (int i = 1; i <= 4; i++) {
		//	sum += H[i].front().num;
		//}
		//if (sum == 140) {
		//	for (int i = 0; i < v.size(); i++) {
		//		//print(v[i], i + 1);
		//		//cout << v[i];
		//	}
		//	//cout << endl;
		//}
		if (max < ret)max =ret;

 		return;
	}
	vector<Data>CH[5];
	for (int i = 1; i <= 4; i++) {//
		copy(CH, H);
		v.push_back(i);
		print(i, v.size());
		if (H[i].front().num == 40&&H[i].front().plus==0) {
			H[i].front().plus == 1;
			ret += H[i].front().num;
		}
		else ret += H[i].front().num;
		dfs(i);
		ret -= H[i].front().num;
		v.pop_back();
		copy(H, CH);
	}
}
void init() {
	for (int i = 1; i <= 10; i++) {
		scanf("%d", &map[i]);
	}
	for (int i = 1; i <= 4; i++) {
		H[i].push_back({ 0, 2,0 });
	}
}
int main(void) {
	init();
	dfs(0);
	cout << max;
	return 0;
}