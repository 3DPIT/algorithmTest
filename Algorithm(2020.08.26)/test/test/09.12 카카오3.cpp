#include <string>
#include <vector>
#include <string.h>
using namespace std;
string num[50001];//숫자저장
int chk[50001];//충족하는 것 확인 배열
vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;
	int size = info.size();
	char cInfo[50001][5];//인포의 내용 정리하는 백터
	for (int i = 0; i < info.size(); i++) {//표로 만들기
		cInfo[i][0] = info[i][0];
		int idx = 1;
		for (int j = 0; j < info[i].size(); j++) {
			if (info[i][j] == ' ') {//스페이스 구간
				if ('0' <= info[i][j+1] && info[i][j+1] <= '9') {//숫자라면
					for (int k = j+1; k < info[i].size(); k++) {
						num[i] += info[i][k];//숫자 따로 저장
					}
					break;
				}
				else {
					cInfo[i][idx++] = info[i][j + 1];//앞자리 저장
					j++;
				}
			}
		}
	}
	for (int i = 0; i < query.size(); i++) {
		int cnt = 0;//조건 요소 맞는지 파악
		int acnt = 0;//조건을 만족하는 것 카운트
		string a;//마지막 숫자 저장
		int k = 0;//인덱스 넘기기위한 변수
		for (int j = 0; j < query[i].size(); j++) {
			char chkChar;
			//가장 앞 문자 찾기
			if (j == 0) {//초기값 저장
				chkChar = query[i][j];
			}
			else if (j != 0) {
					while (query[i][j] != ' ') {
						j++;
					}
					if ('0' <= query[i][j + 1] && query[i][j + 1] <= '9') {//숫자의 위치라면
						for (; j < query[i].size(); j++) {
							a += query[i][j];
						}
					}
					else {
						j += 5;
						chkChar = query[i][j];//값 저장
					}
			}
			
			for (int i = 0; i < info.size(); i++) {//기록 체크
				if(k<=3)
					if (chkChar=='-'||chkChar == cInfo[i][k])chk[i]++;
				if (k == 4)
					if (stoi(num[i]) >= stoi(a))chk[i]++;
				if (chk[i] == 5)acnt++;//만족하는것 카운트하기
			}
			k++;
		}

		memset(chk, 0, sizeof(chk));//초기화
		answer.push_back(acnt);//리턴값 저장
	}
	return answer;
}
int main(void) {
	solution({"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"},
		{"cpp and - and senior and pizza 250","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"});
}