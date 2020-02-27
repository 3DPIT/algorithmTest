#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
int n;
int arr[9];
int retIdx;
struct Screat {
	Screat() {
		int t;
		while (cin >> t) {
			init();
			for (int i = 0; i < 8; i++) {
				scanf("%d",&arr[i]);
			}
				arrCircle();
			printf("#%d ", t);
			int cnt = 0;
			for (int i = 0; i < 8; i++) {
				printf("%d ", arr[retIdx++]);
				if (retIdx == 8)retIdx = 0;
			}
			printf("\n");
		}
	}
	void init() {
		memset(arr, 0, sizeof(arr));
		retIdx = 0;
	}
	void arrCircle() {
		int num = 1;
		int flag = 0;
		while (1) {
			for (int i = 0; i < 8; i++) {
				arr[i] -= num;
				if (arr[i] <= 0) {
					arr[i] = 0;
					retIdx = i;
					retIdx++;
					if (retIdx == 8)retIdx = 0;
					return;
				}
				num++;
				if (num == 6)num = 1;
			}
		}
	}
}Screat;
int main(void) {
	return 0;
}