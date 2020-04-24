#include<stdio.h>
#include<string.h>
using namespace std;
#define KS 101
char gear[5][10];
int gearDir[5];
struct gearStart {
	gearStart() {
		for (int i = 1; i <= 4; i++)
			scanf("%s", gear[i]);
		int k;
		scanf("%d", &k);
		for (int ki = 0; ki < k; ki++) {
			gearR();
		}
		int sum=0;
		for (int idx = 1,two=1; idx <= 4; idx++,two*=2) {
			if (gear[idx][0] == '1') {
				sum += two;
			}
		}
		printf("%d\n",sum);
	}
	void gearR() {
		int num, dir;
		memset(gearDir, 0, sizeof(gearDir));
		scanf("%d %d", &num, &dir);
		gearDir[num] = dir;
		for (int i = num; i >= 2; i--) {//<<<<---
			if (gear[i][6] != gear[i - 1][2]) {
				gearDir[i - 1] = gearDir[i] * -1;
			}
		}

		for (int i = num; i <= 3; i++) {//--->>>>
			if (gear[i][2] != gear[i + 1][6]) {
				gearDir[i + 1] = gearDir[i] * -1;
			}
		}
		for (int i = 1; i <= 4; i++) {
			if (gearDir[i] == -1) {
				reclockRotation(i);
			}
			else if (gearDir[i] == 1) {
			clockRotation(i);
			}
		}
	}
	void clockRotation(int idx) {
		char num;
		num = gear[idx][7];
		for (int i = 6; i >= 0; i--) {
			gear[idx][i+1] = gear[idx][i];
		}
		gear[idx][0]= num;
	}
	void reclockRotation(int idx) {
		char num;
		num = gear[idx][0];
		for (int i = 1; i <= 7; i++) {
			gear[idx][i-1] = gear[idx][i];
		}
		gear[idx][7] = num;
	 }
}gearRa;
int main(void) {

	return 0;
}