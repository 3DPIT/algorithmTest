#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
using namespace std;
#define NS 9
#define MS 9
int map[NS][MS];
int N, M;
int Min;
int cctvDirCnt[] = { 0,4,2,4,4,1 };
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, num;
};
vector<Data>CCTV;
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
void cctvPaint(int dir,Data cctv) {
	int y = cctv.y;
	int x = cctv.x;
	while (1) {
		y += dy[dir];
		x += dx[dir];
		if(safe(y,x)&&map[y][x]!=6){
		map[y][x] = 9;//감시범위
		}
		else {
			break;
		}
	}
}
void copy(int cmap[NS][MS],int map[NS][MS]) {
	for (int i = 0; i < NS; i++) {
		for (int j = 0; j < MS; j++) {
			cmap[i][j] = map[i][j];
		}
	}
}
int zeroCnt() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0)cnt++;
		}
	}
	return cnt;
}
void print(string name, int idx, int cnt, int i) {
	cout << name << endl;
	if (i == 1) {
		cout << "인덱스" << idx << "  cctv범위그린 수" << cnt << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				printf("%2d", map[i][j]);
			}
			printf("\n");
		}
	}
}
void dfs(int idx, int cnt) {
	if (cnt == CCTV.size()) {
		//최소값 구하기
	//	print("맵정보", idx, cnt, 1);
		int cnt = zeroCnt();
		//cout << cnt << endl;
		Min = Min > cnt ? cnt : Min;
		zeroCnt();
		return;
	}
	//print("맵정보", idx, cnt,1);
		for (int j = 0; j < cctvDirCnt[CCTV[idx].num]; j++) {
			int cmap[NS][MS] = { 0, };
			copy(cmap, map);
			if (CCTV[idx].num == 1) {
				cctvPaint(j,CCTV[idx]);
				dfs(idx + 1, cnt + 1);
			}
			else if (CCTV[idx].num == 2) {
				cctvPaint(j,CCTV[idx]);
				cctvPaint((j+2)%4, CCTV[idx]);
				dfs(idx + 1, cnt + 1);

			}
			else if (CCTV[idx].num == 3) {
				cctvPaint(j, CCTV[idx]);
				cctvPaint((j + 3) % 4, CCTV[idx]);
				dfs(idx + 1, cnt + 1);
			}
			else if (CCTV[idx].num == 4) {
				cctvPaint(j, CCTV[idx]);
				cctvPaint((j + 2) % 4, CCTV[idx]);
				cctvPaint((j + 3) % 4, CCTV[idx]);
				dfs(idx + 1, cnt + 1);
			}
			else if (CCTV[idx].num == 5) {
				cctvPaint(j, CCTV[idx]);
				cctvPaint(j+1, CCTV[idx]);
				cctvPaint(j+2, CCTV[idx]);
				cctvPaint(j+3, CCTV[idx]);
				dfs(idx + 1, cnt + 1);
			}
			copy(map, cmap);
		
	}
}
void init() {
	N = M = 0;
	Min = 0x7fffffff;
	CCTV.clear();
	memset(map, 0, sizeof(map));
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] != 0&&map[i][j]!=6)CCTV.push_back({ i,j,map[i][j] });
		}
	}
}
int main(void) {
	int T = 6;
	for (int t = 1; t <= T; t++) {
		init();
		dfs(0, 0);
		printf("#%d %d\n", t,Min);
		//printf("%d", Min);
	}
	return 0;
}