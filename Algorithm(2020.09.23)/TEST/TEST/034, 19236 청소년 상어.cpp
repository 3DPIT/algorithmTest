//20.10.17 ����� û�ҳ� ���
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
#define BS 6//�� ������
int ret;
int dy[] = {0,-1,-1,0,1,1,1,0,-1 };//����
int dx[] = {0,0,-1,-1,-1,0,1,1,1 };
struct Data1 {
	int y, x, num, dir;
};
Data1 fish[17]; int B[4][4];//�Է� ������

bool safe(int y, int x) {//���� üũ
	return 0 <= y && y <4 && 0 <= x && x <4;
}
bool isafe(int y, int x) {
	return 0 > y || y == 4 || x < 0 || x == 4;
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	ret = 0x80000000;//�ּҰ�
	memset(B, 0, sizeof(B));
	memset(fish, 0, sizeof(fish));
	
	//�ʱ� �Է�
	for (int i = 0; i <4; i++) {
		for (int j = 0; j < 4; j++) {
			int num, dir;
			scanf("%d %d", &num, &dir);
			B[i][j]= num; //�迭�� ��ȣ ���� ǥ��
			fish[num].y = i; fish[num].x = j;
			fish[num].num = num; fish[num].dir = dir;
		}
	}
}
void copy(int c[4][4], int b[4][4]) {//�迭 ī��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <4; j++) {
			c[i][j] = b[i][j];
		}
	}
}
void copy1(Data1 cf[16], Data1 f[16]) {//����� ���� ī��
	for (int i = 1; i <= 16; i++) {
		cf[i] = f[i];
	}
}
void fishMove(int y, int x) {
	for (int i = 1; i <= 16; i++) {
		if (fish[i].y == -1)continue;
		//�� �ְų� ����� ���
		Data1 c = fish[i];
		Data1 n; n.dir = c.dir;
		n.y = c.y + dy[c.dir]; n.x = c.x + dx[c.dir];
		while (!safe(n.y, n.x) || (y == n.y&&x == n.x)) {
			n.dir++;
			if (n.dir == 9)n.dir = 1;
			n.y = c.y + dy[n.dir]; n.x = c.x + dx[n.dir];
		}
		//�ٸ� ����Ⱑ �ִ� ���
		if (B[n.y][n.x] != -1) {
			int t = B[n.y][n.x];
			fish[t].y = c.y; fish[t].x = c.x;
			fish[i].y = n.y; fish[i].x = n.x; fish[i].dir = n.dir;
			B[c.y][c.x] = t;
			B[n.y][n.x] = i;
		}
		//��ĭ�� ���
		else {
			fish[i].y = n.y; fish[i].x = n.x; fish[i].dir = n.dir;
			B[c.y][c.x] = -1;
			B[n.y][n.x] = i;
		}
	}
}
int eat(int y,int x) {
	int a = B[y][x];
	fish[B[y][x]].num = -1;
	fish[B[y][x]].dir = -1;
	fish[B[y][x]].x = -1;
	fish[B[y][x]].y = -1;
	B[y][x] = -1;
	return a;
}
void dfs(int y, int x, int sum) {

	//1. ����� ����� �Ա�
	int sharkD = fish[B[y][x]].dir;
	//���� ����� ǥ��
	sum +=eat(y,x);//���� ����� ��
	ret = max(ret, sum);
	//2. ������� �̵�
	fishMove(y,x);
	//3. ����� �̵�
	for (int nd = 1; nd < 4; nd++) {
		Data1 n; 
		n.y = y + dy[sharkD]*nd; n.x = x + dx[sharkD]*nd;
		n.dir = sharkD;
		if (safe(n.y, n.x) &&B[n.y][n.x] != -1) {
			int cB[4][4] = { 0, };
			Data1 cfish[17] = { 0, };
			copy(cB, B);
			copy1(cfish, fish);
			dfs(n.y, n.x, sum);
			copy1(fish, cfish);
			copy(B, cB);
		}
	}
}
int main(void) {
	int T = 1;//�׽�Ʈ ���̽�
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ� �Է�
		dfs(0, 0, 0);
		//���
		printf("%d\n", ret); //printf("#%d %d\n", tc, ret);
	}
	return 0;
}