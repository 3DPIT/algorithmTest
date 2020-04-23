#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 101
int max_R, max_C,ret;
int r, c, k;
int map[NS][NS];
int num[NS];
struct Data {
	int num, cnt;
};
bool cmp(Data a, Data b) {
	if (a.cnt == b.cnt)return a.num < b.num;
	else return a.cnt < b.cnt;
}
vector<Data>v1;

struct twoArrSum {
	twoArrSum(){
		int T;
		T = 1;
		for (int t = 1; t <= T; t++) {
			init();
			scanf("%d %d %d", &r, &c, &k);
			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {
					scanf("%d", &map[y][x]);
				}
			}
			printf("#%d %d\n", t, play());
		}
	}
	void init() {
		max_R = 3;
		max_C = 3;
		ret = 0;
	}
	int  play() {
		while (1) {
			if (map[r-1][c-1] == k) return ret;
			if (ret > 100)return -1;
			if (max_R > 100)max_R = 100;
			if (max_C > 100)max_C = 100;
			if(max_R>=max_C)
			R();
			else if(max_R<max_C)
			C();
			ret++;
		}
	}
	void R() {
		for (int i = 0; i < max_R; i++) {
			for (int j = 0; j < max_C; j++) {
				num[map[i][j]]++;
				map[i][j] = 0;
			}

				for (int k = 1;k <= 100; k++) {
					if (num[k] != 0) {
						v1.push_back({ k,num[k] });
					}
				}
				sort(v1.begin(), v1.end(), cmp);

				int ij = 0;
				for (int jj = 0; jj < v1.size(); jj++) {
					map[i][ij++] = v1[jj].num;
					map[i][ij++] = v1[jj].cnt;

				}

				int vsize = v1.size() * 2;
				if (max_C < vsize)max_C = vsize;

				
				v1.clear();
				memset(num, 0, sizeof(num));

			}
		
	}
	void C() {
		for (int j = 0; j < max_C; j++) {
			for (int i = 0; i < max_R; i++) {
					num[map[i][j]]++;
					map[i][j] = 0;

				}

					for (int k = 1; k <= 100; k++) {
						if (num[k] != 0) {
							v1.push_back({ k,num[k] });
						}
					}
					sort(v1.begin(), v1.end(), cmp);
					int ij = 0;
					for (int jj = 0; jj < v1.size(); jj++) {
						map[ij++][j] = v1[jj].num;
						map[ij++][j] = v1[jj].cnt;

					}

					int vsize = v1.size() * 2;
					if (max_R < vsize)max_R = vsize;
					v1.clear();
					memset(num, 0, sizeof(num));

				
			}
		}
	
}twoArrSum;
int main(void) {

	return 0;
}