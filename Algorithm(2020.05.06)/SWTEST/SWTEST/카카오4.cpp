#include <string>
#include <vector>
#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;
#define NS 26
int dy[] = { 0,1,0,- 1 };
int dx[] = { 1,0,-1,0 };
int chk[NS][NS];
int N;
int Min = 0x7fffffff;
bool safe(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}
struct Data {
	int y, x,dir,sum;
};
void bfs(vector<vector<int>> board) {
	queue<Data>q;
	for(int i=0;i<4;i++)
	q.push({ 0,0,i,0 });
	memset(chk, 0x32, sizeof(chk));
	chk[0][0] = 0;
	while (!q.empty())
	{
		Data c = q.front(); q.pop();
		if (c.y == N - 1 && c.x == N - 1) {
			if (Min > c.sum) {
				Min = c.sum;
			}
		}
		for (int dir = 0; dir < 4; dir++) {
			Data n;
			n.y = c.y + dy[dir];
			n.x = c.x + dx[dir];
			n.dir = dir;
			n.sum = c.sum + 100;
			if (c.dir != n.dir)n.sum += 500;
			if (safe(n.y, n.x) && board[n.y][n.x] == 0) {
				if (chk[n.y][n.x] >= n.sum) {//Á÷¼±
					chk[n.y][n.x] = n.sum;
					q.push(n);

				}
			}

		}

	}
}
int solution(vector<vector<int>> board) {
	Min = 0x7fffffff;
	int answer = 0;
	N = board.size();
	bfs(board);
	return answer=Min;
}

int main(void) {
	cout << solution({ {0,0,0},{0,0,0},{0,0,0} })<< endl;
	cout<<solution({ {0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,1,0,0,0},{0,0,0,1,0,0,0,1},{0,0,1,0,0,0,1,0},{0,1,0,0,0,1,0,0},{1,0,0,0,0,0,0,0} }) << endl;
	cout<<solution({ {0,0,1,0},{0,0,0,0},{0,1,0,1},{1,0,0,0} }) << endl;
	cout<<solution({ {0,0,0,0,0,0},{0,1,1,1,1,0},{0,0,1,0,0,0},{1,0,0,1,0,1},{0,1,0,0,0,1},{0,0,0,0,0,0} }) << endl;
	return 0;
}