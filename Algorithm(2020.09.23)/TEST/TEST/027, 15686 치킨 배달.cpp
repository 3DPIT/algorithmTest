#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 51 //�迭�� �ִ� ũ��
int N, M;//�迭 ũ��, �̴� ġŲ�� ��
int ret; //����� ���� ����
int B[NS][NS];
struct Data {
	int y, x;
};//��ǥ ����ü
vector<Data>C;//ġŲ���� ����
vector<Data>H;//������ ����
vector<int>cC;
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = 0;
	ret = 0x7fffffff;//�ּҰ� ����
	C.clear(); H.clear();
	cC.clear();
	//�ʱ� �Է�
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &B[i][j]);
			// 1. ���� ���� ����
			if (B[i][j] == 1) {//���� ���
				H.push_back({ i,j });
			}
			//2. ġŲ���� ���� ����
			else if (B[i][j] == 2) {//ġŲ���� ���
				C.push_back({ i,j });
			}
		}
	}
}
void dfs(int idx, int cnt) {//3. ���� ���� M���� ġŲ�� ����
	if (idx == C.size()+1)return;//
	if (cnt== M) {//M���� ġŲ�� �����ϱ�
		//4. return ; �κп��� ġŲ�Ÿ� �ּҰ� �̱�
		int sum = 0;//�ּҰŸ� ����
		for (int i = 0; i < H.size(); i++) {// ������ ������ �ּ� �Ÿ��� ġŲ�� ã��
			int minD = 0x7fffffff;
			for (int j = 0; j < cC.size(); j++) {
				int D = abs(H[i].y - C[cC[j]].y) + abs(H[i].x - C[cC[j]].x);
					minD = min(minD, D);//�ּ� ã��
				}
				sum += minD;
		}
		//5. �ּҰ� ����
		ret = min(ret, sum);
		return;
	}
	cC.push_back(idx);
	dfs(idx + 1, cnt + 1);
	cC.pop_back();
	dfs(idx + 1, cnt);
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d",&T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		dfs(0, 0);
		//���
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}