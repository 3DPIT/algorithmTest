
#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
int N, ret;// ���ڼ�, �����
int dy[] = { 1,-1,0,0 };
int dx[] = { 0,0,-1,1 };
struct Data {
	int y, x, dir, energy;
};
//int board[4005][4005];
vector<Data>board;
void init() {
	N = ret = 0;
	board.clear();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int x, y, dir, energy;
		scanf("%d %d %d %d", &x, &y, &dir, &energy);
		board.push_back({ y * 2, x * 2, dir, energy });
	}
}
bool cmp(Data a, Data b) {
	if (a.y == b.y)return a.x < b.x;
	return a.y < b.y;
}
void play() {
	int time = 4001;
	while (board.size() != 0) {//���� �� ���� �ݺ�
		for (int i = 0; i < board.size(); i++) {//���忡 �ִ� ���ڼ� ��ŭ ������
			if (board.size() == 0)break;//������ Ż��
			Data n;
			board[i].y = board[i].y + dy[board[i].dir];//�̵� ��Ű��
			board[i].x = board[i].x + dx[board[i].dir];
			if (board[i].y == -2001 || board[i].x == -2001 || board[i].y == 2001 || board[i].x == 2001) {//������ �Ѿ�� ��� ���ֱ�
				board.erase(board.begin() + i);
				i--;
			}
		}
		//���� ��ġ ���� Ȯ��
		sort(board.begin(), board.end(), cmp);//�ϴ� ����
		for (int i = 0; i < board.size() - 1; i++) {
			if (board.size() == 0)break;
			int cnt = 0; int cj = 0;//������ ������ j��
			for (int j = i + 1; j < board.size(); j++) {
				if (board[i].y == board[j].y&&
					board[i].x == board[j].x) {
					ret += board[j].energy;
					cnt++;
				}
				else {
					break;
				}
			}
			if (cnt != 0) {//�ߺ��ΰ� ������
				ret += board[i].energy;
				board.erase(board.begin() + i, board.begin() + cnt + i + 1);//����
				i--;
			}
		}
	}
}
int main()
{
	//ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);
	int test_case;
	int T;
	cin >> T;
	//	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		T = 1;
		play();
		printf("#%d %d\n", test_case, ret);

	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}