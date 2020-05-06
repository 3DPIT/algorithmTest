#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include<string>
#include<queue>
#include<iostream>
using namespace std;
#define NS 22
int N;
int A[NS][NS];
int map[NS][NS];
int ret;
int visit[NS][NS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int cnt = 0; int Max = 0x8000000;
int Min = 0x7fffffff;
void print(string n, int idx) {
	cout << n << endl;
	if (idx == 0) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				printf("%2d", map[i][j]);
			}
			printf("\n");
		}
	}
	if (idx == 1) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				printf("%2d", visit[i][j]);
			}
			printf("\n");
		}
	}
}
void init() {
	N = 0;
	ret = 0x7fffffff;
	memset(A, 0, sizeof(A));
	memset(map, 0, sizeof(map));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}
}
bool safe(int y, int x) {
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
struct Data {
	int sum, cnt;
};
struct data1 {
	int y, x;
};
void five(int y, int x, int d1, int d2) {
	vector<data1>v1;
	vector<data1>v2;
	for (int i = y, j = x; i < y + d1, j > x - d1; i++, j--) {
		v1.push_back({ i,j });
	}

	for (int i = y, j = x; j < x + d2, i < y + d2; j++, i++) {
		v2.push_back({ i,j });
	}

	for (int i = y + d1, j = x - d1; j <= x - d1 + d2, i <= y + d1 + d2; j++, i++) {
		v1.push_back({ i,j });
	}


	for (int i = y + d2, j = x + d2; j >= x + d2 - d1, i <= y + d2 + d1; j--, i++) {
		v2.push_back({ i,j });
	}
	int sum = 0;
	for (int i = 0; i < v1.size(); i++) {
		for (int y = v1[i].y; y <= v2[i].y; y++) {
			for (int x = v1[i].x; x <= v2[i].x; x++) {
				if(safe(y,x))
				map[y][x] = 5;

			}

		}
	}
	Max = Max < sum ? sum : Max;
	Min = Min > sum ? sum : Min;
}

void dfs(int y, int x) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (safe(ny, nx) && visit[ny][nx] == 0 && map[ny][nx] == 0) {
			visit[ny][nx] = cnt;
			dfs(ny, nx);

		}
	}
}
void fivedfs()
{
	cnt = 0;
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			if (map[i][j] == 0 && visit[i][j] == 0) {
				visit[i][j] = ++cnt;
				dfs(i, j);
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 5) {
				visit[i][j] = 2;
			}
		}
	}



}
Data v[6];

int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;
void one(int x, int y, int d1, int d2) {
	f1 = f2 = f3 = f4 = f5 = 0;
	int sum = 0;
	for (int i = 1; i < x + d1; i++) {
		for (int j = 1; j <= y; j++) {
			if (map[i][j] == 0 && safe(i, j)) {
				if (f1 == 0)f1 = 1;
				map[i][j] = 1;
				sum += A[i][j];
			}
		}
	}
	Max = Max < sum ? sum : Max;
	Min = Min > sum ? sum : Min;
}
void two(int x, int y, int d1, int d2) {
	int sum = 0;
	for (int i = 1; i <= x + d2; i++) {
		for (int j = y + 1; j <= N; j++) {
			if (map[i][j] == 0 && safe(i, j)) {
				if (f2 == 0)f2 = 1;

				map[i][j] = 2;
				sum += A[i][j];
			}
		}
	}
	Max = Max < sum ? sum : Max;
	Min = Min > sum ? sum : Min;
}
void tree(int x, int y, int d1, int d2) {
	int sum = 0;
	for (int i = x + d1; i <= N; i++) {
		for (int j = 1; j < y - d1 + d2; j++) {
			if (map[i][j] == 0 && safe(i, j)) {
				if (f3 == 0)f3 = 1;
				map[i][j] = 3;
				sum += A[i][j];
			}
		}
	}
	Max = Max < sum ? sum : Max;
	Min = Min > sum ? sum : Min;
}
void four(int x, int y, int d1, int d2) {
	int sum = 0;
	for (int i = x + d2 + 1; i <= N; i++) {
		for (int j = y - d1 + d2; j <= N; j++) {
			if (map[i][j] == 0 && safe(i, j)) {
				if (f4 == 0)f4 = 1;
				map[i][j] = 4;
				sum += A[i][j];
			}
		}
	}
	Max = Max < sum ? sum : Max;
	Min = Min > sum ? sum : Min;
}
void clac() {
	int num[6] = { 0, };
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			num[map[i][j]] += A[i][j];
		}
	}
	int min = 0x7fffffff; int max = 0x80000000;
	for (int i = 0; i <= 5; i++) {
		if (i == 0 & num[i] != 0)return;
		if (i != 0 && num[i] == 0)return;
	}
	for (int i = 1; i <= 5; i++) {
		if (min > num[i])min = num[i];
		if (max < num[i])max = num[i];
	}
	//for (int i = 1; i <= N; i++) {
	//	for (int j = 1; j <= N; j++) {
	//		cout << chk[i][j];
	//	}
	//	cout << endl;
	//}
	//cout << max - min << endl;
	if (ret > max - min)ret = max - min;
}
void elect() {
	for (int d1 = 1; d1 <= N; d1++) {
		for (int d2 = 1; d2 <= N; d2++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					memset(v, 0, sizeof(v));
					memset(map, 0, sizeof(map));
					five(i, j, d1, d2);
					one(i, j, d1, d2);
					two(i, j, d1, d2);
					tree(i, j, d1, d2);
					four(i, j, d1, d2);
					clac();
									
					Min = 0x7fffffff;
					Max = 0x80000000;

				}
			}
		}
	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		elect();

		//printf("%d %d\n", t, ret);
		printf("%d\n", ret);
	}
	return 0;
}