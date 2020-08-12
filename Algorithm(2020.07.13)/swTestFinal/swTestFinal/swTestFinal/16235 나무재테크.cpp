#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define N_SIZE 12 //�ִ� �迭 ũ�Ⱚ
int dy8[] = {-1,-1,-1,0,0,1,1,1};
int dx8[] = {-1,0,1,-1,1,-1,0,1};
int currentSoil[N_SIZE][N_SIZE];//���翵��� 5����
int A[N_SIZE][N_SIZE];//S2D2�� ���� ������ �����
int ret;//����� ����
int N, M, YEAR;//�迭ũ��, ������, �� ��
vector<int>Tree[N_SIZE][N_SIZE];//���� ���� ����
struct Data {
	int y, x, age;
};
vector<Data>dieTree;
bool safe(int y, int x) {//���� üũ
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
//�� 
//�ڽ� ���� ��ŭ ��� ��� 
// ���� 1���� (���� ���� ��� ����)
void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Tree[i][j].size() != 0) {//������ �Ѱ��� ������
				sort(Tree[i][j].begin(), Tree[i][j].end());//������� ����
				for (int k = 0; k < Tree[i][j].size(); k++) {//��� ���
					if (Tree[i][j].size() == 0)break;
					if (currentSoil[i][j] - Tree[i][j][k] >= 0) {
						currentSoil[i][j] -= Tree[i][j][k];
						Tree[i][j][k]++;//���� ����
					}
					else {
						dieTree.push_back({ i,j,Tree[i][j][k]/2 });//���� ���� ���� �� /2����
						Tree[i][j].erase(Tree[i][j].begin() + k);//���� ���� ����
						k--;
					}
				}
			}
		}
	}
}

//����
//���� ���� ���� ���� / 2 ���� ������� ���
void summer() {
	for (int i = 0; i < dieTree.size(); i++) {
		currentSoil[dieTree[i].y][dieTree[i].x] += dieTree[i].age;//����� ����
	}
	dieTree.clear();//���� ���� �ʱ�ȭ
}

//���� 
//���̰� 5�� ����ΰ� 8�������� ���� 1��¥�� ����
void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Tree[i][j].size() != 0) {
				for (int k = 0; k < Tree[i][j].size(); k++) {
					if (Tree[i][j][k] % 5 == 0) {// ���� �����ϸ�
						for (int dir = 0; dir < 8; dir++) {
							int ny = i + dy8[dir];
							int nx = j + dx8[dir];
							if (safe(ny, nx)) {
								Tree[ny][nx].push_back(1);
							}
						}
					}
				}
			}
		}
	}
}
//�ܿ�
//S2D2�� ����� �ִ� ���� A�� �Է����� �־��� ��� ���� 
void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			currentSoil[i][j] += A[i][j];// ����� ���� ��Ű��
		}
	}
}
void init() {//�ʱ�ȭ ��Ű��
	N = M = YEAR = ret = 0;
	memset(currentSoil, 0, sizeof(currentSoil));
	memset(A, 0, sizeof(A));
	scanf("%d %d %d", &N, &M, &YEAR);//�迭 ũ��, ���� ��, �⵵ �Է�
	for (int i = 1; i <= N; i++) {// �ʱ� �� 5�� �ʱ�ȭ �ϸ鼭 A�迭 �Է�
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);//�ܿ￡ ������ �����
			currentSoil[i][j] = 5;//�ʱ� �� �����
		}
	}

	int y, x, age;
	for (int i = 0; i < M; i++) {// ���� �ɱ�
		scanf("%d %d %d", &y, &x, &age);
		Tree[y][x].push_back(age);
	}
}
void chkCnt() {//���� �ִ� ���� ���� üũ
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ret += Tree[i][j].size();
			Tree[i][j].clear();
		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {//�׽�Ʈ ���̽� ��ŭ �ݺ�
		init();
		while (YEAR--) {//�⵵ ��ŭ �ݺ�
			spring();
			summer();
			fall();
			winter();
		}
		chkCnt();// ���� ���� ����
		printf("%d\n", ret);
	//	printf("#%d %d\n", tc, ret);//����� ����
	}
	return 0;
}