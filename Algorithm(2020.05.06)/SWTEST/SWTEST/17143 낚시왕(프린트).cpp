#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
#define NS 101
#define MS 101
int N, M, K;
int ret;
struct Data {
	int y, x, s, d, z;
};
vector<Data>v;
void init() {
	N = M = K = ret = 0;
	v.clear();
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++) {
		Data c;
		scanf("%d %d %d %d %d", &c.y, &c.x, &c.s, &c.d, &c.z);
		v.push_back(c);
	}
}
bool cmp(Data a, Data b) {
	if (a.y == b.y) {
		return a.x < b.x;
	}
	return a.y < b.y;
}
bool cmp1(Data a, Data b) {
	if (a.y == b.x&&a.y <= b.x) return a.z > b.z;
}
void P(string name, int idx) {
	cout << name << endl;
	if (idx == 0) {
		for (int i = 0; i < v.size(); i++) {
			printf("%d %d %d", v[i].y, v[i].x, v[i].z);
			cout << endl;
		}
	}
}
int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0, 0,0,1,-1 };
bool safe(int y, int x) {
	return 1 <= y && y <= N && 1 <= x && x <= M;
}
void eat(int x) {
	for (int k = 0; k < v.size(); k++) {
		if (v[k].x == x) {
			ret += v[k].z;
			v.erase(v.begin() + k);
			break;
		}
	}
}
void equlPosEat() {
	for (int k = 0; k < v.size() - 1; k++) {
		if (v.size() == 0)break;
		if (v[k].y == v[k + 1].y&&v[k].x == v[k + 1].x) {
			if (v[k].z < v[k + 1].z) {
				v[k] = v[k + 1];
				v.erase(v.begin() + k + 1);
				k--;
			}
			else {
				v.erase(v.begin() + k + 1);
				k--;
			}
		}
	}
}
void fishing() {
	for (int i = 1; i <= M; i++) {
		if (v.size() == 0) break;
		sort(v.begin(), v.end(), cmp);
		eat(i);
		//cout << ret << endl;
		for (int k = 0; k < v.size(); k++) {
			Data n;
			n.y = v[k].y;
			n.x = v[k].x;
			n.d = v[k].d;
			if (v[k].d == 1 || v[k].d == 2) {
				n.s = v[k].s % ((N * 2) - 2);
			}
			else {
				n.s = v[k].s % ((M * 2) - 2);
			}
			for (int t = 0; t < n.s; t++) {
				n.y += dy[n.d]; n.x += dx[n.d];
				if (!safe(n.y, n.x)) {
					n.y -= dy[n.d];
					n.x -= dx[n.d];
					if (n.d == 1) {
						n.d = 2;
					}
					else if (n.d == 2) {
						n.d = 1;
					}
					else if (n.d == 3) {
						n.d = 4;
					}
					else if (n.d == 4) {
						n.d = 3;
					}
					n.y += dy[n.d];
					n.x += dx[n.d];
				}

			}
			v[k].y = n.y;
			v[k].x = n.x;
			v[k].d = n.d;
		}
		//cout << i << endl;
		sort(v.begin(), v.end(), cmp);
		//P("벡터정렬확인", 0);
		equlPosEat();
		//P("같은게 있으면 정렬후", 0);


	}
}
int main(void) {
	int T = 1;
	for (int t = 1; t <= T; t++) {
		init();
		fishing();
		printf("#%d %d\n", t, ret);
		printf("%d\n", ret);
	}

	return 0;
}