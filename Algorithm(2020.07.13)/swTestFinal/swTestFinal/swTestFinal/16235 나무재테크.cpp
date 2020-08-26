#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define N_SIZE 12 //최대 배열 크기값
int dy8[] = {-1,-1,-1,0,0,1,1,1};
int dx8[] = {-1,0,1,-1,1,-1,0,1};
int currentSoil[N_SIZE][N_SIZE];//현재영양분 5저장
int A[N_SIZE][N_SIZE];//S2D2가 땅에 저장할 영양분
int ret;//결과값 저장
int N, M, YEAR;//배열크기, 나무수, 년 수
vector<int>Tree[N_SIZE][N_SIZE];//나무 나이 저장
struct Data {
	int y, x, age;
};
vector<Data>dieTree;
bool safe(int y, int x) {//범위 체크
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
//봄 
//자신 나이 만큼 양분 흡수 
// 나이 1증가 (제일 나이 어린순 부터)
void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Tree[i][j].size() != 0) {//나무가 한개라도 있으면
				sort(Tree[i][j].begin(), Tree[i][j].end());//어린순으로 정렬
				for (int k = 0; k < Tree[i][j].size(); k++) {//양분 흡수
					if (Tree[i][j].size() == 0)break;
					if (currentSoil[i][j] - Tree[i][j][k] >= 0) {
						currentSoil[i][j] -= Tree[i][j][k];
						Tree[i][j][k]++;//나이 증가
					}
					else {
						dieTree.push_back({ i,j,Tree[i][j][k]/2 });//죽은 나무 영양 분 /2저장
						Tree[i][j].erase(Tree[i][j].begin() + k);//죽은 나무 삭제
						k--;
					}
				}
			}
		}
	}
}

//여름
//봄에 죽은 나무 나이 / 2 땅의 양분으로 흡수
void summer() {
	for (int i = 0; i < dieTree.size(); i++) {
		currentSoil[dieTree[i].y][dieTree[i].x] += dieTree[i].age;//영양분 저장
	}
	dieTree.clear();//죽은 나무 초기화
}

//가을 
//나이가 5의 배수인것 8방향으로 나무 1살짜리 생성
void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (Tree[i][j].size() != 0) {
				for (int k = 0; k < Tree[i][j].size(); k++) {
					if (Tree[i][j][k] % 5 == 0) {// 번식 가능하면
						for (int dir = 0; dir < 8; dir++) {
							int ny = i + dy8[dir];
							int nx = j + dx8[dir];
							if (safe(ny, nx)) {
								Tree[ny][nx].push_back(1);
							}
						}
					}
				}
			}
		}
	}
}
//겨울
//S2D2가 양분이 있는 땅에 A의 입력으로 주어진 양분 저장 
void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			currentSoil[i][j] += A[i][j];// 영양분 축적 시키기
		}
	}
}
void init() {//초기화 시키기
	N = M = YEAR = ret = 0;
	memset(currentSoil, 0, sizeof(currentSoil));
	memset(A, 0, sizeof(A));
	scanf("%d %d %d", &N, &M, &YEAR);//배열 크기, 나무 수, 년도 입력
	for (int i = 1; i <= N; i++) {// 초기 땅 5로 초기화 하면서 A배열 입력
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);//겨울에 저장할 영양분
			currentSoil[i][j] = 5;//초기 땅 영양분
		}
	}

	int y, x, age;
	for (int i = 0; i < M; i++) {// 나무 심기
		scanf("%d %d %d", &y, &x, &age);
		Tree[y][x].push_back(age);
	}
}
void chkCnt() {//남아 있는 나무 갯수 체크
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ret += Tree[i][j].size();
			Tree[i][j].clear();
		}
	}
}
int main(void) {
	int testCase = 1;
	//scanf("%d", &testCase);
	for (int tc = 1; tc <= testCase; tc++) {//테스트 케이스 만큼 반복
		init();
		while (YEAR--) {//년도 만큼 반복
			spring();
			summer();
			fall();
			winter();
		}
		chkCnt();// 나무 갯수 저장
		printf("%d\n", ret);
	//	printf("#%d %d\n", tc, ret);//결과값 도출
	}
	return 0;
}