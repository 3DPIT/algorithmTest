#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define S 13 
int N, K;
int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };
int ret;
int flag = 0;
struct Data {
	int y, x, dir, num, color;
};
int iinput[S][S];
vector<Data>input[S][S];
vector<Data>v[11];
struct NewGame {
	NewGame() {
		init();
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &iinput[i][j]);
			}
		}

		for (int k = 1; k <= K; k++) {
			int y, x, dir;
			scanf("%d %d %d", &y, &x, &dir);
			v[k].push_back({ y - 1,x - 1,dir,k });
			input[y - 1][x - 1].push_back({ y - 1,x - 1,dir,k,0 });
		}
		while (flag == 0) {
			play();
		}

		printf("%d\n", ret);
	}
	void init() {
		N = K = ret = 0;
		memset(input, 0, sizeof(input));
		for (int i = 0; i < 11; i++) {
			v[i].clear();
		}
	}
	void play() {
		ret++;
		for (int i = 1; i <= K; i++) {
			if (input[v[i].front().y][v[i].front().x].front().num == v[i].front().num) {
				Data c = v[i].front();
				int ny = c.y + dy[c.dir];
				int nx = c.x + dx[c.dir];
				//resultChk();
				if (!safe(ny, nx)) {
					if (v[input[c.y][c.x].front().num].front().dir == 1) {
						v[input[c.y][c.x].front().num].front().dir = 2;
					}
					else if (v[input[c.y][c.x].front().num].front().dir == 2) {
						v[input[c.y][c.x].front().num].front().dir = 1;
					}
					else if (v[input[c.y][c.x].front().num].front().dir == 3) {
						v[input[c.y][c.x].front().num].front().dir = 4;
					}
					else if (v[input[c.y][c.x].front().num].front().dir == 4) {
						v[input[c.y][c.x].front().num].front().dir = 3;
					}
					c = v[i].front();
					ny = c.y + dy[c.dir];
					nx = c.x + dx[c.dir];
				}
				else if (iinput[ny][nx] == 0) {//Èò
					white(c.y, c.x, ny, nx);
				}
				else if (iinput[ny][nx] == 1) {//»¡
					red(c.y, c.x, ny, nx);
				}
				else if (iinput[ny][nx] == 2 ) {//ÆÄ
					blue(c.y, c.x, ny, nx);
				}
			}
		}

		if (ret == 1001) {
			flag = 1;
			ret = -1; return;
		}
		resultChk();
		if (flag == 1) {
			return;
		}
	}
	void resultChk() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (input[i][j].size() >= 4) {
					flag = 1;

					return;
				}
			}
		}
	}
	void white(int cy, int cx, int y, int x) {
		for (int i = 0; i < input[cy][cx].size(); i++) {
			Data c = input[cy][cx][i];
			v[c.num].clear();
			v[c.num].push_back({ y,x,c.dir,c.num,c.color });
			input[y][x].push_back({ y,x,c.dir,c.num,c.color });
		}
		while (!input[cy][cx].empty())input[cy][cx].pop_back();
	}
	void red(int cy, int cx, int y, int x) {
		for (int i = input[cy][cx].size()-1; i>=0; i--) {
			Data c = input[cy][cx][i];
			v[c.num].clear();
			v[c.num].push_back({ y,x,c.dir,c.num,c.color });
			input[y][x].push_back({ y,x,c.dir,c.num,c.color });
		}
		while (!input[cy][cx].empty())input[cy][cx].pop_back();
		
	}
	void blue(int cy, int cx, int y, int x) {
		if (iinput[y][x] == 3 || !safe(y, x)) {
			if (v[input[cy][cx].front().num].front().dir == 1) {
				v[input[cy][cx].front().num].front().dir = 2;
			}
			else if (v[input[cy][cx].front().num].front().dir == 2) {
				v[input[cy][cx].front().num].front().dir = 1;
			}
			else if (v[input[cy][cx].front().num].front().dir == 3) {
				v[input[cy][cx].front().num].front().dir = 4;
			}
			else if (v[input[cy][cx].front().num].front().dir == 4) {
				v[input[cy][cx].front().num].front().dir = 3;
			}
		}
		if (iinput[y][x] == 1) {
			white(cy, cx, cy + dy[input[y][x].front().dir], cx + dx[input[y][x].front().dir]);
		}
		if (iinput[y][x] == 2) {
			red(cy, cx, cy + dy[input[y][x].front().dir], cx + dx[input[y][x].front().dir]);
		}
	}
	bool safe(int y, int x) {
		return 0 <= y && y < N && 0 <= x && x < N;
	}
}NewGame;
int main(void) {

}