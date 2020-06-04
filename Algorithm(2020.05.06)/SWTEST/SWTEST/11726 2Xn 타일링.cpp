//#include<stdio.h>
//#include<iostream>
//#include<string.h>
//#include<string>
//#include<vector>
//using namespace std;
//#define S 1004
//int D[S];
//int n;
//int dfs(int d) {
//	if (d == 0) {
//		return 1;
//	}
//	if (D[d] != -1)return D[d];
//	D[d] = (dfs(d - 1) + 2*(dfs(d - 2))) % 10007;
//	return D[d];
//}
//void init() {
//	scanf("%d", &n);
//}
//int main(void) {
//	init();
//
//	memset(D, -1, sizeof(D));
//	cout<<dfs(n)<<endl;
//	/*for (int i = 2; i <= n; i++) {
//		D[i] = (D[i - 1] + 2 * (D[i - 2])) % 10007;
//	}*/
//	//cout << D[n];
//
//	return 0;
//}


#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
int ret = 0x80000000;
void copy(int cboard[11][11], vector<vector<int> >board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			cboard[i][j] = board[i][j];
		}
	}
}
int solution(vector<vector<int> >board) {
	int answer = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			vector<vector<int> >c;
			int cc[11][11] = { 0, };
			c = board;
			copy(cc, board);
			
			cc[i][j] = 0;
			int cnt = 1;
			while (1) {
				int flag = 0;
				for (int x = 0; x < c.size(); x++) {
					vector<int>a;

					//내리는 소스 
					for (int y = 0; y < c.size(); y++) {
						if (cc[y][x] != 0) {
							a.push_back(cc[y][x]);
							cc[y][x] = 0;
						}
					}
					int y = c.size() - 1;
					for (int yy = a.size() - 1; yy >= 0; yy--) {
						cc[y--][x] = a[yy];// 사탕 내리기
					}
					/////

				}
				int chk[11][11] = { 0, };

				for (int y = 0; y < c.size(); y++) {
					int cx = 1;
					for (int x = 0; x < c.size() - 1; x++) {
						int copynum = cc[y][x];
						if (copynum == 0)continue;
						chk[y][x] = 1;
						int ccnt = 0;
						cx = x;
						while (cc[y][cx] == cc[y][cx + 1]) {
							chk[y][cx+1] = 1;
							ccnt++;
							cx++;

						}//
						if (ccnt < 3) {
							for (int aa = x; aa <= cx; aa++) {
								chk[y][aa] = 0;
							}
						}
						else {
							x = cx;
						}
					}
				}

				for (int x = 0; x < c.size(); x++) {
					int cy = 1;
					for (int y = 0; y < c.size() - 1;y++) {
						int copynum = cc[y][x];
						if (copynum == 0)continue;	
						if (chk[y][x] != 1)
							chk[y][x] = 2;

						int ccnt = 1;
						cy = y;
						while (cc[cy][x] == cc[cy+1][x]) {
							if(chk[cy+1][x]!=1)
							chk[cy+1][x] = 2;
							ccnt++;
							cy++;

						}//
						if (ccnt < 3) {
							for (int aa = y; aa <= cy; aa++) {
								if(chk[aa][x]==2)
								chk[aa][x] = 0;
							}
						}
						else {
							y = cy;
						}
					}
				}

				for (int y = 0; y < c.size(); y++) {
					for (int x = 0; x < c.size(); x++) {
						if (chk[y][x] != 0) {
							cnt++;
							cc[y][x] = 0;
							flag = 1;
						}
					}
				}

				if (flag == 0)break;
				flag = 0;



			}/////반복 
			if (ret < cnt)ret = cnt;

		}

	}
	return answer=ret;

}
int main(void) {
	cout << solution({ { 1,1,3,3 }, { 4,1,3,4 }, { 1,2,1,1 }, { 2,1,3,2 } });
	return 0;
}




