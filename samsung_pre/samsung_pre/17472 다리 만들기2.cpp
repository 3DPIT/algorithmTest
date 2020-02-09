#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define MAP_S 11
int N, M, numIsland,map[MAP_S][MAP_S];
int num[7] = { 0, };
int chk[MAP_S][MAP_S];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
vector<int>D;
vector<int>G[7];
int Min = 0x7fffffff;
struct Data {
	int y, x, cnt;
};
bool cmp(Data a, Data b) {
	if (a.y == b.y)return a.x < b.x;
	return a.y < b.y;
}
vector<Data>v;
struct makeIsland {
	makeIsland() {// 초기화 진행
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &map[i][j]);
			}
		}
	}
	void dfs(int idx) {
		for (int i = 0; i < G[idx].size(); i++) {
			if (num[G[idx][i]] ==0 ) {
				num[G[idx][i]] = 1;
				dfs(G[idx][i]);
			}
		}
	}
	void dfs1(int idx, int sum) {
		if (idx == v.size()){
			for (int i = 0; i <D.size() ; i++) {
				cout << D[i] << " ";
			}
			cout << endl;
			for (int i = 0; i < 7; i++) {
				G[i].clear();
			}//그래프 초기화
			sum = 0;
			for (int i = 0; i < D.size(); i++) {
				G[v[D[i]].y].push_back(v[D[i]].x);//그래프 연결
				sum += v[D[i]].cnt;
			}

			if (connectG()) {

				if (Min > sum)Min = sum;
			}
			return;
		}
		D.push_back(idx);
		dfs1(idx + 1, sum + v[idx].cnt);

		D.pop_back();
		dfs1(idx + 1, sum);

	}
	void dfs(int y, int x) {//섬 번호 매기는 dfs
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (map[ny][nx] == 1 && chk[ny][nx] == 0) {
				chk[ny][nx] = numIsland;
				map[ny][nx] = numIsland;
				dfs(ny, nx);
			}
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < M;
	}
	bool connectG() {
		memset(num, 0, sizeof(num));
		int c = 0;
		for (int i = 1; i <= numIsland; i++) {
			if (num[i] == 0) {
				num[i] = 1;
				c++;
				dfs(i);
			}
		}
		if (c == 1)return true;
		else return false;
	}
	
	void make(int y, int x,int d,int cnt) {
		int num = map[y][x];
		int ny = y + dy[d];
		int nx = x + dx[d];
		while (1) {
			if (!safe(ny, nx)) return ;
			else if (map[ny][nx] == 0) {
				cnt++;
			}
			else if (map[ny][nx] == num)return;
			else if (map[ny][nx] != num ) {
				if (map[ny][nx] != 0 && cnt >= 2) {
					v.push_back({ num,map[ny][nx],cnt });
					v.push_back({ map[ny][nx],num,cnt });
				}
				else {
					return;
				}
				return;
			}
			ny += dy[d];
			nx += dx[d];
		}
	}
	void numbering() {//섬에 번호 매기기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 1 && chk[i][j] == 0) {
					numIsland++;
					map[i][j] = numIsland;
					chk[i][j] = numIsland;
					dfs(i, j);
				}
			}
		}
	}
	void connectIsland() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] != 0) {
					for (int dir = 0; dir < 4; dir++) {
						make(i, j, dir, 0);
					}
				}
			}
		}
	}

	void deleteDouble() {

		sort(v.begin(), v.end(),cmp);// 순서 정렬
		for (int i = 0; i < v.size()-1; i++) {
			if (v.size() == 0)return;
			Data a = v[i];
			int cnt = a.cnt;
			for (int j = i+1; j < v.size(); j++) {
				if (v.size() == 0)return;
				Data b = v[j];
				if (a.y == b.y&&a.x == b.x) {
					if (cnt > b.cnt)cnt = b.cnt;
					v.erase(v.begin() + j);
					j--;
				}
				else {
					v[i].cnt = cnt;
					break;
				}
			}
		}
	}
}connect;
int main(void) {
	connect.numbering();
	connect.connectIsland();
	connect.deleteDouble();
	connect.dfs1(0,0);
	if (Min == 0x7fffffff)cout << -1 << endl;
	else cout << Min << endl;
	return 0;
}