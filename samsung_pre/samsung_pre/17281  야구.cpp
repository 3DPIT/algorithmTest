#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define S 51
#define Ss 10
int N;
int Max = 0x80000000;
int Data[S][Ss];
int num[Ss];
int v[Ss];
struct BaseBall {
	BaseBall() {
		//init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 1; j <= 9; j++) {
				scanf("%d", &Data[i][j]);
			}
		}
		playBall();
		printf("%d\n", Max);
	}

	void playBall() {
		v[0] = 0;
		dfs(1,0, 0);
	}
	void simul()
	{
		int round = 0;
		int pan[4];
		int score = 0;
		int head = 1;
		while (round != N)
		{
			int out = 0;
			memset(pan, 0, sizeof(pan));//�ǻ���
			while (1)
			{
				if (Data[round][v[head]] == 0)out++;
				else //������ �´�.
				{
					//for���� ���� 1�ξֵ� ó�� 
					int cp[5];
					memset(cp, 0, sizeof(cp));
					cp[Data[round][v[head]]] = 1; //ģ��.
					for (int i = 1; i <= 3; i++)
					{
						if (pan[i] == 1)
						{
							pan[i] = 0;
							int sc = i + Data[round][v[head]]; //����
							if (sc >= 4)sc = 4;
							cp[sc]++;
						}
					}
					for (int i = 1; i <= 3; i++)pan[i] = cp[i];


					score += cp[4];//������ȹ��
					cp[4] = 0;
				}
				head++;
				if (head == 10)head = 1;
				if (out == 3)break;//3�ƿ�ü����
			}
			round++;
		}
		Max= Max< score ? score : Max;
	}
	void play() {
		int out = 0;
		int round = 0;
		int currentHuman = 1;
		int anta = 0;
		int sum = 0;
		int s[4] = { 0, };
		while (round != N) {//N ���� ��ŭ �ؾ��ϴϱ�
			int idx = v[currentHuman];
			if (Data[round][idx] == 0) {//�ƿ�
				out++;
				if (out == 3) {
					out = 0;
					memset(s, 0, sizeof(s));
					round++;
				}
			}
			else {//1��Ÿ
				int base[5] = { 0, };
				base[Data[round][idx]] = 1;
				for (int i = 1; i <= 3; i++) {
					if (s[i] == 1) {
						s[i] = 0; {
							int score = i + Data[round][idx];
							if (score > 3)score = 4;
							base[score]++;
						}
					}
				}
				for (int i = 1; i <= 3; i++) {
					s[i] = base[i];
				}
				sum += base[4];
				base[4] = 0;
			}

				}
		if (Max < sum)Max = sum;
	}
	int idx1 = 1;
	void dfs(int idx,int d, int cnt) {
		if (cnt == 8) {
			v[4] = 1;
			play();
			return;
		}
		for (int i = 2; i <= 9; i++) {
			if (num[i] == 0) {
				if (idx == 4)idx++;
				num[i] = 1;
				v[idx] = i;
				dfs(idx+1,i, cnt + 1);
				v[idx] = 0;
				num[i] = 0;

			}
		}
	}
}BaseBall;


int main(void) {
	return 0;
}