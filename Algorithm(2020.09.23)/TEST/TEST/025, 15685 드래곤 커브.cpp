#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 101//�迭 �ִ� ũ��
int N;//�迭�� ũ��
int ret;//��� ��
int map[NS][NS];//�巡�� Ŀ�� Ȯ�� �迭
int dy[] = { 0,-1,0,1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, dir, gen;//��ǥ, ����, ����
};
vector<Data>dragon;
void init_input(){//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = ret = 0;
	memset(map, 0, sizeof(map));
	dragon.clear();
	//�ʱ� �Է�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		Data c;
		scanf("%d %d %d %d", &c.x, &c.y, &c.dir, &c.gen);
		dragon.push_back(c);//�巡�� ���� ����
	}
}
void dragonLevel() {//�巡�� Ŀ�� �Է�
	for (int i = 0; i < dragon.size(); i++) {
		//1. �巡�� ���� ��� ����
		vector<int>dragonD;//�巡�� ���� ����
		dragonD.push_back(dragon[i].dir);
		for (int g = 1; g<=dragon[i].gen; g++) {
			for (int D = dragonD.size() - 1; D >= 0; D--) {
				dragonD.push_back((dragonD[D]+1) % 4);//��� ����
			}
		}
		//2. �巡�� ���� ��� �迭 ����
		int y = dragon[i].y; int x = dragon[i].x;
		for (int di = 0; di < dragonD.size(); di++) {
			map[y][x] = 1;
			Data n; n.y = y + dy[dragonD[di]]; n.x = x + dx[dragonD[di]];
			map[n.y][n.x] = 1;
			y = n.y; x = n.x;
		}
	}
	//3. Ȯ��
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1) {
				ret++;
			}
		}
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽�
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		dragonLevel();//�巡�� ����
		//���
		//printf("#%d %d\n", tc, ret);
		printf("%d\n", ret);
	}
	return 0;
}