#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
int chk[201][201][201];//물통 중복 체크
int waterOutOfA[201];//A 가 빈경우 C의 물의양 저장 끝에서 출력할것
struct Data {
	int A, B, C;
};
int A, B, C;
int MaxA, MaxB, MaxC;
void zeroChk(int c) {
	waterOutOfA[c] = 1;
}
void waterFlow() {
	queue<Data>q;
	q.push({ 0,0,C });//초기 값
	zeroChk(q.front().C);//A가 제로일때 체크해서 C값 저장
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.A != 0 && (MaxB - c.B) > 0) {
			if (((MaxB - c.B) > c.A) && MaxB >= (MaxB - c.B) + c.A&&chk[0][c.B+c.A][c.C]==0) {
				chk[0][c.B + c.A][c.C] = 1;
				q.push({ 0,c.B + c.A,c.C });
			}
			if (((MaxB - c.B) > c.A) && MaxB < (MaxB - c.B) + c.A&& chk[c.A - (MaxB - c.B)][MaxB][c.C]==0) {
				chk[c.A - (MaxB - c.B)][MaxB][c.C] = 1;
				q.push({ c.A - (MaxB - c.B), MaxB, c.C });
			}
		}
		if (c.A != 0 && (MaxC - c.C) > 0) {
			if (((MaxC - c.C) > c.A) && MaxC >= (MaxC - c.C) + c.A&&chk[0][c.C + c.A][c.C] == 0) {
				chk[0][c.C + c.A][c.C] = 1;
				q.push({ 0,c.C + c.A,c.C });
			}
			if (((MaxC - c.C) > c.A) && MaxC < (MaxC - c.C) + c.A&&chk[c.A - (MaxC - c.C)][MaxB][c.C]==0) {
				chk[c.A - (MaxC - c.C)][MaxB][c.C] = 1;
				q.push({ c.A - (MaxC - c.C), MaxB, c.C });
			}
		}

		if (c.B != 0 && (MaxA - c.A) > 0) {//B
			if (((MaxA - c.A) > c.B) && MaxA >= (MaxA - c.A) + c.B&&chk[c.A + c.B][0][c.C]==0) {
				chk[c.A + c.B][0][c.C] = 1;
				q.push({ c.A+c.B,0,c.C});
			}
			if (((MaxA - c.A) > c.B) && MaxA < (MaxA - c.A) + c.B&&chk[MaxA][c.B - (MaxA - c.A)][c.C]==0) {
				chk[MaxA][c.B - (MaxA - c.A)][c.C] = 1;
				q.push({ MaxA,c.B - (MaxA - c.A), c.C });
			}
		}
		if (c.B != 0 && (MaxC - c.C) > 0) {
			if (((MaxC - c.C) > c.B) && MaxC >= (MaxC - c.C) + c.B&&chk[c.A][0][c.B + c.C]==0) {
				chk[c.A][0][c.B + c.C] = 1;
				q.push({c.A,0,c.B+c.C});
			}
			if (((MaxC - c.C) > c.B) && MaxC < (MaxC - c.C) + c.B&&chk[c.A][c.B - (MaxC - c.C)][MaxC] == 0){
				chk[c.A][c.B - (MaxC - c.C)][MaxC] = 1; 
				q.push({ c.A,c.B - (MaxC - c.C), MaxC});
			}
		}


		if (c.C != 0 && (MaxA - c.A) > 0) {//C
			if (((MaxA - c.A) > c.C) && MaxA >= (MaxA - c.A) + c.C&&chk[c.A + c.C][c.B][0]==0) {
				chk[c.A + c.C][c.B][0] = 1;
				q.push({ c.A + c.C,c.B,0 });
			}
			if (((MaxA - c.A) > c.C) && MaxA < (MaxA - c.A) + c.C&&chk[MaxA][c.C - (MaxA - c.A)][c.C]==0) {
				chk[MaxA][c.C - (MaxA - c.A)][c.C] = 1;
				q.push({ MaxA,c.C - (MaxA - c.A), c.C });
			}
		}
		if (c.C != 0 && (MaxB - c.B) > 0) {
			if (((MaxB - c.B) > c.C) && MaxB >= (MaxB - c.B) + c.C&&chk[c.A][c.B + c.C][0]==0) {
				chk[c.A][c.B + c.C][0] = 1;
				q.push({ c.A,c.B + c.C,0 });
			}
			if (((MaxB - c.B) > c.C) && MaxB < (MaxB - c.B) + c.C&&chk[c.A][MaxB][c.C - (MaxB - c.B)]==0) {
				chk[c.A][MaxB][c.C - (MaxB - c.B)] = 1;
				q.push({ c.A,MaxB,c.C-(MaxB-c.B)});
			}
		}

	}
}
void solve() {
	for (int i = 1; i <= 200; i++) {
		if (waterOutOfA[i] == 1) {
			cout << i << " ";
		}
	}
	cout << endl;
}
void init() {
	cin >> MaxA >> MaxB >> MaxC;
	C = MaxC;// C 비커는 가득 !!
	waterFlow();
	solve();
	
}
int main(void) {
	init();
	return 0;
}