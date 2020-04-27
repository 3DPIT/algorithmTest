#include<stdio.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<string>
#include<queue>
using namespace std;
#define NS 51
int N, M;
int map[NS][NS];
int chk[NS];
int visit[NS][NS];
int Min = 0x7fffffff;
int Max = 0x80000000;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x, cnt;
};
vector<Data>virus;//함수 - 바이러스 수집
vector<int>virusIdx;
void allPrint(string name) {
	if (name == "전체맵출력") {
		cout << name << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%2d", map[i][j]);
			}
			printf("\n");
		}
	}
	else if (name == "조합출력")
	{
		cout << name << endl;
		for (int i = 0; i < virusIdx.size(); i++) {
			printf("%2d", virusIdx[i]);
		}
		printf("\n");

	}
	else if (name == "큐돌고방문배열") {
		cout << name << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%2d", visit[i][j]);
			}
			printf("\n");
		}
	}

}

struct Virus {
	Virus() {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 2) {
					virus.push_back({ i, j });
				}
			}
		}//전체 맵 입력


		virusDfs(0, 0);//함수 - 수집 바이러스 M개 뽑아내는 dfs
		if (Min == 0x7fffffff)printf("-1\n");
		else {
			if (Min != 0)Min--;
			printf("%d\n", Min);//출력 - 최종 결과 출력
		}
	}
	void init() {//초기화
		virus.clear();
		virusIdx.clear();
		memset(map, 0, sizeof(map));
		Max = 0x80000000;
		Min = 0x7fffffff;
	}
	int bfs() {
		memset(visit, 0, sizeof(visit));
		queue<Data>q;
		for (int i = 0; i < virusIdx.size(); i++) {
			q.push({ virus[virusIdx[i]].y,virus[virusIdx[i]].x,1 });
			visit[virus[virusIdx[i]].y][virus[virusIdx[i]].x] = 1;
		}
		while (!q.empty())
		{
			Data c = q.front(); q.pop();
			for (int dir = 0; dir < 4; dir++) {
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				n.cnt = c.cnt + 1;
				if (safe(n.y, n.x) && visit[n.y][n.x] == 0 && map[n.y][n.x] != 1) {

					visit[n.y][n.x] = n.cnt;
					q.push(n);

				}
			}
		}
		return chkMap();
	}
	int chkMap() {
		Max = 0x80000000;
		int flag = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 1 && visit[i][j] == 0) {
					return -1;
				}
				else if (map[i][j] != 1) {
					flag = 1;
					Max = Max < visit[i][j] ? visit[i][j] : Max;
				}
			}
		}
		if (flag)
			return Max;
		else
			return 0;
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < N;
	}
	void virusDfs(int idx, int d) {
		if (virusIdx.size() == M) {// 뽑았으면
			//allPrint("조합출력");
			int ret = bfs();//함수 - bfs바이러스 전파
			//allPrint("큐돌고방문배열");
			//allPrint("ret");
			//cout << ret << endl;
			if (ret != -1) {
				Min = Min > ret ? ret : Min;
			}
			return;
		}
		for (int i = d; i < virus.size(); i++) {
			if (chk[i] == 0) {
				chk[i] = 1;
				virusIdx.push_back(i);
				virusDfs(idx + 1, i);
				virusIdx.pop_back();
				chk[i] = 0;
			}
		}
	}
}Virus;
int main(void) {

	return 0;
}