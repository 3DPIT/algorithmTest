#include <string>
#include <vector>

using namespace std;
int chk[100001];//선물의 종류 파악
int solution(vector<vector<int>> boxes) {
	int answer = -1;
	for (int i = 0; i < boxes.size(); i++) {
		for (int j = 0; j < boxes[i].size(); j++) {
			chk[boxes[i][j]]++;
		}
	}//정보저장
	int setChk = 0;
	for (int i = 0; i < 100001; i++) {
		if (chk[i] >= 2)setChk++;
		if (setChk == boxes.size())return 0;
	}

	return answer=boxes.size()-setChk;
}
int main(void) {
	//solution({ {1, 2}, {2, 1}, {3, 3}, {4, 5}, {5, 6}, {7, 8} });
	solution({{1, 2}, {3, 4}, {5, 6}});
	solution({{1, 2}, {2, 3}, {3, 1}});

	return 0;
}