#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
using namespace std;
int chk[4];
int d[10];
int map[32] = {
	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
	13,16,19,22,24,28,27,26,25,30,35,0};
int cube[10];
struct data{
	int num,dir,s,nidx,bnum;
}horse[5];
int sum;
int max1 = 0x80000000;
int f = 0;
int sim() {
	f = 0;
	memset(horse, 0, sizeof(horse));
	for (int i = 1; i <= 4; i++) {
		horse[i].num = -1;
		horse[i].bnum = -1;
	}
	sum = 0;
	for (int i = 0; i < 10; i++) {
		int num = d[i];
		if (horse[num].nidx == -2)continue;
		for (int j = 0; j < cube[i]; j++) {//이동 횟수
			if (horse[num].num == 31)break;
			if (horse[num].nidx!=-2&&horse[num].nidx != 0) {
				horse[num].num = horse[num].nidx;
				horse[num].nidx = 0;
			}
			else
			horse[num].num++;
			if (horse[num].num == 22) {
				horse[num].nidx = 28;
			}
			if (horse[num].num == 24) {
				horse[num].nidx = 28;
			}
			if (horse[num].num == 30) {
				horse[num].nidx = 19;
			}
			if (horse[num].num == 19) {
				horse[num].nidx = 31;
			}
			if (horse[num].num == 31) {
				horse[num].nidx = -2;
				break;
			}
		}//j끝
		//cout <<num<< "num" << horse[num].num << endl;
		int flag = 0;
		for (int a = 1; a <= 4; a++) {
			if (num == a)continue;
			if (horse[num].num!=31&&horse[num].num != -1 && horse[num].num ==horse[a].num) {
				horse[num].num = horse[num].bnum;
				f = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			return -1;
			horse[num].nidx = -2;
			horse[num].s = 0;
		}
		if (flag==0&&horse[num].num == 19) {
			horse[num].s += 40;//점수 추가
			horse[num].nidx = -2;
		}
		else if (flag == 0&& horse[num].num != 19) {
			horse[num].bnum = horse[num].num;
			horse[num].s += map[horse[num].num];//점수 추가
		}
		if (horse[num].num == 4) {
			horse[num].nidx = 20;
		}
		else if (horse[num].num == 22) {
			horse[num].nidx = 28;
		}
		else if (horse[num].num == 24) {
			horse[num].nidx = 28;
		}
		else if (horse[num].num == 30) {
			horse[num].nidx = 19;
		}
		else if (horse[num].num == 9) {
			horse[num].nidx = 23;
		}
		else if (horse[num].num == 14) {
			horse[num].nidx = 25;
		}

	}
	for (int i = 1; i <= 4; i++) {
		sum += horse[i].s;
	}
	return sum;
}
void dfs(int idx, int d1) {
	if (idx == 10) {
		int a=sim();

		if (max1<a) {
			//cout << f << endl;
			//for (int i = 0; i < 10; i++) {
			//	cout << d[i] << " ";
			//}
			//cout << a;
			//cout << endl;
			max1 = a;
		}
		return;
	}
	for (int j = 1; j <= 4; j++) {
			d[idx] = j;
			dfs(idx+1, d1++);
			d[idx] = 0;
	}
}
void init() {
	for (int i = 1; i <= 4; i++) {
		horse[i].num = 0;
		horse[i].dir = 0;
	}
	for (int i = 0; i < 10; i++) {
		scanf("%d", &cube[i]);
	}
}
int main(void) {
	init();
	//for (int i = 0; i < 31; i++) {
	//	cout << i << " " << map[i] << endl;
	//}
	dfs(0, 0);
	cout << max1;
	return 0;
}