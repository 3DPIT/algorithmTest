#include <string>
#include <vector>
#include <queue>
using namespace std;
int dy[] = {0,0,-1,1,0,0,-1,1,0 };//���� ����
int dx[] = {0,-1,0,0,1,-1,0,0,1 };
struct Data {
	int y, x,cnt,removeImage,image;
};
bool safe(int y, int x) {//���� ����
	return 0 <= y && y < 4 && 0 <= x && x < 4;
}
int solution(vector<vector<int>> board, int r, int c) {
	//���� ��, Ŀ�� ��ġ
	int answer = 0;
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] != 0)cnt++;
		}
	}
	cnt /= 2;//�׸��� ��
	queue<Data>q;
	int visit[4][4][8];
	q.push({ r,c,0,0,0});
	visit[r][c][0] = 1;

	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.removeImage == cnt) {
			answer = c.cnt;
			break;//Ż�� (�ּҰ�)
		}
		for (int i = 1; i <= 9; i++) {
			Data n;
			n.y = c.y + dy[i]; n.x = c.x + dx[i];
			if (board[c.y][c.x] != 0) {//��ġ�� ���� 
				if (1 <= i && i <= 4) {

					if (safe(n.y, n.x) && visit[n.y][n.x][i] == 0) {
						if (c.image != 0 && c.image == n.image) {//������°��
							n.removeImage++;
						}
						visit[n.y][n.x][i] = 1;
						n.cnt = c.cnt + 2;
						n.image = board[c.y][c.x];//�̹��� Ŭ��
						q.push(n);
					}
				}
				else {//��Ʈ���̶� ���� �������
					while (1) {
						if (!safe(n.y, n.x)||board[n.y][n.x] != 0  ) {
							if(!safe(n.y, n.x)) n.y -= dy[i]; n.x -= dx[i];//��ĭ�ڷ�
							break;
						}
						n.y += dy[i]; n.x += dx[i];//�̵�
					}
					if (safe(n.y, n.x) && visit[n.y][n.x][i] == 0) {
						visit[n.y][n.x][i] = 1;
						n.cnt = c.cnt + 1;
						q.push(n);
					}

				}
			}
			else {//���� �ƴѰ��
				if (1 <= i && i <= 4) {
					if (safe(n.y, n.x) && visit[n.y][n.x][i] == 0) {
						visit[n.y][n.x][i] = 1;
						n.cnt = c.cnt + 1;
						q.push(n);
					}
				}
				else {//��Ʈ���̶� ���� �������
					while (1) {
						if (board[n.y][n.x] != 0 || !safe(n.y, n.x)) {
							if (!safe(n.y, n.x)) n.y -= dy[i]; n.x -= dx[i];//��ĭ�ڷ�
							break;
						}
						n.y += dy[i]; n.x += dx[i];//�̵�
						if (safe(n.y, n.x) && visit[n.y][n.x][i] == 0) {
							visit[n.y][n.x][i] = 1;
							n.cnt = c.cnt + 1;
							q.push(n);
						}
					}
				}
			}
		}
	}
	return answer;
}
int main(void) {
	solution({{1, 0, 0, 3}, {2, 0, 0, 0}, {0, 0, 0, 2}, {3, 0, 1, 0}}, 1, 0);
}