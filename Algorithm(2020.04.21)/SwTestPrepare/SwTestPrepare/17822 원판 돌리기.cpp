#include<stdio.h>
#include<string.h>
using namespace std;
#define NS 52
int N, M, T;
int map[NS][NS];
int chk[NS][NS];
int flag = 0;
int dFlag = 0;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int ret = 0;
struct CircleRotation {
	CircleRotation() {
		scanf("%d %d %d", &N, &M, &T);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		for (int ti = 0; ti < T; ti++) {
			int num, dir, cnt;
			scanf("%d %d %d", &num, &dir, &cnt);
			Rotation(num, dir, cnt);

		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				ret += map[i][j];
			}
		}
		printf("%d\n", ret);
	}
	void Rotation(int num, int dir, int cnt)
	{
		for (int i = 1; i <= N; i++) {
			if (i%num == 0) {
				if (dir == 0) {
					for (int cnti = 0; cnti < cnt; cnti++)//줄일 수 있음
						clock(i - 1);
				}
				else {
					for (int cnti = 0; cnti < cnt; cnti++)//줄일 수 있음
						reclock(i - 1);
				}
			}
		}
		pDfs();
		if (dFlag == 0) {
			sumArr();
		}
			dFlag = 0;
	}
	void sumArr() {
		int sum = 0;
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] != 0) {
					sum += map[i][j];
					cnt++;
				}
			}
		}
		float dsum = 0;
		if (sum != 0)
			dsum = (float)sum / cnt;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j]!=0&&map[i][j] < dsum)map[i][j]++;
				else if (map[i][j] != 0 && map[i][j] > dsum)map[i][j]--;
			}
		}
	}
	void pDfs() {
		memset(chk, 0, sizeof(chk));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (chk[i][j] == 0) {
					chk[i][j] = 1;
					int num = map[i][j];
					if (num != 0) {
						dfs(i, j, num);
						
					}
					if (flag == 1) {
						dFlag = 1;
						map[i][j] = 0;
					}
					chk[i][j] = 0;
					flag = 0;
				}
			}
		}
	}
	void dfs(int y, int x, int num) {
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (0 > ny)continue;
			if (0 > nx)nx = M - 1;
			if (ny >= N)continue;
			if (nx >= M)nx = 0;
			if (map[ny][nx]!=0&&chk[ny][nx] == 0 && map[ny][nx] == num) {
				flag = 1;
				chk[ny][nx] = 1;
				map[ny][nx] = 0;
				dfs(ny, nx,num);
			}
		}
	}
	void reclock(int idx) {
		int num = map[idx][0];
		for (int i = 1; i < M; i++) {
			map[idx][i-1] = map[idx][i];
		}
		map[idx][M-1] = num;
	}
	void clock(int idx) {
		int num = map[idx][M-1];
		for (int i = M-2; i >=0; i--) {
			map[idx][i + 1] = map[idx][i];
		}
		map[idx][0] = num;
	}
}ca;
int main(void) {
	//CircleRotation ca;

	return 0;
}