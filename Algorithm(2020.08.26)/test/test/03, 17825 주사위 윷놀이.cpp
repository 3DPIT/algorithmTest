#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
int cubeNum[11];//�ֻ��� �� ���� �迭
int D[33];//���� ���� ���� �迭
int ret;//�ִ� ����
struct Data {
	int idx,nextIdx,visitPreIdx;//���� �ε���,���� �ε���
}horse[4];//��
int board[33] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,
			13,16,19,25,
			22,24,
			28,27,26,
			30,35 };//�� �������
void init() {
	ret = 0x80000000;
	memset(horse, 0, sizeof(horse));
	memset(cubeNum, 0, sizeof(cubeNum));//�ʱ�ȭ
	memset(D, 0, sizeof(D));//�ʱ�ȭ
	for (int i = 0; i < 10; i++) {
		scanf("%d", &cubeNum[i]);
	}
}
bool playGame(int &sum) {
	sum = 0;
	memset(horse, 0, sizeof(horse));
	int visit[33] = { 0, };//�湮üũ
	//������ �ε����� �̰��̸� ���� �Ѿ��
	/*5-22
	  25-31
	  27-25
	  30-25
	  32-20
	  20-21
	*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < cubeNum[i]; j++) {
			if (horse[D[i]].nextIdx == -1|| horse[D[i]].nextIdx == -2)break;//���� �Ѿ�� ��� ����
			if (horse[D[i]].nextIdx != 0) {//�Ķ��� �κ��ΰ�� �� ������ �̵� ��Ű��
				horse[D[i]].idx = horse[D[i]].nextIdx;
				horse[D[i]].nextIdx = 0;
			}
			else  horse[D[i]].idx++;
			if (horse[D[i]].idx == 25)horse[D[i]].nextIdx = 31;//25������ 30������ ����
			if(horse[D[i]].idx == 27|| horse[D[i]].idx == 30)horse[D[i]].nextIdx = 25;
			//19������ 25��
			//24������ 25��
			//26������ 25�� ���� ����
			if (horse[D[i]].idx == 32)horse[D[i]].nextIdx = 20;//35������ 40�� ���� ����
			if (horse[D[i]].idx == 20)horse[D[i]].nextIdx = 21;
			if (horse[D[i]].idx == 21) {
				horse[D[i]].nextIdx = -1;//�������� ���� üũ
				break;
			}
		}
		if (horse[D[i]].idx == 5)horse[D[i]].nextIdx = 22;
		if (horse[D[i]].idx == 10)horse[D[i]].nextIdx = 26;
		if (horse[D[i]].idx == 15)horse[D[i]].nextIdx = 28;
		if (horse[D[i]].idx == 25)horse[D[i]].nextIdx = 31;
		if (horse[D[i]].idx == 27|| horse[D[i]].idx == 30)horse[D[i]].nextIdx = 25;
		if (horse[D[i]].idx == 32)horse[D[i]].nextIdx = 20;
		if (horse[D[i]].idx == 20)horse[D[i]].nextIdx = 21;


		if (visit[horse[D[i]].idx] == 0) {//���� ĭ�� ���� �ִ��� Ȯ��
			if (horse[D[i]].idx == 21 && horse[D[i]].nextIdx == -1) {
				sum += board[horse[D[i]].idx];//�̵� �� �� ������ĭ�� �� ����
				if (horse[D[i]].visitPreIdx != 0) {//������ ĭ�� �湮 ����� ���� ����
					visit[horse[D[i]].visitPreIdx] = 0;
					horse[D[i]].visitPreIdx = 0;
				}
				horse[D[i]].nextIdx = -2;
			}
			if(horse[D[i]].idx != 21){
				sum += board[horse[D[i]].idx];//�̵� �� �� ������ĭ�� �� ����
				if (horse[D[i]].visitPreIdx != 0) {//������ ĭ�� �湮 ����� ���� ����
					visit[horse[D[i]].visitPreIdx] = 0;
					horse[D[i]].visitPreIdx = 0;
				}
				horse[D[i]].visitPreIdx = horse[D[i]].idx;//���� �ε��� ���
				visit[horse[D[i]].idx] = 1;//�湮 üũ
			}
		}
		else return false;//���� ĭ�� ���� �ִ°�� ���� 
	}
	return true;
}
void dfs(int idx,int d) {//���� �̾Ƴ���
	if (idx == 10) {//���� ���� 10�� �̱�
		int sum = 0;
		if (!playGame(sum)) return;
		ret = ret < sum ? sum : ret;
		return;
	}
	for (int i = 0; i < 4; i++) {
		D[idx] = i;
		dfs(idx + 1,d++);
		D[idx] = 0;
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {
		init();
		dfs(0,0);
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}