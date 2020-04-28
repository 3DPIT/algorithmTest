#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define NS 21
int N, ret;
int map[NS][NS];
int Max;
struct BoardGame {
	BoardGame() {
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		dfs(0);
		printf("%d\n", Max);
	}
	void init() {
		ret = N = 0;
		Max = 0x80000000;
		memset(map, 0, sizeof(map));
	}
	void copy(int map[NS][NS], int cmap[NS][NS]) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cmap[i][j] = map[i][j];
			}
		}
	}
	void arrRot() {
		int cmap[NS][NS] = { 0, };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cmap[i][j] = map[j][N-1 - i];
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				map[i][j] = cmap[i][j];
			}
		}
	}
	int numMax() {
		int mMax = 0x80000000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				mMax = mMax < map[i][j] ? map[i][j] : mMax;
			}
		}
		return mMax;
	}
	void downArr() {
		queue<int>q;
		for (int j = 0; j < N; j++) {// �� ������
			for (int i = N-1; i >=0; i--) {
				if (map[i][j] != 0) {
					q.push(map[i][j]);
					map[i][j] = 0;
				}
			}
			for (int i = N - 1; q.size() != 0; i--) {
				map[i][j] = q.front();
					q.pop();
				}
		}
		//print("�ʳ����� ���", 0);
		for (int j = 0; j < N; j++) {// �� ������
			for (int i = N - 1; i >= 1; i--) {
				if (map[i][j] == map[i - 1][j] && map[i][j] != 0) {
					map[i][j] += map[i - 1][j];
					map[i - 1][j] = 0;
				}
			}
		}
		//print("�� ���ϰ� ���", 0);
		for (int j = 0; j < N; j++) {// �� ������
			for (int i = N - 1; i >= 0; i--) {
				if (map[i][j] != 0) {
					q.push(map[i][j]);
					map[i][j] = 0;
				}
			}
			for (int i = N - 1; q.size()!=0; i--) {
				map[i][j] = q.front();
				q.pop();
			}
		}
		//print("�ʳ����� ���", 0);

	}
	void dfs(int idx) {
		if (idx == 4) {
			print("�����fin", 0);
			ret = numMax();//�Լ� - ���ִ밪 ã��
			Max = Max < ret ? ret : Max;//�ִ밪 �ֽ�ȭ
			return;
		}
		int cmap[NS][NS] = { 0, };
		copy(map, cmap);//�Լ� - ī��
		downArr();//�Լ� - �Ʒ��� ������
		print("�����", 0);
		dfs(idx + 1);
		copy(cmap, map);//�Լ� - ����

		arrRot();//�Լ� - ȸ��
		print("��ȸ�����", 0);
		copy(map, cmap);//�Լ� - ī��
		downArr();//�Լ� - �Ʒ��� ������
		print("�����", 0);
		dfs(idx + 1);
		copy(cmap, map);//�Լ� - ����

		arrRot();//�Լ� - ȸ��
		copy(map, cmap);//�Լ� - ī��
		print("��ȸ�����", 0);
		downArr();//�Լ� - �Ʒ��� ������
		print("�����", 0);
		dfs(idx + 1);
		copy(cmap, map);//�Լ� - ����

		arrRot();//�Լ� - ȸ��
		print("��ȸ�����", 0);
		copy(map, cmap);//�Լ� - ī��
		downArr();//�Լ� - �Ʒ��� ������
		print("�����", 0);
		dfs(idx + 1);
		copy(cmap, map);//�Լ� - ����
	}
	void print(string name, int num) {
		cout << name << endl;
		if (num == 0) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					printf("%3d", map[i][j]);
				}
				cout << endl;
			}
		}
	}

}BoardGame;

int main(void) {

	return 0;
}