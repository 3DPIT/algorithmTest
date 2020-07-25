#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
#define MAP_SIZE 101
int N;
int map[MAP_SIZE][MAP_SIZE];
int dy[] = { 0,-1,0,1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, dir, age;
};
void print(string name, int idx, vector<int> &dragonDir) {
	cout << name<<endl;
	for (int i = 0; i < dragonDir.size(); i++) {
		cout << dragonDir[i] << " ";
	}
	cout << endl;

}
int main(void) {
	scanf("%d", &N);//�巡�� Ŀ�� ����
	for (int i = 0; i < N; i++) {
		int y, x, dir, age;
		scanf("%d %d %d %d", &x, &y, &dir, &age);//y��, x��, ���� , ����
		vector<int>dragonDir;//�巡�� ��� ����
		dragonDir.push_back(dir);
		for (int age_Idx = 0; age_Idx < age; age_Idx++) {// ���� ��ŭ ������
			for (int k = dragonDir.size() - 1; k >= 0; k--) {//�巡�� ��� ���������� �ð���� 90 ȸ��
				dragonDir.push_back((dragonDir[k]+1) % 4);
			}
			//print("�巡�� ���", age_Idx + 1,dragonDir);
		}
		//�巡�� ��� �迭�� ���
		map[y][x] = 1;
		for (int k = 0; k < dragonDir.size(); k++) {
			map[y + dy[dragonDir[k]]][x + dx[dragonDir[k]]] = 1;
			y += dy[dragonDir[k]]; x += dx[dragonDir[k]];
		}
	}
	//1x1 ���簢�� ã��
	int ret = 0;//���簢�� ���� ����
	for (int i = 0; i < 100-1; i++) {
		for (int j = 0; j < 100-1; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1
				&& map[i + 1][j] == 1 && map[i + 1][j + 1] == 1) {
				ret++;
			}
		}
	}
	cout << ret << endl;// ���簢�� ���� ���
	return 0;
}