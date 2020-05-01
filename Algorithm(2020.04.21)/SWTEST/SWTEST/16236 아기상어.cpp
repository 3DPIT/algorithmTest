#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
#include<queue>
using namespace std;
#define NS 21
int N, ret;
int map[NS][NS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, d;
};
queue<Data>q;
void init() {
	//초기화
	while (!q.empty())q.pop();
	N = ret = 0;
	memset(map, 0, sizeof(map));

	//시작
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				q.push({ i,j,0 });
				map[i][j] = 0;
			}
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		int minD, minY, minX;

		int size = 2;
		int eat = 0;
		while (1) {
			int visit[NS][NS] = { 0, };
			minD = minY = minX = 0x7fffffff;
			while (!q.empty()) {
				Data c = q.front(); q.pop();
				if (minD < c.d)break;// 그이상것 돌면 종료
				if (map[c.y][c.x] != 0 && map[c.y][c.x] < size) {
					if (minD > c.d) {
						minD = c.d;
						minY = c.y;
						minX = c.x;
					}
					else if (minD == c.d) {
						if (minY > c.y) {
							minY = c.y;
							minX = c.x;
						}
						else if (minY == c.y&&minX > c.x) {
							minX = c.x;
							minY = c.y;
						}
					}
				}// 최소 뽑기

				for (int dir = 0; dir < 4; dir++) {
					Data n;
					n.y = c.y + dy[dir];
					n.x = c.x + dx[dir];
					n.d = c.d + 1;
					if (map[n.y][n.x] <= size && safe(n.y, n.x)
						&& visit[n.y][n.x] == 0) {
						visit[n.y][n.x] = 1;
						q.push(n);
					}
				}


			}// q 마지막칸
			//cout << "minD   " << minD << "minY  " << minY << "minX   " << minX << endl;
			if (minD == 0x7fffffff) {//먹을 물고기 없으면
				break;
			}
			else {//먹을수 있으면 
				ret += minD;
				eat++;
				if (eat == size) {//자기 크기만큼 먹으면 증가
					eat = 0;
					size++;
				}
				while (!q.empty()) 	q.pop();
				map[minY][minX] = 0;
				q.push({ minY,minX,0 });
			}
		}
		cout << ret << endl;
	}
	return 0;
}