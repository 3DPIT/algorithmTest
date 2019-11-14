#include <string>
#include <vector>
#include<queue>
#include<iostream>
using namespace std;
#define NS 101
int N;
int input[NS][NS];//board ������ ��������
int chk[NS][NS][2];//�湮üũ�� �迭
int dy[] = { -1,1,0,0,1,-1,-1,1,-1,-1,1,1 };//��,��,��,��,�ݽð�, �ð�
int dx[] = { 0,0,-1,1,-1,-1,1,1,-1,1,1,-1 };
int ret;
struct Data {
	int y, x, dir, cnt;
};
void copy(int input[NS][NS], vector<vector<int> >board) {
	N = board.size();
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			input[i + 1][j + 1] = board[i][j];
		}
	}
}
bool safe(Data n) {
	if (n.y<1 || n.y>N || n.x<1 || n.x>N)return false;
	return true;
}
void BFS() {
	queue<Data>q;
	q.push({ 1,1,0,0 });
	chk[1][1][0] = 1;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.dir == 0 & ((c.y == N && c.x + 1 == N) || (c.y == N && c.x == N))) {
			ret = c.cnt;
			return;
		}
		if (c.dir == 1 & ((c.y + 1 == N && c.x == N) || (c.y == N && c.x == N))) {
			ret = c.cnt;
			return;
		}
		//�����¿� �̵�
		//������ ��� �밢�� �̵�
		if (c.dir == 0) {
			for (int dir = 0; dir < 4; dir++) {
				//��//
				if (dir == 0 && safe({ c.y - 1 ,c.x,0,0 }) && input[c.y - 1][c.x] == 0 && safe({ c.y - 1 ,c.x + 1,0,0 }) && input[c.y - 1][c.x + 1] == 0
					&& chk[c.y - 1][c.x][0] == 0) {
					chk[c.y - 1][c.x][0] = 1;
					q.push({ c.y - 1,c.x,0,c.cnt + 1 });
				}
				//��//
				if (dir == 1 && safe({ c.y + 1 ,c.x,0,0 }) && input[c.y + 1][c.x] == 0 && safe({ c.y + 1 ,c.x + 1 ,0,0 }) && input[c.y + 1][c.x + 1] == 0
					&& chk[c.y + 1][c.x][0] == 0) {
					chk[c.y + 1][c.x][0] = 1;
					q.push({ c.y + 1,c.x,0,c.cnt + 1 });
				}
				//��//
				if (dir == 2 && safe({ c.y  ,c.x - 1,0,0 }) && input[c.y][c.x - 1] == 0
					&& chk[c.y][c.x - 1][0] == 0) {
					chk[c.y][c.x - 1][0] = 1;
					q.push({ c.y,c.x - 1,0,c.cnt + 1 });
				}
				//��//
				if (dir == 3 && safe({ c.y ,c.x + 2,0,0 }) && input[c.y][c.x + 2] == 0
					&& chk[c.y][c.x+1][0] == 0) {
					chk[c.y][c.x+1][0] = 1;
					q.push({ c.y,c.x+1,0,c.cnt + 1 });
				}
			}
			for (int dir = 4; dir < 8; dir++) {
				//xy�� �ð�//
				if (dir == 4 && safe({ c.y + 1 ,c.x + 1,0,0 }) && input[c.y + 1][c.x + 1] == 0 && safe({ c.y + 1 ,c.x,0,0 }) && input[c.y + 1][c.x] == 0
					&& chk[c.y][c.x][1] == 0) {
					chk[c.y][c.x][1] = 1;
					q.push({ c.y,c.x,1,c.cnt + 1 });
				}
				//xy�� �ݽð�//
				if (dir == 5 && safe({ c.y - 1 ,c.x ,0,0 }) && input[c.y - 1][c.x] == 0 && safe({ c.y -1 ,c.x + 1,0,0 }) && input[c.y-1][c.x + 1] == 0
					&& chk[c.y - 1][c.x][1] == 0) {
					chk[c.y - 1][c.x][1] = 1;
					q.push({ c.y - 1,c.x,1,c.cnt + 1 });
				}
				//�ٸ��� �ð�//
				if (dir == 6 && safe({ c.y - 1 ,c.x ,0,0 }) && input[c.y - 1][c.x] == 0 && safe({ c.y -1 ,c.x +1,0,0 }) && input[c.y -1][c.x +1] == 0
					&& chk[c.y -1][c.x + 1][1] == 0) {
					chk[c.y -1][c.x + 1][1] = 1;
					q.push({ c.y -1,c.x + 1,1,c.cnt + 1 });
				}
				//�ٸ��� �ݽð�//
				if (dir == 7 && safe({ c.y + 1 ,c.x ,0,0 }) && input[c.y + 1][c.x] == 0 && safe({ c.y + 1 ,c.x +1,0,0 }) && input[c.y +1][c.x +1] == 0
					&& chk[c.y][c.x + 1][1] == 0) {
					chk[c.y][c.x + 1][1] = 1;
					q.push({ c.y ,c.x + 1,1,c.cnt + 1 });
				}
			}
		}
		//�����¿� �̵�
		//������ ��� �밢�� �̵�
		else if (c.dir == 1) {
			for (int dir = 0; dir < 4; dir++) {
				//��//
				if (dir == 0 && safe({ c.y + dy[dir] ,c.x + dx[dir],0,0 }) && input[c.y + dy[dir]][c.x + dx[dir]] == 0
					&& chk[c.y + dy[dir]][c.x + dx[dir]][1] == 0) {
					chk[c.y + dy[dir]][c.x + dx[dir]][1] = 1;
					q.push({ c.y + dy[dir],c.x + dx[dir],1,c.cnt + 1 });
				}
				//��//
				if (dir == 1 && safe({ c.y + 1 + dy[dir] ,c.x + dx[dir],0,0 }) && input[c.y + 1 + dy[dir]][c.x + dx[dir]] == 0
					&& chk[c.y + dy[dir]][c.x + dx[dir]][1] == 0) {
					chk[c.y + dy[dir]][c.x + dx[dir]][1] = 1;
					q.push({ c.y + dy[dir],c.x + dx[dir],1,c.cnt + 1 });
				}
				//��//
				if (dir == 2 && safe({ c.y ,c.x-1,0,0 }) && input[c.y][c.x -1] == 0 && safe({ c.y + 1 ,c.x-1,0,0 }) && input[c.y + 1][c.x-1] == 0
					&& chk[c.y][c.x-1][1] == 0) {
					chk[c.y][c.x-1][1] = 1;
					q.push({ c.y,c.x-1,1,c.cnt + 1 });
				}
				//��//
				if (dir == 1 && safe({ c.y,c.x + 1 ,0,0 }) && input[c.y ][c.x + 1] == 0 && safe({ c.y + 1  ,c.x + 1,0,0 }) && input[c.y + 1 ][c.x + 1] == 0
					&& chk[c.y][c.x + 1][1] == 0) {
					chk[c.y][c.x + 1][1] = 1;
					q.push({ c.y,c.x+1,1,c.cnt + 1 });
				}
			}
			for (int dir = 8; dir < 12; dir++) {
				//xy�� �ð�//
				if (dir == 8 && safe({ c.y  ,c.x - 1,0,0 }) && input[c.y][c.x - 1] == 0 && safe({ c.y + 1,c.x - 1,0,0 }) && input[c.y + 1][c.x - 1] == 0
					&& chk[c.y][c.x - 1][0] == 0) {
					chk[c.y][c.x - 1][0] = 1;
					q.push({ c.y,c.x - 1,0,c.cnt + 1 });
				}
				//xy�� �ݽð�//

				if (dir == 9 && safe({ c.y ,c.x + 1,0,0 }) && input[c.y][c.x + 1] == 0 && safe({ c.y + 1 ,c.x + 1 ,0,0 }) && input[c.y + 1][c.x + 1] == 0
					&& chk[c.y][c.x][0] == 0) {
					chk[c.y][c.x][0] = 1;
					q.push({ c.y,c.x,0,c.cnt + 1 });
				}
				//�ٸ��� �ð�//
				if (dir == 10 && safe({ c.y,c.x + 1 ,0,0 }) && input[c.y][c.x + 1] == 0 && safe({ c.y + 1 ,c.x + 1,0,0 }) && input[c.y + 1][c.x + 1] == 0
					&& chk[c.y + 1][c.x][0] == 0) {
					chk[c.y + 1][c.x][0] = 1;
					q.push({ c.y + 1,c.x,0,c.cnt + 1 });
				}
				//�ٸ��� �ݽð�//
				if (dir == 11 && safe({ c.y ,c.x - 1 ,0,0 }) && input[c.y][c.x - 1] == 0 && safe({ c.y + 1 ,c.x - 1,0,0 }) && input[c.y + 1][c.x - 1] == 0
					chk[c.y + 1][c.x - 1][0] = 1;
					q.push({ c.y + 1 ,c.x - 1,0,c.cnt + 1 });
				}
			}
		}
	}
}
int solution(vector<vector<int>> board) {
	copy(input, board);
	int answer = 0;
	BFS();
	return answer = ret;
}
int main(void) {
	cout << solution({ {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} });
	return 0;
}