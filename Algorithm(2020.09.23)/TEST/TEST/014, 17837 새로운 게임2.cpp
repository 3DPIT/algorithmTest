#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define NSIZE 13//체스판의 최대크기
#define KSIZE 11//말의 최대 개수
struct HorseData {
	int num, dir;
};//이동시킬때 말의 정보 
struct Data {
	int y, x, dir,num;
};//현재위치의 말의 정보
vector<HorseData>horse;//이동할때 말의 정보 담기
vector<Data>horse_pos[KSIZE];//각 말의 정보
int chess_place[NSIZE][NSIZE];//입력으로 주어지는 배열
vector<Data>v_place[NSIZE][NSIZE];//말의 올라가있는수 저장
int dy[] = { 0,0,0,-1,1 };//방향 
int dx[] = { 0,1,-1,0,0 };
int N, K;//체스판의 크기, 말의 개수
int ret;//결과값 입력
void init_input() {//초기화 및 초기 입력
	//초기화
	N = K = ret = 0;
	memset(chess_place, 0, sizeof(chess_place));
	horse.clear();
	for (int i = 0; i <= NSIZE; i++) { for (int j = 0; j <= NSIZE; j++) { v_place[i][j].clear(); } }
	for (int i = 0; i < KSIZE; i++)horse_pos[i].clear();
	//초기 입력
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &chess_place[i][j]);
		}
	}
	for (int i = 1; i <= K; i++) {
		int y, x, dir;//말의 위치 y,x,방향
		scanf("%d %d %d", &y, &x, &dir);
		v_place[y][x].push_back({ y,x,dir,i});//말의 판위에 올라간것
		horse_pos[i].push_back({ y,x,dir,0});//말 정보저장
	}
}
bool safe(int y, int x) {//범위 지정
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void white(int idx){//흰색의 경우
	int cy=horse_pos[idx].front().y;
	int cx = horse_pos[idx].front().x;
	int cdir = horse_pos[idx].front().dir;
	//현재 위치에 있는 것들 모으기
	queue<Data>q;
	for (int i = 0; i < v_place[cy][cx].size(); i++) {
		if (v_place[cy][cx][i].num == idx) {
			for (int j = i; j < v_place[cy][cx].size(); j++) {
				q.push(v_place[cy][cx][j]);//위치의 것들 저장
			}
			v_place[cy][cx].erase(v_place[cy][cx].begin() + i, v_place[cy][cx].end());
			//제거 
			break;
		}
	}//for i
	while (!q.empty()) {//다음 위치에 저장시키기
		//정보 바꿔주기
		Data c = q.front(); q.pop();
		Data n;
		n.y = c.y + dy[cdir];
		n.x = c.x + dx[cdir];
		n.dir = c.dir;
		n.num = c.num;
		horse_pos[c.num].front().y = n.y;
		horse_pos[c.num].front().x = n.x;
		horse_pos[c.num].front().dir = n.dir;
		horse_pos[c.num].front().num = n.num;
		v_place[n.y][n.x].push_back(n);//위에 올리기
	}
}
void red(int idx) {//빨강의 경우
	int cy = horse_pos[idx].front().y;
	int cx = horse_pos[idx].front().x;
	int cdir = horse_pos[idx].front().dir;
	//현재 위치에 있는 것들 모으기
	queue<Data>q;
	for (int i = 0; i < v_place[cy][cx].size(); i++) {
		if (v_place[cy][cx][i].num == idx) {
			for (int j = v_place[cy][cx].size()-1; j >=i; j--) {
				q.push(v_place[cy][cx][j]);//위치의 것들 저장
			}
			v_place[cy][cx].erase(v_place[cy][cx].begin() + i, v_place[cy][cx].end());
			//제거 
			break;
		}
	}//for i
	while (!q.empty()) {//다음 위치에 저장시키기
		//정보 바꿔주기
		Data c = q.front(); q.pop();
		Data n;
		n.y = c.y + dy[cdir];
		n.x = c.x + dx[cdir];
		n.dir = c.dir;
		n.num = c.num;
		horse_pos[c.num].front().y = n.y;
		horse_pos[c.num].front().x = n.x;
		horse_pos[c.num].front().dir = n.dir;
		horse_pos[c.num].front().num = n.num;
		v_place[n.y][n.x].push_back(n);//위에 올리기
	}
}
void blue_out(int idx){//파란색 또는 나가는 경우
	int cy = horse_pos[idx].front().y;
	int cx = horse_pos[idx].front().x;
	if (horse_pos[idx].front().dir == 1) { horse_pos[idx].front().dir = 2; }
	else if (horse_pos[idx].front().dir == 2) { horse_pos[idx].front().dir = 1; }
	else if (horse_pos[idx].front().dir == 3) { horse_pos[idx].front().dir = 4; }
	else if (horse_pos[idx].front().dir == 4) { horse_pos[idx].front().dir = 3; }
	int cdir= horse_pos[idx].front().dir; 
	for (int i = 0; i < v_place[cy][cx].size(); i++) {
		if (v_place[cy][cx][i].num == idx) {
			v_place[cy][cx][i].dir = cdir;
			break;
		}
	}
	if (safe(cy + dy[cdir], cx + dx[cdir]) &&(chess_place[cy + dy[cdir]][cx + dx[cdir]] == 0|| chess_place[cy + dy[cdir]][cx + dx[cdir]] == 1)) {//범위를 넘거나 파란색인경우가 아닌경우만 넘기기
		if (chess_place[cy + dy[cdir]][cx + dx[cdir]] == 0)white(idx);//흰색으로 보내기
		else if (chess_place[cy + dy[cdir]][cx + dx[cdir]] == 1)red(idx);//빨간색으로 보내기
	}
}
bool chkFinish() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (v_place[i][j].size() >= 4) {//탈출 조건
				return true;
			}
		}
	}
	return false;//탈출 못함
}
void gameStart() {
	while (ret != 1001) {
		++ret;//시간증가
		int flag = 0;
		for(int i=1;i<=K;i++){//말의 이동시작
			Data c = horse_pos[i].front();
			int ny = c.y + dy[c.dir]; int nx = c.x + dx[c.dir];
			if (!safe(ny, nx) || chess_place[ny][nx] == 2) {
				//파란색 또는 바깥나가는 경우
				blue_out(i);
			}
			else if (chess_place[ny][nx] == 0 ) {
				//흰색의 경우
				white(i);
			}
			else if (chess_place[ny][nx] == 1) {
				//빨간색의 경우
				red(i);
			}
			if (chkFinish()) {
				flag = 1;
				return;
			}
		}
		if (chkFinish()) {
			break;//4개이상인곳 있는지 확인
		}
	}
	if (ret == 1001)ret = -1;//게임이 종료안되는 경우
}
int main(void) {
	int T = 1;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//초기화 및 입력
		init_input();
		gameStart();//알고리즘 게임 시작
		//출력
		printf("%d\n", ret);
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}