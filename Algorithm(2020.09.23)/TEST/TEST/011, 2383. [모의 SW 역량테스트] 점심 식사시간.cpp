#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NSIZE 10//���� �� ���� ����
#define HSIZE 10//����� �ִ� ��
int N;//���� �� ���� ����
int H;//����� ��
int ret;//���� �ּҰ� ���� ����
int map[NSIZE][NSIZE];//�� �迭
int D[HSIZE];//������� ��� ������ ���� �迭
struct Data {
	int y, x, downTime, stairNum, flag;
};//����� ����� ��������
vector<Data>human;//����� ����
vector<Data>stair;//����� ����
void initAndInput() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	H = N = 0;
	ret = 0x7fffffff;
	memset(map, 0, sizeof(map));
	human.clear(); stair.clear();
	//�ʱ� �Է�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] > 1) {//����� ����

				stair.push_back({ i,j,0,map[i][j],0 });
			}
			else if (map[i][j] == 1) {//����� ����
				human.push_back({ i,j,-2,0,0 });
			}
		}
	}
}
void dfs(int idx, int cnt) {//������ ��� �����ϱ�
	if (cnt == human.size()) {//�ٻ��� ���
		//cout << "����� ������ ��� ���" << endl;
		//for (int i = 0; i < human.size(); i++) {
		//	cout << D[i] << " ";
		//}
		vector<Data>v;//�ΰ����� ���� 
		//������ �����ſ��� 1����ܰ� 2����� ��� ������
		for (int i = 0; i < human.size(); i++) {//
			v.push_back({ human[i].y,human[i].x,0,D[i] });
			//����� ��ǥ�� y, x, 0, �׻���� ������ ���
		}
		int Time = 0;// �ð� ���
		vector<int>one;
		vector<int>two;
		vector<int>oneStay;
		vector<int>twoStay;
		int finishCnt = 0;//���� ����
		while (finishCnt != human.size()) {//����� �� �������� ���� ������
			++Time;//�� ����
			for (int i = 0; i < v.size(); i++) {//�������Կ� ���� flag 1�ΰ� �ð� ����					
				if (v[i].flag == 1) {
					v[i].downTime--;
					if (v[i].downTime == 0 && v[i].flag != 3) {//������ Ÿ��
						//���� ���� �ϸ鼭 �� ��ܿ����� ����
						if (v[i].stairNum == 1) {
							one.pop_back();//1��� ����
						}
						else if (v[i].stairNum == 2) {
							two.pop_back();//2��� ����
						}
						v[i].flag = 3;
						finishCnt++;
					}
				}
			}
			if (finishCnt == human.size())break;
			for (int i = 0; i < v.size(); i++) {//��ܿ� �ø��� ��
				//����� ��ġ
				int sy = stair[v[i].stairNum - 1].y; int sx = stair[v[i].stairNum - 1].x;
				//����� ��ġ
				int hy = v[i].y; int hx = v[i].x;
				//�Ÿ� ���
				int distance = abs(sy - hy) + abs(sx - hx);
				if (distance == Time || (v[i].flag == 2 && oneStay.size() != 0 && oneStay.front() == i) || (v[i].flag == 2 && twoStay.size() != 0 && twoStay.front() == i)) {//�̰�� ��ܿ� ������ ���
					if (v[i].stairNum == 1 && one.size() != 3) {//�ִ� �� �� �ִ� ���
						if (v[i].flag == 2)oneStay.erase(oneStay.begin());//������� �־��ֱ�
						one.push_back(i);
						v[i].downTime = stair[0].stairNum;//��ܿ� �ִٴ� ǥ��
						v[i].flag = 1;//���� ��ܿ� �ִ°� ǥ��
					}
					else if (v[i].stairNum == 2 && two.size() != 3) {
						if (v[i].flag == 2)twoStay.erase(twoStay.begin());//������� �־��ֱ�
						two.push_back(i);
						v[i].downTime = stair[1].stairNum;//��ܿ� �ִٴ� ǥ��
						v[i].flag = 1;//���� ��ܿ� �ִ°� ǥ��
					}
					else {
						if (v[i].flag != 2 && v[i].stairNum == 1)oneStay.push_back(i);
						if (v[i].flag != 2 && v[i].stairNum == 2)twoStay.push_back(i);
						v[i].flag = 2;//��� ���� �͵�
					}
				}
			}
			//������� ������� �̵���Ű��
		}
		ret = min(ret, Time);
		return;
	}
	D[idx] = 1;//1�� ��� ����
	dfs(idx + 1, cnt + 1);
	D[idx] = 2;//2�� ��� ����
	dfs(idx + 1, cnt + 1);
	D[idx] = 0;//��� ���� ����
}
int main(void) {
	int T;//�׽�Ʈ ���̽�
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		initAndInput();//�ʱ�ȭ �� �ʱ� �Է�
		dfs(0, 0);//������� ��� ����
		printf("#%d %d\n", tc, ret+1);
	}

	return 0;
}