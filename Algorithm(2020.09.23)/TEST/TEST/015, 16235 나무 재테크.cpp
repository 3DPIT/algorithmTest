#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define NSIZE 11
int N, M, K;//��ũ��, ������, ���
int A[NSIZE][NSIZE];//�ʱ� �Է� �迭
int soil[NSIZE][NSIZE];//��� ����Ǵ� �迭
int die_soil[NSIZE][NSIZE];//���� ���� ����Ǵ� �迭
int ret;//����� ����
int dy[] = { -1,-1,-1,0,0,1,1,1};//8���� ���� ���Ľ� ���
int dx[] = { -1,0,1,-1,1,-1,0,1};
vector<int>tree[NSIZE][NSIZE];//���� ����Ǵ� �迭
bool safe(int y, int x) {//���� Ȯ��
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = K = ret = 0;
	memset(A, 0, sizeof(A));
	memset(soil, 0, sizeof(soil));
	memset(die_soil, 0, sizeof(die_soil));
	for (int i = 1; i < NSIZE; i++)for (int j = 1; j < NSIZE; j++)tree[i][j].clear();
	//�ʱ��Է�
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);//�ܿ￡ �Ѹ� ��� ����
			soil[i][j] = 5;//�ʱ� ��� ����
		}
	}
	for (int m = 0; m < M; m++) {
		int y, x, age;
		scanf("%d %d %d", &y, &x, &age);
		tree[y][x].push_back(age);
	}
}
void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree[i][j].size() != 0) {
				//�ϳ��� ĭ�� ���� ���� ������ �ִٸ�, ���̰� � �������� ����� �Դ´�.
				sort(tree[i][j].begin(), tree[i][j].end());//ũ�� ������ ���� ����
				for (int k = 0; k < tree[i][j].size(); k++) {
					if (tree[i][j].size() == 0)break;
					int currentTree = tree[i][j][k];//���� ���� ����
					//����, ���� ����� ������ �ڽ��� ���̸�ŭ ����� ���� �� ���� ������ ����� ���� ���ϰ� ��� �״´�
					if (soil[i][j] - currentTree < 0) {//��� ���� ���ϴ� ���
						die_soil[i][j] += (currentTree / 2);//���� ���� ��� ����
						tree[i][j].erase(tree[i][j].begin() + k);//���� �������̰� ���ֱ�
						k--;
					}
					//������ ������ �ڽ��� ���̸�ŭ ����� �԰�, ���̰� 1 �����Ѵ�
					else if(soil[i][j]-currentTree>=0){//������ ����
						soil[i][j] -= currentTree;//��� ���
						tree[i][j][k]++;//���� �ѻ� ����					
					}
				}
			}
		}
	 }
}
//�������� ���� ���� ������ ������� ���ϰ� �ȴ�. ������ ���� �������� ���̸� 2�� ���� ���� ������ �ִ� ĭ�� ������� �߰��ȴ�.
void summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			soil[i][j] += die_soil[i][j];//��� ����
			die_soil[i][j] = 0;//���� ���� ��� ��� �迭 �ʱ�ȭ
		}
	}
}
//�������� ������ �����Ѵ�. �����ϴ� ������ ���̰� 5�� ����̾�� �ϸ�, ������ 8���� ĭ�� ���̰� 1�� ������ �����. � ĭ (r, c)�� ������ ĭ�� (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1) �̴�. ���� ���� ����� ĭ���� ������ ������ �ʴ´�.
void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree[i][j].size()!=0) {//������ ������
				for (int k = 0; k < tree[i][j].size(); k++) {
					if (tree[i][j][k] % 5 == 0) {//������ ���̰� 5�� ������
						for (int dir = 0; dir < 8; dir++) {
							int ny = i + dy[dir]; int nx = j + dx[dir];
							if (safe(ny, nx)) {//������ ��ġ�� ������ �� �ִ� �����̶��
								tree[ny][nx].push_back(1);//�ѻ쳪�� ����
							}
						}
					}
				}
			}
		}
	}
}
//�ܿ￡�� S2D2�� ���� ���ƴٴϸ鼭 ���� ����� �߰��Ѵ�. �� ĭ�� �߰��Ǵ� ����� ���� A[r][c]�̰�, �Է����� �־�����.
void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			soil[i][j] += A[i][j];
		}
	}
}
void chkTree() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ret += tree[i][j].size();
		}
	}
}
void tree_go() {//������ ����
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}
	chkTree();//���� ���� ����
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽�
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		tree_go();
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}