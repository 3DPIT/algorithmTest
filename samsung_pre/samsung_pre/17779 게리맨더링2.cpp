#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 21
int map[NS][NS];
int input[NS][NS];
int ret[NS];
int N;
int chk[NS][NS];

int r = 0x7fffffff;
struct elect {
	struct Data {
		int y, x;
	};
	bool safe(int y, int x) {
		return (1 <= y && y <= N && 1 <= x && x <= N);
	}
	int flag = 0;
	void areaWrite(int y, int x, int d1, int d2) {// 성공 문제
		flag = 0;
		memset(chk, 0, sizeof(chk));
		vector<Data>v;
		vector<Data>v1;
		//one
		for (int i = y, j = x; i <= y + d1 && j >= x - d1; i++, j--) {
			if (i<1 || i>N || j<1 || j>N) {
				flag = 1; return;
			}
			v.push_back({ i,j });
			map[i][j] = 5;
		}
		//three
		for (int i = y + d1 + 1, j = x - d1 + 1; i <= y + d1 + d2 && j <= x - d1 + d2; i++, j++) {
			if (i<1 || i>N || j<1 || j>N) {
				flag = 1; return;
			}
			v.push_back({ i,j });
			map[i][j] = 5;
		}
		if (flag == 1)return;
		//two
		for (int i = y, j = x; i <= y + d2 && j <= x + d2; i++, j++) {
			if (i<1 || i>N || j<1 || j>N) {
				flag = 1; return;
			}
			v1.push_back({ i,j });
			map[i][j] = 5;
		}
		if (flag == 1)return;

		//four
		for (int i = y + d2 + 1, j = x + d2 - 1; i <= y + d2 + d1 && j >= x + d2 - d1; i++, j--) {
			if (i<1 || i>N || j<1 || j>N) {
				flag = 1; return;
			}
			v1.push_back({ i,j });
			map[i][j] = 5;
		}

		for (int i = 0; i < v.size(); i++) {
			for (int ii = v[i].y; ii <= v1[i].y; ii++) {
				for (int jj = v[i].x; jj <= v1[i].x; jj++) {
					map[ii][jj] = 5;
				}
			}
		}
	}
	elect() {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &input[i][j]);
			}
		}

		for (int d1 = 1; d1 <= N; d1++) {
			for (int d2 = 1; d2 <= N; d2++) {
				for (int i = 1; i <= N; i++) {
					for (int j = 1; j <= N; j++) {


						memset(map, 0, sizeof(map));
						memset(chk, 0, sizeof(chk));
						//	vector<Data>v;
						//	vector<Data>v1;
						///*	i = 2;
						//	j = 5;
						//	d1 = 3;
						//	d2 = 2;*/
						//	int flag = 0;
						//	for (int y = i,x=j; y <= i + d1&&x>=j-d1; y++,x--) {
						//		if (!safe(y, x)) {
						//			flag = 1; break;
						//		}
						//		map[y][x] = 5;
						//		if (chk[y][x] == 0) {
						//			chk[y][x] = 1;
						//			v.push_back({ y,x });
						//		}
						//	}
						//	if (flag)continue;

						//	for (int y = i + d1, x = j - d1; y <= i + d1 + d2 && x <= j - d1 + d2; y++, x++) {
						//		if (!safe(y, x)) {
						//			flag = 1; break;
						//		}
						//		map[y][x] = 5;
						//		if (chk[y][x] == 0) {
						//			chk[y][x] = 1;
						//			v.push_back({ y,x });
						//		}
						//	}
						//	if (flag)continue;

						//	for (int y = i, x = j; y <= i + d1&&x<=j+d2; y++,x++) {
						//		if (!safe(y, x)) {
						//			flag = 1; break;
						//		}
						//		map[y][x] = 5;
						//		if (chk[y][x] !=2) {
						//			chk[y][x] = 2;
						//			v1.push_back({ y,x });
						//		}
						//	}
						//	if (flag)continue;

						//	for (int y = i + d2, x = j + d2; y <= i + d1 + d2 && x >= j +d2 - d1; y ++,x--) {
						//		if (!safe(y, x)) {
						//			flag = 1; break;
						//		}
						//		map[y][x] = 5;
						//		if (chk[y][x] !=2) {
						//			chk[y][x] = 2;
						//			v1.push_back({ y,x });
						//		}
						//	}
						//	if (flag)continue;
						//	if (v.size() != v1.size())continue;
						//	int flag2 = 1;
						//	for (int i = 0; i < v.size(); i++) {
						//		for (int ii = v[i].y; ii <= v1[i].y; ii++) {
						//			for (int jj = v[i].x; jj <= v1[i].x; jj++) {
						//				map[ii][jj] = 5;
						//			}
						//		}
						//	}
						int flag2 = 0;
						areaWrite(i, j, d1, d2);
						if (flag == 1)continue;
						for (int y = 1; y < i + d1; y++) {
							for (int x = 1; x <= j; x++) {
								if (map[y][x] == 0) {
									map[y][x] = 1;
								}
								if (flag2 == 0)
									flag2++;
							}
						}//1

						for (int y = 1; y <= i + d2; y++) {
							for (int x = j + 1; x <= N; x++) {
								if (map[y][x] == 0) {
									map[y][x] = 2;
								}
								if (flag2 == 1)
									flag2++;
							}
						}//2%

						for (int y = i + d1; y <= N; y++) {
							for (int x = 1; x < j - d1 + d2; x++) {
								if (map[y][x] == 0) {
									map[y][x] = 3;
								}
								if (flag2 == 2)
									flag2++;
							}
						}//3

						for (int y = i + d2 + 1; y <= N; y++) {
							for (int x = j - d1 + d2; x <= N; x++) {
								if (map[y][x] == 0) {
									map[y][x] = 4;
								}
								if (flag2 == 3)
									flag2++;
							}
						}//4
					/*	printf("\n");
						for (int ii = 1; ii <= N; ii++) {
							for (int ji = 1; ji <= N; ji++) {
								printf("%d ", map[ii][ji]);
							}
							printf("\n");
						}
						printf("\n");*/
						if (flag2 != 4)continue;
						int Max = 0x80000000;

						int Min = 0x7fffffff;
						memset(ret, 0, sizeof(ret));
						for (int ii = 1; ii <= N; ii++) {
							for (int ji = 1; ji <= N; ji++) {
								ret[map[ii][ji]] += input[ii][ji];
							}
						}
						for (int ii = 1; ii <= 5; ii++) {
							if (Min > ret[ii])Min = ret[ii];
							if (Max < ret[ii])Max = ret[ii];
						}
						if (r > Max - Min)r = Max - Min;
					}

				}

			}
		}
	}
}elect;
int main(void) {
	cout << r << endl;
	return 0;
}




