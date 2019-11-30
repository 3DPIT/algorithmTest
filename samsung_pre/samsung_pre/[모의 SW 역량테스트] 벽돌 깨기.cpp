#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
using namespace std;
#define NS 16
#define MS 13
int N, M, K;
int ret;
int nMin = 0x7fffffff;
int input[NS][MS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
void cntZero() {//벽돌개수 확인 함수
	ret = 0;//ret 초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (input[i][j] != 0)ret++;
		}
	}
}
void copy(int cinput[NS][MS], int input[NS][MS]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cinput[i][j] = input[i][j];
		}
	}
}
void downBlock() {
	for (int x = 0; x < M; x++) {
		vector<int>v;
		for (int y = 0; y < N; y++) {
			if (input[y][x] != 0) {
				v.push_back(input[y][x]);
				input[y][x] = 0;
			}
		}
		int Y = N - 1;
		while(!v.empty()){
			input[Y][x] = v.back();
			v.pop_back();
			Y--;
		}
	}
}
struct Data {
	int y, x;
};
bool safe(int y, int x) {
	if (0 <= y && y < N && 0 <= x && x < M)return true;
	else return false;
}
void breakBlock(int xIdx) {
	int y = 0;
	while (1) {
		if (y >= N) return;
		if (input[y][xIdx]!=0)break;
		y++;
	}//블록의 위치 찾기
	queue<Data>q;
	q.push({ y,xIdx });
	int chk[NS][MS] = { 0,};
	chk[y][xIdx] = 1;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		int C = input[c.y][c.x];
		input[c.y][c.x] = 0;
		for (int cc = 1; cc <=C; cc++) {
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + (dy[dir] * (cc - 1)); n.x = c.x + (dx[dir] * (cc - 1));
				if (safe(n.y, n.x) && chk[n.y][n.x] == 0) {
					chk[n.y][n.x] = 1;
					q.push(n);
				}
			}
		}

	}
	downBlock();
}
void dfs(int idx) {//공 위치 선정
	if (idx == K) {

		cntZero();
		nMin = nMin > ret ? ret : nMin;
		return;
	}
	for (int i = 0; i < M; i++) {
		int cinput[NS][MS] = { 0, };
		copy(cinput, input);
		breakBlock(i);
		dfs(idx + 1);
		copy(input, cinput);
	}
}
void init() {
	nMin = 0x7fffffff;
	memset(input, 0, sizeof(input));
	cin >> K >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> input[i][j];
		}
	}
	dfs(0);
}
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		cout << "#" << tc << " " << nMin << endl;
	}
	return 0;
}