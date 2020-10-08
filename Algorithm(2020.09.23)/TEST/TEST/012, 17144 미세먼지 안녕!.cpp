#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#define NMSIZE 50
int N, M, T;//y축, x축, 시간
int map[NMSIZE][NMSIZE];//초기 입력으로 주어지는 배열
int a1y, a1x, a2y, a2x;//공기청정기 위치
int dy[] = { 0,-1,0,1 };//이동할 방향 배열
int dx[] = { 1,0,-1,0 };
int ret;//결과값 저장
void initAndInput() {//초기화및 입력
	N = M = T = a1y = a1x = a2y = a2x = ret=0;
	memset(map, 0, sizeof(map));
	int flag = 0;
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1) {
				if (!flag) {//상단청정기 위치 저장
					a1y = i; a1x = j;
					flag = 1;//하단청정기 저장을 위해서
				}
				if (flag) {//하단청정기 위치 저장
					a2y = i; a2x = j;
				}
			}
		}
	}
}
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < M;
}
bool isafe1(int y, int x) {//상단경로 탈출 확인
	return y == a1y + 1 || x == M || y == -1;
}
bool isafe2(int y, int x) {//하단경로 탈출 확인
	return x == M || y == a2y-1 || y == N;
}
void downClean() {//하단 경로 흡입
	int cy = a2y; int cx = a2x; int dir = 3;//공기청정기 현재 위치와 시작 방향
	while (1) {
		int ny = cy + dy[dir]; int nx = cx + dx[dir];//다음 위치 체크
		if (a2y == ny && a2x == nx) {
			map[cy][cx] = 0;
			break;
		}
		if (isafe2(ny, nx)) {//방향 전환 시키기
			dir++;
			if (dir == 4)dir = 0;
		}
		else if(map[cy][cx]!=-1){//공기청정기가 아닌 공간이라면
			map[cy][cx] = map[ny][nx];
			cy = ny; cx = nx;//위치 이동시키기
		}
		else {
			cy = ny; cx = nx;//위치 이동시키기
		}
	}
}
void upClean() {//상단 공기 흡입
	int cy = a1y; int cx = a1x; int dir = 1;//공기청정기 현재 위치와 시작 방향
	while (1) {
		int ny = cy + dy[dir]; int nx = cx + dx[dir];//다음 위치 체크
		if (a1y == ny && a1x == nx) {
			map[cy][cx] = 0;
			break;
		}
		if (isafe1(ny, nx)) {//방향 전환 시키기
			dir--;
			if (dir == -1)dir = 3;
		}
		else if (map[cy][cx] != -1) {//공기청정기가 아닌 공간이라면
			map[cy][cx] = map[ny][nx];
			cy = ny; cx = nx;//위치 이동시키기
		}
		else {
			cy = ny; cx = nx;
		}
	}
}
void cleanAir() {
	//미세먼지가 확산된다.확산은 미세먼지가 있는 모든 칸에서 동시에 일어난다.
//(r, c)에 있는 미세먼지는 인접한 네 방향으로 확산된다.
//인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
//확산되는 양은 Ar, c / 5이고 소수점은 버린다.
//(r, c)에 남은 미세먼지의 양은 Ar, c - (Ar, c / 5)×(확산된 방향의 개수) 이다.
//공기청정기가 작동한다.
//공기청정기에서는 바람이 나온다.
//위쪽 공기청정기의 바람은 반시계방향으로 순환하고, 아래쪽 공기청정기의 바람은 시계방향으로 순환한다.
//바람이 불면 미세먼지가 바람의 방향대로 모두 한 칸씩 이동한다.
//공기청정기에서 부는 바람은 미세먼지가 없는 바람이고, 공기청정기로 들어간 미세먼지는 모두 정화된다.
	while (T--) {
		//미세 먼지 확산
		int cMap[NMSIZE][NMSIZE] = { 0, };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] >=1) {
					int chkCnt = 0;//확산된 방향의 개수
					for (int dir = 0; dir < 4; dir++) {
						int ny = i + dy[dir]; int nx = j + dx[dir];
						if (safe(ny, nx) && map[ny][nx] != -1) {
							cMap[ny][nx] += map[i][j] / 5;
							chkCnt++;
						}
					}
					map[i][j] = map[i][j]-((map[i][j] / 5)*chkCnt);
				}
			}//for j
		}//for i

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				map[i][j] += cMap[i][j];//확산 된것 정리 하기
			}
		}
		//상단 공기청정기 동작

		upClean();
		//하단 공기 청정기 동작
		downClean();
	}//while(T--)
	//최종 남은 먼지의 수세기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != -1)ret += map[i][j];
		}
	}
}
int main(void) {
	initAndInput();
	cleanAir();
	printf("%d\n", ret);
	return 0;
}