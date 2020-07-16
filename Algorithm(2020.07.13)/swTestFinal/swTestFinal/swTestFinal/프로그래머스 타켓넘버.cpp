#include <string>
#include <vector>
#include <queue>
#include<iostream>
#include<string>
#include<map>
using namespace std;
int ret = 0;//ÃÖÁ¾°ª
int d[21] = { 0 };
void dfs(int idx,int &target,vector<int>&numbers) {
	if (idx == numbers.size()) {

		int num = 0;
		for (int i = 0; i < numbers.size();i++) {
			num += numbers[i] * d[i];
		}
		if (num == target) ret++;
		return;
	}
	d[idx] = 1;
	dfs(idx + 1, target, numbers);
	d[idx] = -1;
	dfs(idx + 1, target, numbers);	

}
int solution(vector<int> numbers, int target) {
	int answer = 0;
	dfs(0, target, numbers);
	return answer=ret;
}
int main(void) {
	cout << solution({ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, 3);
	return 0;
}