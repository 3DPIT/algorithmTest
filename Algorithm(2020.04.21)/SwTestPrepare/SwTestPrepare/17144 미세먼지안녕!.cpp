#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;
#define NS 51
int R, C, T;
int map[NS][NS];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int ret = 0;
struct Data {
	int y, x;
};
vector<Data>airCleaner;
void dustprint() {
	printf("미세먼지 퍼진후 맵상태\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}
}
void cdirprint() {
	printf("시계방향 이동후 맵상태\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}
}
void rcdirprint() {
	printf("반시계방향 이동후 맵상태\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}
}
struct CleanAir {
	CleanAir() {
		int Ts = 1;
		for (int ti = 1; ti <= Ts; ti++) {
			init();
			scanf("%d %d %d", &R, &C, &T);
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					scanf("%d", &map[i][j]);

					if (map[i][j] == -1) {
						airCleaner.push_back({ i,j });
					}
				}
			}
			for (int Ti = 0; Ti < T; Ti++) {
				spread();
			//	dustprint();//퍼진것 출력확인
				clockDir(airCleaner[0].y - 1, airCleaner[0].x);
				map[airCleaner[0].y][airCleaner[0].x + 1] = 0;
			//	cdirprint();//시계 출력 확인
				reClockDir(airCleaner[1].y + 1, airCleaner[1].x);
				map[airCleaner[1].y][airCleaner[1].x + 1] = 0;
			//	rcdirprint();//반시계 출력확인
			}
			sum();
			//printf("#%d %d\n", ti, ret);
			printf("%d\n", ret);
		}
	}
	void init() {
		memset(map, 0, sizeof(map));
		R = C = T=0;
		ret = 0;
	}
	void sum() {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (map[i][j] != -1) {
					ret += map[i][j];
				}
			}
		}
	}
	void spread() {
		int cmap[NS][NS] = { 0, };
		for (int i = 0; i < R; i++) {//확산 시키기
			for (int j = 0; j < C; j++) {
				if (map[i][j] != 0) {
					int dust = map[i][j] / 5;
					int dustCnt = 0;
					for (int dir = 0; dir < 4; dir++) {
						int ny = i - dy[dir];
						int nx = j - dx[dir];
				
						if (map[ny][nx] != -1 && safe(ny, nx)) {
							dustCnt++;
							cmap[ny][nx] += dust;
						}
						if (dir == 3) {

							map[i][j] = map[i][j] - (dust*dustCnt);
						}
					}
				}
			}
		}

		for (int i = 0; i < R; i++) {//확산저장
			for (int j = 0; j < C; j++) {
				map[i][j] += cmap[i][j];
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < R && 0 <= x && x < C;
	}
	void clockDir(int y,int x) {
		int fy = y; int fx = x;
		int flag = 0;
		int dir = 0;
		while (1) {
			int ny = y +dy[dir];
			int nx = x +dx[dir];
			if (flag == 1 && dir == 0) {//탈출 조건
				break;
			}
			if (0<=ny&&ny<=fy+1&&0<=nx&&nx<C) {
				map[y][x] = map[ny][nx];
			}
			else {
				flag = 1;
				ny-= dy[dir]; nx -= dx[dir];
				dir++;
				if (dir == 4)dir = 0;
			}
			y = ny; x = nx;
		}
	}
	void reClockDir(int y, int x) {
		int fy = y; int fx = x;
		int flag = 0;
		int dir = 2;
		while (1) {
			int ny = y +dy[dir];
			int nx = x + dx[dir];
			if (flag == 1 && dir == 2) {//탈출 조건
				break;
			}
			if (fy-1<=ny&&ny<R&&0<=nx&&nx<C) {
				map[y][x] = map[ny][nx];
			}
			else {
				flag = 1;
				ny -=dy[dir]; nx -= dx[dir];
				dir--;

				if (dir == -1)dir = 3;
			}
			y = ny; x = nx;
		}
	}
}CleanAir;
int main(void) {

	return 0;
}