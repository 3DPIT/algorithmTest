#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define S 101//�ִ� ���ڿ� �迭 ũ��
int r, c, k;//ù° �־����� ��
int ret;//��� ��
int B[S][S];//�ʱ� �迭
int Fr, Fc;//���� ��� ����
struct Data {
	int num; int cnt;
};
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	r = c = k = ret = 0;
	Fr = Fc = 3;
	memset(B, 0, sizeof(B));
	//�ʱ� �Է�
	scanf("%d %d %d", &r, &c, &k);//�ʱ� �Է� ����
	for (int y = 1; y <= 3; y++) {
		for (int x = 1; x <= 3; x++) {
			scanf("%d", &B[y][x]);//�ʱ� �Է� �迭
		}
	}
}
//���� ���� Ƚ���� Ŀ���� ������, �׷��� ���� ���������� ���� Ŀ���� ������ ����
bool cmp(Data a, Data b) {
	if (a.cnt == b.cnt)return a.num < b.num;
	else return a.cnt < b.cnt;
}
void R() {//R����
	int MaxC = 0x80000000;//�ִ� ������ �ప

	for (int y = 1; y <= Fr; y++) {
		Data D[S] = { 0, };//���� ���� 
		vector<Data>v;
		for (int x = 1; x <= Fc; x++) {
			if (B[y][x] != 0) {//0�� ����
				D[B[y][x]].num = B[y][x];//���� 
				D[B[y][x]].cnt++;//����  ����
				B[y][x] = 0;
			}
		}
		for (int i = 1; i <= 100; i++) {
			if (D[i].num != 0)v.push_back({ D[i].num,D[i].cnt });//�����ϱ��� 
		}
		sort(v.begin(), v.end(), cmp);
		int size = v.size();//���� ����
		MaxC = max(MaxC, size*2);
		//���Է�
		int vidx = 0;//���� ���� �ε���
		for (int x = 0;vidx<size;) {
			B[y][++x] = v[vidx].num;
			B[y][++x] = v[vidx].cnt;
			vidx++;
		}
	}
	Fc = (MaxC) % 100;

}
void C() {//C����
	int MaxR = 0x80000000;//�ִ� ������ �ప

	for (int x = 1; x <= Fc; x++) {
		Data D[S] = { 0, };//���� ���� 
		vector<Data>v;
		for (int y = 1; y <= Fc; y++) {
			if (B[y][x] != 0) {//0�� ����
				D[B[y][x]].num = B[y][x];//���� 
				D[B[y][x]].cnt++;//����  ����
				B[y][x] = 0;
			}
		}
		for (int i = 1; i <= 100; i++) {
			if (D[i].num != 0)v.push_back({ D[i].num,D[i].cnt });//�����ϱ��� 
		}
		sort(v.begin(), v.end(), cmp);
		int size = v.size();//���� ����
		MaxR = max(MaxR, size * 2);
		//���Է�
		int vidx = 0;//���� ���� �ε���
		for (int y = 0; vidx < size;) {
			B[++y][x] = v[vidx].num;
			B[++y][x] = v[vidx].cnt;
			vidx++;
		}
	}
	Fr = (MaxR % 100);

}
void Play() {//�ùĽ���
	while (1) {
		if (ret == 101)break;
		if (B[r][c] == k)break;
		//1.R ���� : �迭 A�� ��� �࿡ ���ؼ� ������ �����Ѵ�.���� ���� �� ���� ������ ��쿡 ����ȴ�.
		if(Fr>=Fc) R();
		//2.C ����: �迭 A�� ��� ���� ���ؼ� ������ �����Ѵ�. ���� ���� < ���� ������ ��쿡 ����ȴ�.
		else if(Fr<Fc) C();
		ret++;
	}
	if (ret == 101)ret = -1;//���� ��ã���� -1 ���
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		Play();
		//���
		printf("%d\n", ret); //printf("#%d %d\n", tc, ret);
	}
	return 0;
}