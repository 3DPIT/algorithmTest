#include<iostream>
#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;
#define HSIZE 16
#define WSIZE 13
int dy[] = { -1,1,0,0 };//상하좌우 
int dx[] = { 0,0,-1,1 };
int H, W;//높이, 너비
int N;//벽돌깨는 개수
int input[HSIZE][WSIZE];//입력으로 받는 배열
int ret;//결과 값 저장
void print(int arr[HSIZE][WSIZE]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << input[i][j]<<" ";
		}
		cout << '\n';
	}
}
struct Data {
	int y, x,num;//좌표값만 표시
};
bool safe(int y, int x) {
	return 0 <= y && y < H && 0 <= x && x < W;
}
void init() {
	N = W = H = 0;
	ret = 0x7fffffff;//최소값 도출
	memset(input, 0, sizeof(input));
	scanf("%d %d %d", &N, &W, &H);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d", &input[i][j]);
		}
	}
}
void copy(int ci[HSIZE][WSIZE], int in[HSIZE][WSIZE]) {
	for (int i = 0; i < H; i++) {//배열 미리 복사나 백업
		for (int j = 0; j < W; j++) {
			ci[i][j] = in[i][j];
		}
	}
}
void downArr() {//배열 내리기
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
void blockBreak(int idx) {//벽돌 깨기
	int y = 0 ; int x = idx;
	for (int i = 0; i<H; i++) {
		if (input[i][x] != 0) {
			y = i; break;//벽돌 위치 찾기
		}
	}
	queue<Data>q;
	q.push({ y,x,input[y][x]});
	int visit[HSIZE][WSIZE] = { 0, };// 큐 중복 체크
	visit[y][x] = 1;
	while (!q.empty()) {//벽돌 제거 부분 
		Data c = q.front(); q.pop();
		for (int dir = 0; dir < 4; dir++) {//방향 선정
			for (int p = 1; p < c.num; p++) {
				Data n;
				n.y = c.y + (dy[dir] * p);//거리 계산
				n.x = c.x + (dx[dir] * p);
				n.num = input[n.y][n.x];
				if (safe(n.y,n.x)&&input[n.y][n.x] != 0&&visit[n.y][n.x]==0) {
					visit[n.y][n.x] = 1;//방문 체크
					input[n.y][n.x] = 0;
					q.push(n);
				}
			}
		}
		input[c.y][c.x] = 0;
	}
	// print(input);//확인 배열
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
		ret = ret > cnt ? cnt : ret;//최소값
		return;
	}
	int cinput[HSIZE][WSIZE] = { 0, };//복사 배열
	for (int i = 0; i < W; i++) {
		copy(cinput, input);//배열 백업
		blockBreak(i);
		dfs(i, d + 1);
		copy(input, cinput);//배열 복원
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}