#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
vector<int>v;
int map[11];
struct Data {
	int num, plus;
};
vector<Data>H[5];
void copy(vector<Data>CA[5], vector<Data>A[5]) {
	for (int i = 1; i <= 4; i++) {
		CA[i] = A[i];
	}
}
void print(int idx, int num) {
	for (int i = 1; i <= map[num]; i++) {
		if (H[idx].front().num == 40)continue;
		H[idx].front().num += H[i].front().plus;
		//if (H[idx].front().num == 10 && i < map[num]) {//넘어가는 경우{
		//   if (H[idx].front().plus == -3) H[idx].front().plus = 2;

		//}
		if (H[idx].front().num == 19 && i < map[num]) {//넘어가는 경우{
			if (H[idx].front().plus == 3) H[idx].front().plus = 6;
			/////
		}
		if (H[idx].front().num == 24 && i < map[num]) {//넘어가는 경우
			if (H[idx].front().plus == 2) H[idx].front().plus = 1;

		}
		if (H[idx].front().num == 25 && i < map[num]) {//넘어가는 경우
			if (H[idx].front().plus == 3) H[idx].front().plus = 1;
			else if (H[idx].front().plus == 2)H[idx].front().plus = 5;
			else if (H[idx].front().plus == 6)H[idx].front().plus = 5;
			else if (H[idx].front().plus == 1)H[idx].front().plus = 5;
			else if (H[idx].front().plus == -1)H[idx].front().plus = 5;
		}
		if (H[idx].front().num == 28 && i < map[num]) {//넘어가는 경우
			if (H[idx].front().plus == 1) H[idx].front().plus = 2;
		}//
	}
	if (H[idx].front().num == 10) H[idx].front().plus = 3;
	if (H[idx].front().num == 20) H[idx].front().plus = 2;
	if (H[idx].front().num == 25) H[idx].front().plus = 5;
	if (H[idx].front().num == 30) H[idx].front().plus = 2;
	if (H[idx].front().num == 40) H[idx].front().plus = 0;

}
int max = 0x80000000;
void dfs(int idx) {
	if (v.size() == 10) {
		for (int i = 1; i <= 10; i++) {
			print(v[i - 1], i);
		}

		int sum = 0;
		for (int i = 1; i <= 4; i++) {
			sum += H[i].front().num;
		}
		if (max < sum)max = sum;
		return;
	}
	vector<Data>CH[5];
	for (int i = 1; i <= 4; i++) {//
		copy(CH, H);
		v.push_back(i);
		dfs(i);
		v.pop_back();
		copy(H, CH);
	}
}
void init() {
	for (int i = 1; i <= 10; i++) {
		scanf("%d", &map[i]);
	}
	for (int i = 1; i <= 4; i++) {
		H[i].push_back({ 0, 2 });
	}
}
int main(void) {
	init();
	dfs(0);
	cout << max;
	return 0;
}