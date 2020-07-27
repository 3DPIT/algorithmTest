#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define MAP_SIZE 51
int N, M;// 맵크기, 치킨집 최대 개수
int map[MAP_SIZE][MAP_SIZE];
int finalMin = 0x7fffffff;//치킨거리 최종 최소값
struct Data{
	int y, x;
};
vector<Data>home;// 집 좌표 저장
vector<Data>chicken;//치킨 좌표 저장
vector<int>shortDistance[MAP_SIZE*MAP_SIZE];//각 치킨까지 거리 저장
vector<int>D;// 뽑은 치킨집 저장 
void dfs(int idx, int d) {
	if (idx > chicken.size())return;
	if (d == M) {// 최대 치킨집을 뽑은 경우
		//최소인 치킨집 찾아내기
		int ret = 0;//최소 거리합 저장
		for (int i = 0; i < home.size(); i++) {
			int minDistance = 0x7fffffff;
			for (int j = 0; j < D.size(); j++) {
				minDistance = minDistance > shortDistance[i][D[j]]
					? shortDistance[i][D[j]] : minDistance;//최소 거리 찾기
			}
			ret += minDistance;//최소 거리합 저장
		}
		finalMin = finalMin > ret ? ret : finalMin;//최종 최소값
		return;
	}
	D.push_back(idx);
	dfs(idx + 1, d + 1);// 치킨집 뽑은 경우
	D.pop_back();
	dfs(idx + 1, d);//치킨집 안뽑고 넘긴경우
}
void init() {//초기화 및 입력 
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);//입력값 입력
			if (map[i][j] == 1) {
				home.push_back({ i,j });// 집 좌표 저장
			}
			if (map[i][j] == 2) {
				chicken.push_back({ i,j });//치킨 좌표 저장
			}
		}
	}
	// 미리 집과 치킨과의 거리 구해 놓기
	for (int i = 0; i < home.size(); i++) {
		for (int j = 0; j < chicken.size(); j++) {
			int distance1 = abs(home[i].y - chicken[j].y) + abs(home[i].x - chicken[j].x);//거리 구하기
			shortDistance[i].push_back(distance1);
		}
	}
}
int main(void) {
	init();
	dfs(0, 0);
	printf("%d\n", finalMin);
	return 0;
}