#include <string>
#include <vector>
#include<queue>
#include<iostream>
using namespace std;
#define N 102
int cN;
int input[N][N];//board ������ ��������
int chk[N][N][2];//�湮üũ�� �迭
int dy[] = { -1,0,1,0,1,-1 };//��,��,��,��,�ݽð�, �ð�
int dx[] = { 0,1,0,-1,1,1 };
int ret;
struct Data {
	int y, x, dir,cnt;
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
	q.push(1, 1, 0, 0);
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