#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;
	vector<int> tempArray;
	for (int  ci= 0; ci < commands.size(); ci++) {
		tempArray = array;
		int i = commands[ci][0];//i 값
		int j = commands[ci][1];//j 값
		int k = commands[ci][2];//k 값
		sort(tempArray.begin() + i - 1, tempArray.begin() + j);
		//원하는 범위만 정렬 
		//원하는 범위에서 k번째는 i+k-2 의 인덱스
		answer.push_back(tempArray[i+k-2]);
		

	}
	return answer;
}
int main(void) {
	vector<int> a =
		solution({1,5,2,6,3,7,4},{{2,5,3},{4,4,1},{1,7,3}});
	for (int i = 0; i < a.size(); i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}