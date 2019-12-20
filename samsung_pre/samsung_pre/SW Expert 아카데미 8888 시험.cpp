#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
#define NS 2002
int ret;
int N, T, P;
struct Data {
	int score, zeroProblem, correctProblem, num;
};
bool cmp(Data a, Data b) {
	return a.score > b.score;
}
Data v[NS];
int input[NS][NS];
void init() {

}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testCase;

	cin >> testCase;
	for (int tc = 1; tc <= testCase; tc++) {
		memset(input, 0, sizeof(input));
		memset(v, 0, sizeof(v));
		ret = 0;
		cin >> N >> T >> P;
		//scanf("%d %d %d", &N, &T, &P);
		vector<int>z;
		vector<int>c;
		vector<int>vi[NS];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < T; j++) {
				scanf("%d", &input[i][j]);
				v[i].num = i;
				if (input[i][j] == 0) {
					v[j].zeroProblem++;
				}
				else {
					vi[i].push_back(j);
					v[i].correctProblem++;
				}
			}
		}
		for (int j = 0; j < vi[P - 1].size(); j++) {
			v[P - 1].score += v[vi[P - 1][j]].zeroProblem;
		}

		for (int i = 0; i < N; i++) {
			if (i == P - 1)continue;
			for (int j = 0; j < vi[i].size(); j++) {
				v[i].score += v[vi[i][j]].zeroProblem;
			}
			int num = v[P - 1].score;
			if (v[i].score < num)break;
			if (v[i].score > num)ret++;
			if (v[i].score == num && v[i].correctProblem > v[P - 1].correctProblem)ret++;
			if (v[i].score == num && i < P - 1)ret++;
		}
		ret++;

		cout << '#' << ' ' << tc << ' ' << v[P - 1].score << ' ' << ret << endl;
		//printf("#%d %d %d\n", tc, v[P - 1].score, ret);
	}
	return 0;
}