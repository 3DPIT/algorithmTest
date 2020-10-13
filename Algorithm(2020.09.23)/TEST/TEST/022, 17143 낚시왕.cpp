#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define NMS 102
int N, M, K;//����,����,��� ��
int ret;//�����
int sea[NMS][NMS];//�ٴ� �迭
int dy[] = { 0,-1,1,0,0 };
int dx[] = {0,0,0,1,-1 };
struct Data {
	int y, x, s, d, z;//��ġ y, ��ġ x, ���ǵ�, ����, ũ��
};
vector<Data>shark;
bool cmp(Data a, Data b) {//���� ���� ����
	if (a.y == b.y)return a.x < b.x;
	return a.y < b.y;
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = M = K = ret = 0;
	memset(sea, 0, sizeof(sea));
	//�ʱ� �Է�
	scanf("%d %d %d", &N, &M, &K);//���� ���� ũ�� ����� ��
	for (int k = 0; k < K; k++) {//�ʱ� �Է�
		Data c;
		scanf("%d %d %d %d %d", &c.y, &c.x, &c.s, &c.d, &c.z);
			if (c.d == 1 || c.d == 2) {
				//���Ʒ� ��� ���ǵ� ���̱�
				c.s = (c.s % ((N*2)-2));//(N-1)*2;
			}
			else if (c.d == 3 || c.d == 4) {//(M-1)*2
				c.s = (c.s% ((M * 2) - 2));
			}
		shark.push_back(c);//��� ���� �Է�
	}
}
bool safe(int y, int x) {
	return 1<= y && y <= N && 1 <= x && x <= M;
}
void fishing() {
	for (int j = 1; j <= M; j++) {//���������� ���� ����
		sort(shark.begin(), shark.end(),cmp);
		//���ø� �ϴ� ���
		for (int s = 0; s < shark.size(); s++) {
			if (shark.size() == 0)break;
			if (shark[s].x == j) {//��� ���ü���
				ret += shark[s].z;//��� ����
				shark.erase(shark.begin() + s);
				break;//�Ѹ����� ��ƾ��� ��Ģ��
			}
		}
		//����� �̵�
		for (int i = 0; i < shark.size(); i++) {
			Data n; Data c = shark[i];
			for (int s = 0; s < c.s; s++) {//���ǵ� ��ŭ �̵�
				n.y = c.y + dy[c.d];
				n.x = c.x + dx[c.d];
				if (safe(n.y, n.x)) {//�̵� ������ �����̸� �̵�
					c.y = n.y; c.x = n.x;
					shark[i].y = c.y; shark[i].x = c.x;
				}
				else {//����� ���
					//���� ��ȯ
					if (c.d == 1)c.d = 2;
					else if (c.d == 2)c.d = 1;
					else if (c.d == 3)c.d = 4;
					else if (c.d == 4)c.d = 3;
					//��ĭ�̵���Ű��
					shark[i].d = c.d;
					c.y = c.y + dy[c.d]; c.x = c.x + dx[c.d];//�̵�
					shark[i].y = c.y; shark[i].x = c.x;
				}
			}
		}//for i
		sort(shark.begin(), shark.end(),cmp);//�ѹ��� ����
		//���� ��ġ�� ��� �����ϱ�
		for (int a = 0; a < shark.size() - 1; a++) {
			if (shark.size() == 0)break;
			int cnt = 0;//���� ��� ������ üũ
			int maxSize = shark[a].z;
			Data cM;//�ƽ��� ����
			cM = shark[a];
			for (int b = a+1; b < shark.size(); b++) {
				if (shark[a].y == shark[b].y&&shark[a].x == shark[b].x) {//������ ����
					if (maxSize < shark[b].z) {//����ū ��ü �����ϱ�
						maxSize = shark[b].z;
						cM = shark[b];
					}
					cnt++;
				}
				else break;//���� ������ ����
			}
			if (cnt != 0) {
				shark.erase(shark.begin() + a+1, shark.begin() +a+ cnt+1);//��� �԰�
				shark[a] = cM;//���� ū������ ��ü
			}
		}
	}//for j
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();// �ʱ�ȭ �� �ʱ� �Է�
		fishing();//���� ����
		//���
		printf("%d\n", ret);
	//	printf("#%d %d\n", tc, ret);
	}
	return 0;
}