#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define S 51
int N, M, K;
int arr[S][S];
int num[7];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int Min = 0x7fffffff;
struct Data {
	int r, c, s;
};
vector<Data>v;
struct Rot {
	Rot() {
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &arr[i][j]);
			}
		}

		for (int i = 0; i < K; i++) {
			Data c;
			scanf("%d %d %d", &c.r, &c.c, &c.s);
			v.push_back({ c.r-1,c.c-1,c.s });
		}
	}
	bool safe(int yy, int xx, int y, int x, int s) {
		//현재 y, 현재 x, 기준점 y,기준점 x,(- or +) 되는 값
		int ys = y - s;
		int xs = x - s;
		int ye = y + s;
		int xe = x + s;
		return ys <= yy && yy <= ye && xs <= xx && xx <= xe;
	}
	void copy(int map[S][S], int cmap[S][S]) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cmap[i][j] = map[i][j];
			}
		}
	}
	vector<int>aa;
	void rot(int idx) {
		Data c = v[idx];
		Data s; Data e; int dir = 3;
		for (int i = 1; i <= c.s; i++) {
			s.r = c.r - i;  e.r = c.r + i;
			s.c = c.c - i;  e.s = c.c + i;
			Data n = s;
			int flag = 0;
			int num = arr[n.r][n.c];
			while (1)
			{
				if (dir == 3 && flag == 1) {
					break;
				}
					n.r = n.r - dy[dir];
					n.c = n.c - dx[dir];
					if (safe(n.r, n.c, c.r, c.c, i)) {
						arr[n.r + dy[dir]][n.c + dx[dir]] = arr[n.r][n.c];
					}
					else {
						n.r = n.r + dy[dir];
						n.c = n.c + dx[dir];
						dir--;
						if (dir == -1)dir = 3;
					}
					if(dir!=3)flag = 1;
				}
			arr[n.r+dy[0]][n.c+dx[0]] = num;
		}
	}
	int chkSum(int arr[S][S]) {
		int mmin = 0x7fffffff;
		for (int i = 0; i < N; i++) {
			int sum = 0;
			for (int j = 0; j < M; j++) {
				sum += arr[i][j];
			}
			if (mmin > sum) mmin = sum;
		}
		return mmin;
	}
	void dfs(int idx) {
		if (idx == K) {
			int num = chkSum(arr);
			if (Min > num)Min = num;
			return;
		}
		int cmap[S][S] = { 0, };
		for (int i = 0; i < K; i++) {
			if (num[i] == 0) {
				aa.push_back (i);
				num[i] = 1;
				copy(arr, cmap);
				rot(i);
				dfs(idx + 1);
				copy(cmap, arr);
				num[i] = 0;
				aa.pop_back();

			}
		}
	}
}D;
int main(void) {
	D.dfs(0);
	cout << Min << endl;
	return 0;
}