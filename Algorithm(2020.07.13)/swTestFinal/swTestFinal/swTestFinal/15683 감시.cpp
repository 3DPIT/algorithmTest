#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
#define ROOM_SIZE 9
int room[ROOM_SIZE][ROOM_SIZE];
int cctvCnt[] = { 0,4,2,4,4,1 };// cctv 방향
int N, M;
int dy[] = { 0,1,0,-1 };//상 우 하 좌
int dx[] = { 1,0,-1,0 };
int Min = 0x7fffffff;//최소값
struct Data {//y,x,값 cctv 종류 담기
	int y, x, type;
};
vector<Data>CCTV;//cctv 담는 공간
void init() {//초기값 설정
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &room[i][j]);
			if (room[i][j] != 6// 벽이나 빈공간이 아닌것 수집
				&& room[i][j] != 0) {
				CCTV.push_back({ i,j,room[i][j] });
			}
		}
	}
}
bool safe(int y, int x) {//맵의 범위 넘어가는지 체크
	return 0 <= y && y < N && 0 <= x && x < M;
}
void search(int dir, int y, int x) {//경로에 표시하기
	dir = (dir % 4);// dir 회전 
	while (1) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (room[ny][nx] != 6&&safe(ny,nx)) {
			room[ny][nx] = 8;// 감시영역 생성
		}
		else {
			break;
		}
		y = ny; x = nx;
	}
}
void copy(int cr[ROOM_SIZE][ROOM_SIZE], int r[ROOM_SIZE][ROOM_SIZE]) {//배열 복사
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cr[i][j] = r[i][j];
		}
	}
}
void print(int idx,int i) {//감시 경로 입히기
	if (CCTV[idx].type == 1) {
		search(i, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
	}
	if (CCTV[idx].type == 2) {
		search(i, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 2, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
	}
	if (CCTV[idx].type == 3) {
		search(i, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 1, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
	}
	if (CCTV[idx].type == 4) {
		search(i, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 1, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 2, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
	}
	if (CCTV[idx].type == 5) {
		search(i, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 1, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 2, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
		search(i + 3, CCTV[idx].y, CCTV[idx].x);//방향 ,y,x 넘기기
	}
}
void dfs(int idx,int cnt) {
	if (cnt == CCTV.size()) {// 현재 방향으로 cctv 경로 다찍은 경우 남은 사각 지대 검사하기 
		int ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (room[i][j] == 0) {
					ret++;//사각지대 저장되는곳
				}
			}
		}
		Min = Min > ret ? ret : Min;//사각지대의 최소값
		return;
	}
	int croom[ROOM_SIZE][ROOM_SIZE] = { 0, };//이전값 복사하는 배열
	for (int i = 0; i < cctvCnt[CCTV[idx].type]; i++) {
		copy(croom, room);
		print(idx, i);//cctv별로 경로 입히기
		dfs(idx + 1, cnt + 1);
		copy(room, croom);
	}
}
int main(void) {
	init();
	dfs(0,0);
	cout << Min << endl;
	return 0;
}