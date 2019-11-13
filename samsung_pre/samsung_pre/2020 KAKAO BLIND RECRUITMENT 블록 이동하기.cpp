#include <string>
#include <vector>
#include<queue>
#include<iostream>
using namespace std;
#define N 101
int cN;
int input[N][N];//board ������ ��������
int chk[N][N][N][N][3];//�湮üũ�� �迭
int dy[] = { -1,0,1,0,1,-1 };//��,��,��,��,�ݽð�, �ð�
int dx[] = { 0,1,0,-1,1,1 };
int ret;
struct Data {
	int y, x, y1, x1, cnt;
};
void copy(int input[N][N], vector<vector<int> >board) {
	cN = board.size();
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			input[i + 1][j + 1] = board[i][j];
		}
	}
}
void BFS() {

	queue<Data>q;
	q.push({ 1,1,1,2,0 });
	chk[1][1][1][2][0] = 1;
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if ((c.y == cN && c.x == cN) || (c.y1 == cN && c.x1 == cN)) {// ���޽�
			ret = c.cnt;
			return;
		}
		for (int dir = 0; dir < 6; dir++) {
			Data n;
			if (dir == 4 || dir == 5) {//ȸ���� ���
				if (c.y == c.y1) {
					//���� y1 x1 ���� �߽����� �̵�
					n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
					n.y1 = c.y1; n.x1 = c.x1;
					n.cnt = c.cnt + 1;
					if (!(n.y<1 || n.y>cN || n.x<1 || n.x>cN || c.y + 1 < 1 || c.y + 1 > cN || c.x + 1 < 1 || c.x > cN)
						&& dir == 4 && chk[n.y][n.x][n.y1][n.x1][dir - 3] == 0) {
						if (input[n.y][n.x] != 1 && input[c.y + 1][c.x + 1] != 1) {//�ݽð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}
					else {
						if (!(n.y<1 || n.y>cN || n.x<1 || n.x>cN || c.y - 1 < 1 || c.y > cN || c.x + 1 < 1 || c.x > cN)
							&& input[n.y][n.x] != 1 && input[c.y - 1][c.x + 1] != 1) {//�ð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}
					//���� y,x ���� �߽����� �̵�
					n.y = c.y; n.x = c.x;
					n.y1 = c.y1 - dy[dir]; n.x1 = c.x1 - dx[dir];
					n.cnt = c.cnt + 1;
					if (!(n.y1<1 || n.y1>cN || n.x1<1 || n.x1>cN || c.y1 - 1 < 1 || c.y1 - 1 > cN || c.x1<1 || c.x1>cN)
						&& dir == 4 && chk[n.y][n.x][n.y1][n.x1][dir - 3] == 0) {
						if (input[n.y1][n.x1] != 1 && input[c.y1 - 1][c.x] != 1) {//�ݽð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}
					else {
						if (!(n.y1<1 || n.y1>cN || n.x1<1 || n.x1>cN || c.y1 - 1 < 1 || c.y1 - 1 > cN || c.x1 + 1 < 1 || c.x1 + 1 > cN)
							&& input[n.y1][n.x1] != 1 && input[c.y1 - 1][c.x1 + 1] != 1) {//�ð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;							q.push(n);
							q.push(n);
						}
					}
				}
				else if (c.x == c.x1) {
					//����y1 x1 ���� �߽����� �̵�
					n.y = c.y - dy[dir]; n.x = c.x - dx[dir];
					n.y1 = c.y1; n.x1 = c.x1;
					n.cnt = c.cnt + 1;
					if (n.y<1 || n.y>cN || n.x<1 || n.x>cN || n.y1<1 || n.y1>cN || n.x1<1 || n.x1>cN)continue;
					if (dir == 4 && chk[n.y][n.x][n.y1][n.x1][dir - 3] == 0) {
						if (input[n.y][n.x] != 1 && input[c.y][c.x + 1] != 1) {//�ð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}
					else {
						if (input[n.y][n.x] != 1 && input[c.y][c.x - 1] != 1) {//�ݽð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}
					//���� y,x ���� �߽����� �̵�
					n.y = c.y; n.x = c.x;
					n.y1 = c.y1 - dy[dir]; n.x1 = c.x1 - dx[dir];
					n.cnt = c.cnt + 1;
					if (n.y<1 || n.y>cN || n.x<1 || n.x>cN || n.y1<1 || n.y1>cN || n.x1<1 || n.x1>cN)continue;
					if (dir == 4 && chk[n.y][n.x][n.y1][n.x1][dir - 3] == 0) {
						if (input[n.y1][n.x1] != 1 && input[c.y1 - 1][c.x1 - 1] != 1) {//�ð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}
					else {
						if (input[n.y1][n.x1] != 1 && input[c.y1 + 1][c.x1 - 1] != 1) {//�ݽð� �̵�
							chk[n.y][n.x][n.y1][n.x1][dir - 3] = 1;
							q.push(n);
						}
					}

				}
			}
			else {//�����¿� ���
				n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
				n.y1 = c.y1 + dy[dir]; n.x1 = c.x1 + dx[dir];
				n.cnt = c.cnt + 1;
				if (n.y<1 || n.y>cN || n.x<1 || n.x>cN || n.y1<1 || n.y1>cN || n.x1<1 || n.x1>cN)continue;
				if (chk[n.y][n.x][n.y1][n.x1][0] == 0) {
					if (dir == 0 || dir == 2) {//���� �ΰ�� 
						if (input[n.y][n.x] == 0 && input[n.y1][n.x1] == 0) {
							chk[n.y][n.x][n.y1][n.x1][0] = 1;
							q.push(n);
						}
					}
					else {//�¿� �ΰ��
						if (dir == 1 & input[n.y1][n.x1] == 0) {//����
							chk[n.y][n.x][n.y1][n.x1][0] = 1;
							q.push(n);
						}
						else {
							chk[n.y][n.x][n.y1][n.x1][0] = 1;
							q.push(n);
						}
					}
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