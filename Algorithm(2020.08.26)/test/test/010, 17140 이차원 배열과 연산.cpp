#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define INPUT_SIZE 101
int input[INPUT_SIZE][INPUT_SIZE];//�Է����� �־����� �迭
int R, C;//������ �����ϱ����� �Ǻ��� ���� ����
int r, c, k;// �Է����� �־����� �� ,��, �࿭�� ��
int ret;//����� ����
struct Data {
	int num, cnt;
};
bool cmp(Data a, Data b) {// ���� ����
	if (a.cnt == b.cnt)return a.num < b.num;//����� ������ ��ȣ�������� ��������
	else return a.cnt < b.cnt;//�׷��� �ƴϸ� ���� Ƚ���� ��������
}
void init() {
	memset(input, 0, sizeof(input));
	R = C = 3;
	ret = 0;
	scanf("%d %d %d", &r, &c, &k);
	for(int i=0;i<R;i++){
		for (int j = 0; j < C; j++) {
			scanf("%d", &input[i][j]);//�Է�
		}
	}
}
void rMath() {//R����
	int MaxC = 0x80000000;
	for (int i = 0; i < R; i++) {
		Data D[INPUT_SIZE] = { 0, };//������ ������ ���� �迭
		for (int j = 0; j < C; j++) {
			if (input[i][j] != 0) {//0�� ����
				D[input[i][j]].num = input[i][j]; D[input[i][j]].cnt++;//������ ����
				input[i][j] = 0;
			}
		}
		sort(D+0, D + 101, cmp);
		vector<int>a;//���� �Ϸ� �� ������ ����
		for (int i = 1; i <= 100; i++) {
			if (D[i].num != 0) {
				a.push_back(D[i].num);
				a.push_back(D[i].cnt);
			}
		}
		int size = a.size();
		MaxC = MaxC < size ? size : MaxC;// C�� �ִ밪 ã��
		for (int j = 0; j < a.size(); j++) {//���� ��� ����
			input[i][j] = a[j];
		}
	}
	C = MaxC;
	if (C > 100)C = 100;
}
void cMath() {//C����
	int MaxR = 0x80000000;//R�� �ִ밪 �Ǻ�����
	for (int j = 0; j < C; j++) {
		Data D[INPUT_SIZE] = { 0, };//���� ������� 
		for (int i = 0; i < R; i++) {
			if (input[i][j] != 0) {
				D[input[i][j]].num = input[i][j]; D[input[i][j]].cnt++;//������ ����
				input[i][j] = 0;//�ʱ�ȭ
			}
		}
			sort(D + 0, D + 101, cmp);//����
			vector<int>a;//���� ��� ����
			for (int i = 1; i <= 100; i++) {
				if (D[i].num != 0) {
					a.push_back(D[i].num); a.push_back(D[i].cnt);//���� ��� ����
				}
			}
			int size = a.size();
			MaxR = MaxR < size ? size : MaxR;//�ִ� R������
			for (int i = 0; i < a.size(); i++) {
				input[i][j] = a[i];
			}
		
	}

	R = MaxR;
	if (R > 100)R = 100;
}
void play() {//���� ����
	while (1) {
		if (ret > 100)break;
		if (input[r-1][c-1] == k)break;// ���� ����
		if (R >= C) {
			rMath();//R����
		}
		else if (R<C) {
			cMath();//C����
		}

		ret++;
	}
}
int main(void) {
	int testCase = 1;
	scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();//�ʱⰪ �Է�
		play();//���� ����
		//����� ���
		if (ret > 100) ret = -1;
		printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	 
	return 0;
}