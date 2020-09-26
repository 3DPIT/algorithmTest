#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
struct Data {
	int y, x, k, dir;//��ġy,x,���� ��, ����
};
int dy[] = { 0,-1,1,0,0 };//�� �� �� ��
int dx[] = { 0,0,0,-1,1 };
vector<Data>MS;//�̻����� ���� ��°�
int N, K, M;//���� ����, �̻��� ������ ����, �ݸ��ð�
int ret;//��� ��(���� �̻����� ��)
bool safeZone(int y, int x) {
	return y == 0 || x == 0 || y == N - 1 || x == N - 1;
}
bool cmp(Data a, Data b) {//���� ����
	if (a.y == b.y)return a.x < b.x;
	else return a.y < b.y;
}
void init() {
	//�ʱ�ȭ
	MS.clear();
	N = K = M = ret = 0;

	//�Է�
	scanf("%d %d %d", &N, &M, &K);
	for (int k = 0; k < K; k++) {//�̻��� ���� �Է�
		Data c;

		scanf("%d %d %d %d", &c.y, &c.x, &c.k, &c.dir);
		MS.push_back(c);//�Է�
	}
	return;
}
void play() {
	for (int m = 0; m < M; m++) {//�ݸ��ð�
		if (MS.size() == 0)break;//Ż��
		for (int k = 0; k < MS.size(); k++) {//�̻��� �̵���Ű��
			if (MS.size() == 0)break;//Ż��
			Data n, c;//������ġ, ������ġ ���� ����
			c = MS[k];

			n.y = c.y + dy[c.dir]; n.x = c.x + dx[c.dir];//��ġ �̵�
			n.k = c.k; n.dir = c.dir;
			if (safeZone(n.y, n.x)) {//���� ������ ������
				//�̻��� �� �� ���� �� ���� �ݴ�� ����
				if (c.k == 1) {//�̻����� ���� 0�Ǵ� �������
					MS.erase(MS.begin() + k);
					k--;
				}
				else {
					//�̻��� �� ����
					n.k = c.k / 2;
					//���� ��ȯ
					if (c.dir == 1)n.dir = 2;
					else if (c.dir == 2)n.dir = 1;
					else if (c.dir == 3)n.dir = 4;
					else if (c.dir == 4)n.dir = 3;
					MS[k] = n;//��ġ ����
				}
			}//if ��(���� ���� �˻�)
			else MS[k] = n;
		}//for�� ��
		sort(MS.begin(), MS.end(), cmp);//����
		// �ߺ� ��ġ �ֵ� ó���ϱ�
		for (int i = 0; i < MS.size() - 1; i++) {
			if (MS.size() == 0)break;
			int cnt = 0;//�ߺ� ���� Ȯ��
			int Max = MS[i].k;//�ߺ��Ǵ°��� �ִ밪
			int MaxDir = MS[i].dir;//�ߺ��Ǵ°����� �ִ��� ����
			int sum = MS[i].k;
			for (int j = i + 1; j < MS.size(); j++) {
				if (MS.size() == 0)break;
				if (MS[i].y == MS[j].y&&MS[i].x == MS[j].x) {
					cnt++;
					sum += MS[j].k;//�̻��� ���� ���ϱ�
					if (Max < MS[j].k) {//�ִ븦 ���� ���� ���� ���ϱ�
						Max = MS[j].k;
						MaxDir = MS[j].dir;
					}
				}
				else break;//�ߺ����� ������ ����
			}
			if (cnt != 0) {//���� ��ġ�� �ִ� ���� ������
				MS.erase(MS.begin() + i + 1, MS.begin() + i + cnt + 1);
				MS[i].k = sum;//���� ����
				MS[i].dir = MaxDir;//�ִ��� ���� ���� ����
			}
		}
	}//for�� �� �ݸ��ð�
	for (int i = 0; i < MS.size(); i++) {
		ret += MS[i].k;
	}
	return;
}
int main(void) {
	int T;//�׽�Ʈ ���̽�
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}