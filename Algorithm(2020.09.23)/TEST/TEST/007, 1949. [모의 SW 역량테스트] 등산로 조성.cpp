#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define NSIZE 8 //�Է����� �־����� �迭 �ִ�ũ��
int N, K;//���� �� ���Ǳ���, �ִ� ���� ���� ����
int mountain[NSIZE][NSIZE];//�Է����� �־����� �迭
int ret;//���� �ִ밪 ����
int maxMT;//�ְ� ���츮
int maxCnt;//�ִ� �����մ� ����
int visit[NSIZE][NSIZE];//Ž���� üũ�� �迭
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
bool safe(int y, int x) {//�迭 �Ѿ�°� üũ
	return 0 <= y && y < N && 0 <= x && x < N;
}
void init() {//�ʱ�ȭ
	N = K = 0;
	ret = maxMT=maxCnt = 0x80000000;
	memset(mountain, 0, sizeof(mountain));
	memset(visit, 0, sizeof(visit));
}
void dfs(int y, int x,int cnt) {//Ž�� ����
	
	for (int dir = 0; dir < 4; dir++) {
		if (safe(y+dy[dir],x+dx[dir])&&visit[y+dy[dir]][x+dx[dir]]==0&&mountain[y][x] > mountain[y + dy[dir]][x + dx[dir]]) {//������ ������ ã��
			//���� �ȳѾ�ų� �湮�������ų� ���纸�� �������
			visit[y + dy[dir]][x + dx[dir]] = 1;
			maxCnt = max(maxCnt, cnt+1);
			dfs(y + dy[dir], x + dx[dir],cnt+1);
			visit[y + dy[dir]][x + dx[dir]] = 0;
		}
	}
}
void hiking() {//�Է��ϰ� �˰��� ����
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++) {//�Է��ϸ鼭
		for (int j = 0; j < N; j++) {
			scanf("%d", &mountain[i][j]);
			if (maxMT < mountain[i][j]) {
				maxMT = max(maxMT, mountain[i][j]);//�ִ밪 ����
			}
		}
	}
	for (int cy = 0; cy < N; cy++) {
		for (int cx = 0; cx < N; cx++) {
			if (mountain[cy][cx] == maxMT) {//�ְ� ���츮 ã��
				for (int y = 0; y < N; y++) {
					for (int x = 0; x < N; x++) {
						
						for (int k = 0; k <= K; k++) {//���츮 �ٿ��� Ž���ϱ�
							memset(visit, 0, sizeof(visit));//�湮 �迭 �ʱ�ȭ
							mountain[y][x] -= k;//���츮 ũ�� 1�� ���̱�
							dfs(cy, cx,1);
							ret = max(ret, maxCnt);
							mountain[y][x] += k;//�ٽ� �����ϱ�
						}//for k

					}//for x
				}//for y
			}
		}//for cx
	}//for cy
}
int main(int argc, char** argv)
{
	int T;
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case)
	{
		init();
		hiking();//��� ����
		printf("#%d %d\n", test_case, ret);
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}