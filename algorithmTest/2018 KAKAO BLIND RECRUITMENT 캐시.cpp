
#include <vector>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
// (!stricmp(cache[i].c_str(), data.c_str())) { // 대소문자를 구분하지 않고 문자열 비교
struct Data {
	string C; int cnt;
};

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
	vector<Data>LRU;
	for (int i = 0; i < cities.size(); i++) {// 대문자로 전부 변환
		string a;
		for (int j = 0; j < cities[i].size(); j++) {
			a += toupper(cities[i][j]);
		}
		cities[i] = a;
	}

	for (int i = 0; i < cities.size(); i++) {
		if (cacheSize == 0) {
			return cities.size() * 5;
		}
		if (LRU.size() < cacheSize) {
			int flag = 0;
			for (int j = 0; j < LRU.size(); j++) {// 있는지 확인 
				if (!(strcmp(cities[i].c_str(), LRU[j].C.c_str()))) {//있으면 hit
					flag = 1;
					answer += 1;
					break;
				}
			}
			if (flag == 0) {
				LRU.push_back({ cities[i],0 });
				answer += 5;
			}
		}

		else {
			int maxCnt = 0x80000000;
			int idx = 0;
			for (int k = 0; k < cacheSize; k++) {
				int cnt = 0;
				for (int j = i; j >= 0; j--) {
					if (!strcmp(cities[j].c_str(), LRU[k].C.c_str())) {
						if (maxCnt < cnt) {
							maxCnt = cnt;
							idx = k;
						}
						break;
					}
					else {
						cnt++;
					}

				}
			}//가장 최근에 사용하지 않는 것 찾기;
			int flag = 0;
			for (int j = 0; j < LRU.size(); j++) {
				if (!strcmp(LRU[j].C.c_str(), cities[i].c_str())) {
					answer += 1;
					flag = 1;
					break;
				}
			}
			if (flag==0) {
				//int idx = searchIdx(i, cacheSize, LRU, cities);
				answer += 5;
				LRU[idx].C= cities[i];
			}

		}
	}
	return answer;
}
int main(void)
{
	cout << solution(0, { "Jeju", "Pangyo", "NewYork", "newyork" });
	return 0;
}