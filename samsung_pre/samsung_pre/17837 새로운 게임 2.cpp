#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
#define NS 13
#define KS 11
typedef struct Data {
	int y, x, dir,cnt;
}Data;
vector<int>horsePos[NS][NS];
vector<Data> horse[KS];
int map[NS][NS];
int N, K;
int ret;
int dy[] = { 0,0,-1,1 };
int dx[] = { 1,-1,0,0 };
struct NewGame2 {
	NewGame2() {
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);// ¸ÊÁ¤º¸
			}
		}
		for (int i = 0; i < K; i++) {
			int y, x, dir;
			scanf("%d %d %d", &y, &x, &dir);
			horsePos[y][x].push_back(i);
			horse[i + 1].push_back({ y,x,dir });//¸»À§Ä¡ ÀúÀå
		}
	}
	void white(Data c,int num) {
		while (horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].size() != 0) {
			int num1 = horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].front();
			horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].erase(horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].begin());
			horse[num1].front().y = horse[num1].front().y + dy[c.dir];
			horse[num1].front().x = horse[num1].front().x + dx[c.dir];
			horsePos[c.y][c.x].push_back(num1);
		}
	}
	void Red(Data c, int num) {
		int flag = 1;
		vector<Data>v;
		while (horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].size() != 0) {
			for (int i = 0; i < horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].size(); i++) {
				if (horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]][i]!=num&&flag) {
					flag = 0;
					continue; 
				}
				v.push_back(horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]][i]);
				int num1 = horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].back();
				horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].erase(horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].begin(),
					horsePos[c.y - dy[c.dir]][c.x - dx[c.dir]].end());
				horse[num1].front().y = horse[num1].front().y + dy[c.dir];
				horse[num1].front().x = horse[num1].front().x + dx[c.dir];
				horsePos[c.y][c.x].push_back(num1);
			}
		}
	}
	void Blue(Data c, int num) {
		if (horse[num].front().dir == 0)
			horse[num].front().dir = 1;
		else if (horse[num].front().dir == 1)
			horse[num].front().dir = 0;
		else if (horse[num].front().dir == 2)
			horse[num].front().dir = 3;
		else if (horse[num].front().dir == 3)
			horse[num].front().dir = 2;
		Data n;
		n.y = c.y + dy[horse[num].front().y];
		n.x = c.x + dx[horse[num].front().x];
		if (safe(c.y + dy[horse[num].front().y, c.x + dx[horse[num].front().x] && map[c.y + dy[horse[num].front().y]][c.x + dx[horse[num].front().x]] != 2)) {
			if (map[c.y + dy[horse[num].front().y]][c.x + dx[horse[num].front().x]] ==0){
				white(n,num);
			}
			if (map[c.y + dy[horse[num].front().y]][c.x + dx[horse[num].front().x]] ==1) {
				Red(n, num);
			}
		}

	}
	bool safe(int y, int x) {
		return (1 <= y && y <= N && 1 <= x && x < N);
	}
	void gameStart() {
		while (1) {
			for (int i = 1; i <= K; i++) {
				Data c = horse[i].front();
				Data n;
				n.y = c.y + dy[c.dir]; n.x = c.x + dx[c.dir];
				n.dir = c.dir;
				if (map[n.y][n.x] == 0) {//Èò»ö
					white(n, i);
				}
				else if (map[n.y][n.x] == 1) {//»¡°£»ö
					Red(n, i);
				}
				else if (!safe(n.y,n.x)||map[n.y][n.x] == 2) {//ÆÄ¶õ»ö
					Blue(c, i);
				}
			}
			ret++;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (horsePos[i][j].size() >= 4) {
						printf("%d\n", ret);
						return ;
					}
				}
			}
			if (ret == 1001) {
				printf("%d\n", -1);
				return;
			}
		}
	}
}NewGame2;
int main(void) {

	return 0;
}