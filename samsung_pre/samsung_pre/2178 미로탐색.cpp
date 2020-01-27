#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define NMS 101
int N, M;
char miro[NMS][NMS];
int chk[NMS][NMS];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
struct Data{
	int y, x, cnt;
};
bool safeZone(int y, int x){
	if (0 <= y && y < N && 0 <= x && x < M) return true;
	else return false;
}
void miroSearch() {
	queue<Data>q;
	q.push({ 0,0,1});
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.y == N - 1 && c.x == M - 1) {// ¹Ì·Î µµÂøÁ¡ µµÂø
			cout << c.cnt;
			return;
		}
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = c.y + dy[dir];
			n.x = c.x + dx[dir];
			n.cnt = c.cnt + 1;
			if (safeZone(n.y, n.x) && miro[n.y][n.x] == '1'&&chk[n.y][n.x] == 0) {
				chk[n.y][n.x] = 1;
				miro[n.y][n.x] = '.';
				q.push({ n.y,n.x,n.cnt });
			}
		}
	}

}
void init() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> miro[i];
	miroSearch();
}
int main(void) {
	init();
	return 0;
}