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
	int y,x,dir,num;
};
vector<Data>horse[KS];
vector<Data>hInput[NS][NS];
int Time = 0;
void wSpace(Data c,Data n) {
	while (!hInput[c.y][c.x].empty()) {
		Data h = hInput[c.y][c.x].front(); hInput[c.y][c.x].erase(hInput[c.y][c.x].begin());
		hInput[n.y][n.x].push_back({ n.y,n.x,h.dir,h.num });
		horse[h.num].front().y = n.y;
		horse[h.num].front().x = n.x;
		horse[h.num].front().dir = h.dir;
		horse[h.num].front().num = h.num;
	}
}
void rSpace(Data c, Data n) {
	while (!hInput[c.y][c.x].empty()) {
		Data h = hInput[c.y][c.x].back(); hInput[c.y][c.x].pop_back();
		hInput[n.y][n.x].push_back({ n.y,n.x,h.dir,h.num });
		horse[h.num].front().y = n.y;
		horse[h.num].front().x = n.x;
		horse[h.num].front().dir = h.dir;
		horse[h.num].front().num = h.num;
	}
}
void bSpace(Data c, Data n) {
	if (hInput[c.y][c.x].front().dir == 1)hInput[c.y][c.x].front().dir = 2;
	else if (hInput[c.y][c.x].front().dir == 2)hInput[c.y][c.x].front().dir = 1;
	else if (hInput[c.y][c.x].front().dir == 3)hInput[c.y][c.x].front().dir = 4;
	else if (hInput[c.y][c.x].front().dir == 4)hInput[c.y][c.x].front().dir = 3;
	n.y = c.y + dy[hInput[c.y][c.x].front().dir];
	n.x = c.x + dx[hInput[c.y][c.x].front().dir];
	//파란공간인경우
	if (input[n.y][n.x] == 2 || (n.y<1 || n.y>N || n.x<1 || n.x>N)) {
		return;
	}
	//하얀공간인경우 
	else if (input[n.y][n.x] == 0) {
		wSpace(c, n);
	}
	//빨간공간인경우
	else if (input[n.y][n.x] == 1) {
		rSpace(c, n);
	}
}
void play() {
	while (1) {
		int cnt = 0;//턴 확인 용도
		Time++;
		for (int i = 1; i <= K; i++) {
			Data c = horse[i].front();
			if (hInput[c.y][c.x][0].num != i)continue;// 하단이 아니면 
			int dir=hInput[c.y][c.x][0].dir;
			Data n;
			n.y = c.y + dy[dir];
			n.x = c.x + dx[dir];
			//파란공간이거나 벗어나는경우 
			if (input[n.y][n.x] == 2 || (n.y<1||n.y>N||n.x<1||n.x>N)) {
				bSpace(c,n);
			}
			//하얀공간인경우 
			else if(input[n.y][n.x]==0){
				wSpace(c,n);
			}
			//빨간공간인경우//
			else if (input[n.y][n.x] == 1) {
				rSpace(c,n);
			}
		
		}
		//탈출 조건
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (hInput[i][j].size() >= 4) {
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
void init() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &input[i][j]);
		}
	}
	for (int i = 1; i <= K; i++) {
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		horse[i].push_back({ y,x,dir});//위치 바로 확인위한 용도
		hInput[y][x].push_back({ 0,0,dir,i });//여러개있는경우 위치
	}
	play();
}
int main(void) {
	init();
	return 0;
}