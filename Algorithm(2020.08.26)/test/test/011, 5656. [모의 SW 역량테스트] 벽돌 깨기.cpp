#include<iostream>
#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;
#define HSIZE 16
#define WSIZE 13
int dy[] = { -1,1,0,0 };//�����¿� 
int dx[] = { 0,0,-1,1 };
int H, W;//����, �ʺ�
int N;//�������� ����
int input[HSIZE][WSIZE];//�Է����� �޴� �迭
int ret;//��� �� ����
void print(int arr[HSIZE][WSIZE]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << input[i][j]<<" ";
		}
		cout << '\n';
	}
}
struct Data {
	int y, x,num;//��ǥ���� ǥ��
};
bool safe(int y, int x) {
	return 0 <= y && y < H && 0 <= x && x < W;
}
void init() {
	N = W = H = 0;
	ret = 0x7fffffff;//�ּҰ� ����
	memset(input, 0, sizeof(input));
	scanf("%d %d %d", &N, &W, &H);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d", &input[i][j]);
		}
	}
}
void copy(int ci[HSIZE][WSIZE], int in[HSIZE][WSIZE]) {
	for (int i = 0; i < H; i++) {//�迭 �̸� ���糪 ���
		for (int j = 0; j < W; j++) {
			ci[i][j] = in[i][j];
		}
	}
}
void downArr() {//�迭 ������
	for (int j = 0; j < W; j++) {
		queue<int>num;
		for (int i = H-1; i>= 0; i--) {
			if (input[i][j] != 0) {
				num.push(input[i][j]);
				input[i][j] = 0;
			}
		}
		for (int i = H - 1; !num.empty(); i--) {
			input[i][j] = num.front(); num.pop();
		}
	}
}
void blockBreak(int idx) {//���� ����
	int y = 0 ; int x = idx;
	for (int i = 0; i<H; i++) {
		if (input[i][x] != 0) {
			y = i; break;//���� ��ġ ã��
		}
	}
	queue<Data>q;
	q.push({ y,x,input[y][x]});
	int visit[HSIZE][WSIZE] = { 0, };// ť �ߺ� üũ
	visit[y][x] = 1;
	while (!q.empty()) {//���� ���� �κ� 
		Data c = q.front(); q.pop();
		for (int dir = 0; dir < 4; dir++) {//���� ����
			for (int p = 1; p < c.num; p++) {
				Data n;
				n.y = c.y + (dy[dir] * p);//�Ÿ� ���
				n.x = c.x + (dx[dir] * p);
				n.num = input[n.y][n.x];
				if (safe(n.y,n.x)&&input[n.y][n.x] != 0&&visit[n.y][n.x]==0) {
					visit[n.y][n.x] = 1;//�湮 üũ
					input[n.y][n.x] = 0;
					q.push(n);
				}
			}
		}
		input[c.y][c.x] = 0;
	}
	// print(input);//Ȯ�� �迭
	downArr();
}
void dfs(int idx, int d) {
	if (d == N) {
		int cnt = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (input[i][j] != 0)cnt++;
			}
		}
		ret = ret > cnt ? cnt : ret;//�ּҰ�
		return;
	}
	int cinput[HSIZE][WSIZE] = { 0, };//���� �迭
	for (int i = 0; i < W; i++) {
		copy(cinput, input);//�迭 ���
		blockBreak(i);
		dfs(i, d + 1);
		copy(input, cinput);//�迭 ����
	}
}
int main(void)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		dfs(0, 0);
		printf("#%d %d\n", test_case, ret);
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}