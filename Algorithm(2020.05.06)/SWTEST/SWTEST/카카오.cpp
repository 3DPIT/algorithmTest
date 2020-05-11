#include <string>
#include <vector>
#include <iostream>
using namespace std;
int map[5][3];
struct Data {
	int y, x;
};
Data num[10];

void init() {
	int num1= 1;
	for (int i = 0; i <= 4; i++) {
		for (int j = 0; j <= 2; j++) {
			num[num1].y = i;
			num[num1++].x = j;
		}
	}
	num[0].y = 3; num[0].x = 1;
}

void print(string name, int idx) {
	if (idx == 0) {
		for (int i = 0; i <=9; i++) {
			cout << num[i].y << num[i].x << endl;
		}
	}
}
bool Lsafe(int y, int x) {
	return 0 <= y && y <= 3 && 0 <= x && x <= 1;
}
bool Rsafe(int y, int x) {
	return 0 <= y && y <= 3 && 1 <= x && x <= 2;
}
string solution(vector<int> numbers, string hand) {
	string answer = "";
	init();
	//print("¸Ê",0);
	int ly=3, lx=0, ry=3, rx=2;
	for (int i = 0; i < numbers.size(); i++) {
		int Lflag = Lsafe(num[numbers[i]].y, num[numbers[i]].x);
		int Rflag = Rsafe(num[numbers[i]].y, num[numbers[i]].x);
		if (Lflag == 1 && Rflag == 1) {
			int Ld = abs(ly - num[numbers[i]].y) + abs(lx - num[numbers[i]].x);
			int Rd = abs(ry - num[numbers[i]].y) + abs(rx - num[numbers[i]].x);
			if (Ld == Rd) {
				if (hand == "right") {
					ry = num[numbers[i]].y;
					rx = num[numbers[i]].x;
					answer.push_back('R');
				}
				else {
					ly = num[numbers[i]].y;
					lx = num[numbers[i]].x;
					answer.push_back('L');

				}
			}
			else if (Ld > Rd) {
				ry = num[numbers[i]].y;
				rx = num[numbers[i]].x;
				answer.push_back('R');
			}
			else if (Ld < Rd) {
				ly = num[numbers[i]].y;
				lx = num[numbers[i]].x;
				answer.push_back('L');
			}
		}
		else if (Lflag == 1 && Rflag == 0) {
			ly = num[numbers[i]].y;
			lx = num[numbers[i]].x;
			answer.push_back('L');
		}
		else if (Lflag == 0 && Rflag == 1) {
			ry = num[numbers[i]].y;
			rx = num[numbers[i]].x;
			answer.push_back('R');
		}

	}
	return answer;
}
int main(void) {
	cout<<solution({ 1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5 }, "right")<<endl;
	cout<<solution({ 7, 0, 8, 2, 8, 3, 1, 5, 7, 6, 2 }, "left")<<endl;
	cout<<solution({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }, ",right")<<endl;
	return 0;
}