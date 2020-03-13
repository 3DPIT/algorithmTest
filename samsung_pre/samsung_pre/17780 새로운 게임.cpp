#include<stdio.h>
#include<vector>
using namespace std;
#define NS 13
#define KS 11
int input[NS][NS];
int N, K;
int dy[] = { 0,0,0,-1,1 };//우,좌,상,하
int dx[] = { 0,1,-1,0,0 };
struct Data {
	int y, x, dir, num;
};
vector<Data>horse[KS];
vector<Data>iinput[NS][NS];
int Time = 0;
struct NewGame {
	NewGame() {
		scanf("%d %d", &N, &K);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &input[i][j]);
			}
		}
		for (int i = 1; i <= K; i++) {
			int y, x, dir;
			scanf("%d %d %d", &y, &x, &dir);
			horse[i].push_back({ y,x,dir });
			iinput[y][x].push_back({ 0,0,dir,i });
		}
		play();
	}
	void play() {
		while (1) {
			int cnt = 0;//턴 확인 용도
			Time++;
			for (int i = 1; i <= K; i++) {
				Data c = horse[i].front();
				if (iinput[c.y][c.x][0].num != i)continue;// 하단이 아니면 
				int dir = iinput[c.y][c.x][0].dir;
				Data n;
				n.y = c.y + dy[dir];
				n.x = c.x + dx[dir];
				//파란공간이거나 벗어나는경우 
				if (input[n.y][n.x] == 2 || !safe(n.y, n.x)) {
					Blue(c, n);
				}
				//하얀공간인경우 
				else if (input[n.y][n.x] == 0) {
					White(c, n);
				}
				//빨간공간인경우//
				else if (input[n.y][n.x] == 1) {
					Red(c, n);
				}

			}
			//탈출 조건
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (iinput[i][j].size() >= 4) {
						printf("%d\n", Time);
						return;
					}
				}
			}
			if (Time == 1001) {
				printf("-1\n");
				return;
			}
		}
	}
	void White(Data c, Data n) {
		while (!iinput[c.y][c.x].empty()) {
			Data h = iinput[c.y][c.x].front(); iinput[c.y][c.x].erase(iinput[c.y][c.x].begin());
			iinput[n.y][n.x].push_back({ n.y,n.x,h.dir,h.num });
			horse[h.num].front().y = n.y;
			horse[h.num].front().x = n.x;
			horse[h.num].front().dir = h.dir;
			horse[h.num].front().num = h.num;
		}
	}
	void Red(Data c, Data n) {
		while (!iinput[c.y][c.x].empty()) {
			Data h = iinput[c.y][c.x].back(); iinput[c.y][c.x].pop_back();
			iinput[n.y][n.x].push_back({ n.y,n.x,h.dir,h.num });
			horse[h.num].front().y = n.y;
			horse[h.num].front().x = n.x;
			horse[h.num].front().dir = h.dir;
			horse[h.num].front().num = h.num;
		}
	}
	void Blue(Data c, Data n) {
		if (iinput[c.y][c.x].front().dir == 1)iinput[c.y][c.x].front().dir = 2;
		else if (iinput[c.y][c.x].front().dir == 2)iinput[c.y][c.x].front().dir = 1;
		else if (iinput[c.y][c.x].front().dir == 3)iinput[c.y][c.x].front().dir = 4;
		else if (iinput[c.y][c.x].front().dir == 4)iinput[c.y][c.x].front().dir = 3;
		n.y = c.y + dy[iinput[c.y][c.x].front().dir];
		n.x = c.x + dx[iinput[c.y][c.x].front().dir];
		if (input[n.y][n.x] == 2 ||!safe(n.y,n.x)) {
			return;
		}
		else if (input[n.y][n.x] == 0) {
			White(c, n);
		}
		else if (input[n.y][n.x] == 1) {
			Red(c, n);
		}
	}
	
	bool safe(int y, int x) {
		return 1 <= y && y <= N && 1 <= x && x <= N;
	}
	
}NewGame;

int main(void) {
	return 0;
}