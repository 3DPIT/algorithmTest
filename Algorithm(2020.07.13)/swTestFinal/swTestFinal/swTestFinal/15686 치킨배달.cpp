#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define MAP_SIZE 51
int N, M;// ��ũ��, ġŲ�� �ִ� ����
int map[MAP_SIZE][MAP_SIZE];
int finalMin = 0x7fffffff;//ġŲ�Ÿ� ���� �ּҰ�
struct Data{
	int y, x;
};
vector<Data>home;// �� ��ǥ ����
vector<Data>chicken;//ġŲ ��ǥ ����
vector<int>shortDistance[MAP_SIZE*MAP_SIZE];//�� ġŲ���� �Ÿ� ����
vector<int>D;// ���� ġŲ�� ���� 
void dfs(int idx, int d) {
	if (idx > chicken.size())return;
	if (d == M) {// �ִ� ġŲ���� ���� ���
		//�ּ��� ġŲ�� ã�Ƴ���
		int ret = 0;//�ּ� �Ÿ��� ����
		for (int i = 0; i < home.size(); i++) {
			int minDistance = 0x7fffffff;
			for (int j = 0; j < D.size(); j++) {
				minDistance = minDistance > shortDistance[i][D[j]]
					? shortDistance[i][D[j]] : minDistance;//�ּ� �Ÿ� ã��
			}
			ret += minDistance;//�ּ� �Ÿ��� ����
		}
		finalMin = finalMin > ret ? ret : finalMin;//���� �ּҰ�
		return;
	}
	D.push_back(idx);
	dfs(idx + 1, d + 1);// ġŲ�� ���� ���
	D.pop_back();
	dfs(idx + 1, d);//ġŲ�� �Ȼ̰� �ѱ���
}
void init() {//�ʱ�ȭ �� �Է� 
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);//�Է°� �Է�
			if (map[i][j] == 1) {
				home.push_back({ i,j });// �� ��ǥ ����
			}
			if (map[i][j] == 2) {
				chicken.push_back({ i,j });//ġŲ ��ǥ ����
			}
		}
	}
	// �̸� ���� ġŲ���� �Ÿ� ���� ����
	for (int i = 0; i < home.size(); i++) {
		for (int j = 0; j < chicken.size(); j++) {
			int distance1 = abs(home[i].y - chicken[j].y) + abs(home[i].x - chicken[j].x);//�Ÿ� ���ϱ�
			shortDistance[i].push_back(distance1);
		}
	}
}
int main(void) {
	init();
	dfs(0, 0);
	printf("%d\n", finalMin);
	return 0;
}