#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<queue>
#include<vector>
using namespace std;
#define NS 101
int N, K, X, La, dir = 0;;
int Time;
char C;
int map[NS][NS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data {
	int y, x;
};
deque<Data>dq;
struct Snake {
	Snake() {
		init();
		scanf("%d", &N);
		scanf("%d", &K);
		appleIn();
		scanf("%d", &La);
		GameStart();

	}
	bool outsafe(int y, int x) {
		return 0 >= y || y > N || 0 >= x || x > N;
	}
	void GameStart() {
		int y = 1,x = 1;
		int size = 1;
		int tail = 0;
		Time = 0;
		dq.push_front({ y,x });
		for (int Li = 0; Li < La; Li++) {
			scanf("%d %c", &X, &C);
			while (1) {
				int flag = 0;
				if (Time == X) {
					if (C == 'L') {
						dir--;
						if (dir == -1)dir = 3;
					}
					else {
						dir++;
						if (dir == 4)dir = 0;
					}
					if (Li < La-1) {
						break;
					}
				}
				y = y + dy[dir];
				x = x + dx[dir];
				if (map[y][x] == -1) {
					flag = 1;
					dq.push_front({ y,x });
				}

				else if (outsafe(y,x)||chk(y,x)) {// ²¿¸®¿¡ ´ê°Å³ª ³ª°¡¸é

					for (; Li < La-1; Li++) {
						scanf("%d %c", &X, &C);
					}
					cout << Time+1 << endl;
					break;
				}
				if (flag == 0) {
					dq.push_front({ y, x });
					map[dq.back().y][dq.back().x] = 0;
					dq.pop_back();
				}
			print("¹ì°æ·ÎÂï±â", 0,Time);
				Time++;
			}
		}
	}
	bool chk(int y, int x) {
		for (int i = 0; i < dq.size(); i++) {
			Data c = dq.front(); dq.pop_front();
			if (y == c.y&&x == c.x) {
				dq.push_back(c);
				return 1;
			}		
			dq.push_back(c);
		}
		return 0;
	}
	void init() {
		dir=N = K = X = La = 0;
		Time = 0;
		C = NULL;
		memset(map, 0, sizeof(map));
	}
	void appleIn() {
		for (int i = 0; i < K; i++) {//»ç°ú
			int y, x;
			scanf("%d %d", &y, &x);
			map[y][x] = -1;
		}
	}
	void print(string name, int num) {
		cout << name << endl;
		if (num == 0) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					printf("%3d", map[i][j]);
				}
				printf("\n");
			}

		}
		if (num == 1) {
			int Len = dq.size();
			for (int i = 0; i < Len; i++) {
				Data c = dq.front(); dq.pop_front();
				map[c.y][c.x] = 4;
				dq.push_back({ c.y,c.x });
			}
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					printf("%3d", map[i][j]);
				}
				printf("\n");
			}
		}
	}
	void print(string name, int num,int time) {
		cout << name << " "<<time<<endl;
		if (num == 0) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					printf("%3d", map[i][j]);
				}
				printf("\n");
			}
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					printf("%3d", map[i][j]);
				}
				printf("\n");
			}
		}
		
	}
}Snake;
int main(void) {

	return 0;
}