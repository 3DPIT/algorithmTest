#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define S 10
int cube[S];//�ֻ������� �� ���� �迭
int ret;//����� ���庯��
int D[S];//1���� ���� 4���� ���� ����
int B[33] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,-1,
			13,16,19,25,22,24,28,27,26,30,35 };//������ �� ����
struct Data {
	int idx, pidx;//������ �ε��� ���� ������ �ε�����
};
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	ret = 0x80000000;//�ּҰ� ����
	memset(cube, 0, sizeof(cube));
	memset(D, 0, sizeof(D));
	//�ʱ� �Է�
	for (int i = 0; i < 10; i++) {
		scanf("%d", &cube[i]);
	}
}
void dfs(int idx, int cnt) {//1. ���� �� ���� ���� ���ϱ�(o)
	if (cnt == 10) {
		int sum = 0;//�� ����
		Data horse_info[5] = { 0, };
		for (int i = 0; i < 10; i++) {//���� ������� ����
			int num = D[i];//���� ����
			for (int j = 0; j < cube[i]; j++) {//���� �̵�����
				//3. ������ĭ ������ ���̵� ���� ��Ű��
				if (horse_info[num].pidx == -1)continue;
				if (horse_info[num].pidx != 0) {//��ġ �̵� ��Ű�� Ư���� ĭ����
					horse_info[num].idx = horse_info[num].pidx;//��ġ �̵�
					horse_info[num].pidx = 0;
				}
				else if (horse_info[num].pidx != -1) {//+1�� �����Ǵ� ĭ������ �̵�
					horse_info[num].idx++;
				}
				if (horse_info[num].idx == 27)horse_info[num].pidx = 25;//24->25
				else if (horse_info[num].idx == 30)horse_info[num].pidx = 25;//26->25
				else if (horse_info[num].idx == 25)horse_info[num].pidx = 31;//25->30
				else if (horse_info[num].idx == 32) horse_info[num].pidx = 20;//35->40
				else if (horse_info[num].idx == 21)	horse_info[num].pidx = -1;//40->����

			}
			//2. �̵��� �������� ���� �ִ��� Ȯ���ؼ� �� ����� ��ü�� �������� �׸��� ������������
			for (int h = 1; h <= 4; h++) {
				if (h != num && horse_info[num].idx != 0 && horse_info[num].pidx != -1 &&
					horse_info[h].idx == horse_info[num].idx) {
					return;//��ü ���Ͻ�Ű��
				}
			}
			if (horse_info[num].pidx != -1) sum += B[horse_info[num].idx];//���� ����

			//�Ķ� �κп� ���߸� �׹������� �̵� ��Ű�� ���� 
			if (horse_info[num].idx == 5) horse_info[num].pidx = 22;//10->13
			else if (horse_info[num].idx == 10)horse_info[num].pidx = 26;//20->22
			else if (horse_info[num].idx == 15) horse_info[num].pidx = 28;//30->28

		}
		//4. �ù� ����� ������ �ִ밪 ���ؼ� ret �� �����ϱ�
		ret = max(ret, sum);
		return;
	}
	for (int i = 1; i <= 4; i++) {
		if (D[idx] == 0) {
			D[idx] = i;
			dfs(idx + 1, cnt + 1);
			D[idx] = 0;
		}
	}

}
void play() {
	dfs(0, 0);
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		play();//���� ����
		//���
		printf("%d\n", ret); //printf("#%d %d\n", tc, ret);
	}
	return 0;
}
