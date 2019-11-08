#include <string>
#include <vector>
#include <queue>
#include<iostream>
#include<string.h>
using namespace std;
#define NS 31
#define MS 31
int chk[MS][NS];
int cnt = 0;
void search(int i, int j, vector<string> board,int m,int n){// 찾기
	char chkBlock = board[i][j];
	if (chkBlock ==' ')return ;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			int ny = i + y; int nx = j + x;
			if (ny < 0 || ny >= m || nx < 0 || nx >= n)return ;
			if (chkBlock!= board[ny][nx]) {
				return ;
			}
		}
	}
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			chk[y + i][x + j] = 1;
		}
	}
}
vector<string> downBlock(int m,int n,vector<string>board) {//블록 내리기
	for (int x = 0; x < n; x++) {
		queue<char>q;
		for (int y = m - 1; y >= 0; y--) {
			if (board[y][x] != ' ') {
				q.push(board[y][x]);
				board[y][x] = ' ';
			}
		}
		int y = m-1;
		while (!q.empty()) {
			board[y--][x] = q.front(); q.pop();
		}

	}
	return board;
}
vector<string> delBlock(int m,int n,vector<string> board) {//블록 지우기
	cnt = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (chk[i][j] == 1) {
				cnt++;
				chk[i][j] = 0;
				board[i][j] = ' ';
			}
		}
	}

	return board = downBlock(m, n, board);//블록 내리기 시작
}
int solution(int m, int n, vector<string> board) {// 문제 솔루션
	int answer = 0;
	while (1) {
		memset(chk, 0, sizeof(chk));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				search(i, j, board,m,n);
			}
		}
		board=delBlock(m, n, board);//블록 지우기 시작
		if (cnt!=0) {
			answer += cnt;
		}
		else {
			break;
		}
	}
	return answer;
}
int main(void) {
	int a = solution(4, 5, { "CCBDE", "AAADE", "AAABF", "CCBBF" });
		cout << a<<endl;
		
	//int	a = solution(6, 6, { "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ" });
	//	cout << a<<endl;
}