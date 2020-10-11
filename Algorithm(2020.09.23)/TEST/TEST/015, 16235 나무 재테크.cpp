#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define NSIZE 11
int N, M, K;//맵크기, 나무수, 년수
int A[NSIZE][NSIZE];//초기 입력 배열
int soil[NSIZE][NSIZE];//양분 저장되는 배열
int die_soil[NSIZE][NSIZE];//죽은 나무 저장되는 배열
int ret;//결과값 저장
int dy[] = { -1,-1,-1,0,0,1,1,1};//8가지 방향 번식시 사용
int dx[] = { -1,0,1,-1,1,-1,0,1};
vector<int>tree[NSIZE][NSIZE];//나무 저장되는 배열
bool safe(int y, int x) {//범위 확인
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void init_input() {//초기화 및 초기 입력
	//초기화
	N = M = K = ret = 0;
	memset(A, 0, sizeof(A));
	memset(soil, 0, sizeof(soil));
	memset(die_soil, 0, sizeof(die_soil));
	for (int i = 1; i < NSIZE; i++)for (int j = 1; j < NSIZE; j++)tree[i][j].clear();
	//초기입력
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);//겨울에 뿌릴 양분 저장
			soil[i][j] = 5;//초기 양분 저장
		}
	}
	for (int m = 0; m < M; m++) {
		int y, x, age;
		scanf("%d %d %d", &y, &x, &age);
		tree[y][x].push_back(age);
	}
}
void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree[i][j].size() != 0) {
				//하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
				sort(tree[i][j].begin(), tree[i][j].end());//크기 순으로 나무 정렬
				for (int k = 0; k < tree[i][j].size(); k++) {
					if (tree[i][j].size() == 0)break;
					int currentTree = tree[i][j][k];//현재 나무 나이
					//만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다
					if (soil[i][j] - currentTree < 0) {//양분 섭취 못하는 경우
						die_soil[i][j] += (currentTree / 2);//죽은 나무 양분 저장
						tree[i][j].erase(tree[i][j].begin() + k);//현재 나무죽이고 없애기
						k--;
					}
					//봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다
					else if(soil[i][j]-currentTree>=0){//나무의 성장
						soil[i][j] -= currentTree;//양분 흡수
						tree[i][j][k]++;//나이 한살 먹음					
					}
				}
			}
		}
	 }
}
//여름에는 봄에 죽은 나무가 양분으로 변하게 된다. 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다.
void summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			soil[i][j] += die_soil[i][j];//양분 저장
			die_soil[i][j] = 0;//죽은 나무 양분 흡수 배열 초기화
		}
	}
}
//가을에는 나무가 번식한다. 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다. 어떤 칸 (r, c)와 인접한 칸은 (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1) 이다. 상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.
void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree[i][j].size()!=0) {//나무가 있을때
				for (int k = 0; k < tree[i][j].size(); k++) {
					if (tree[i][j][k] % 5 == 0) {//나무의 나이가 5의 배수라면
						for (int dir = 0; dir < 8; dir++) {
							int ny = i + dy[dir]; int nx = j + dx[dir];
							if (safe(ny, nx)) {//퍼지는 위치가 저장할 수 있는 공간이라면
								tree[ny][nx].push_back(1);//한살나무 저장
							}
						}
					}
				}
			}
		}
	}
}
//겨울에는 S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다. 각 칸에 추가되는 양분의 양은 A[r][c]이고, 입력으로 주어진다.
void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			soil[i][j] += A[i][j];
		}
	}
}
void chkTree() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ret += tree[i][j].size();
		}
	}
}
void tree_go() {//나무의 성장
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}
	chkTree();//남은 나무 산출
}
int main(void) {
	int T = 1;//테스트 케이스
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();
		tree_go();
		printf("%d\n", ret);
		//printf("#%d %d\n", tc, ret);
	}
	return 0;
}