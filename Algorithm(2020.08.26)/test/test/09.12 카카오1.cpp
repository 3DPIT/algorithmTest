#include <string>
#include <vector>

using namespace std;
//1단계 new_id의 모든 대문자를 대응되는 소문자로 치환합니다.
//2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
//3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
//4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
//5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
//6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
//만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
//7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.

string solution(string new_id) {
	string answer = "";
	//1단계 new_id의 모든 대문자를 대응되는 소문자로 치환합니다.
	for (int i = 0; i < new_id.size(); i++) {
		//if ('A' <= new_id[i] && new_id[i] <= 'Z') {//대문자이면
		new_id[i] = tolower(new_id[i]);
		//}
	}
	//2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
	for (int i = 0; i < new_id.size(); i++) {
		if (!('a' <= new_id[i] && new_id[i] <= 'z')
			&& new_id[i] != '-'&&new_id[i] != '_'&&new_id[i] != '.'
			&& !('0' <= new_id[i] && new_id[i] <= '9')) {//저것들이 아니면 제거
			if (new_id.size() == 0)break;//제거됬는데 아무값도 없는경우 탈출
			new_id.erase(new_id.begin() + i);//제거
			i--;
		}
	}
	//3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] == '.') {//.의 위치 찾기
			int j = i + 1;
			int cnt = 1;
			while (new_id[i] == new_id[j]) {//.의 갯수 파악
				cnt++;//.갯수
				j++;
			}
			if (cnt >= 2) {//2개 이상의 점이면
				for (int k = 0; k < cnt - 1; k++) {//갯수만큼 지우기
					new_id.erase(new_id.begin() + i);
				}
			}
		}
	}
	//4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
	if (new_id.size() != 0 && new_id[0] == '.') new_id.erase(new_id.begin());// 처음 점제거
	if (new_id.size() != 0 && new_id[new_id.size() - 1] == '.')new_id.erase(new_id.begin() + new_id.size() - 1);//마지막 점 제거
	//5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
	if (new_id.size() == 0) {
		new_id.push_back('a');
	}
	//6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
	if (new_id.size() >= 16) {
		new_id.erase(new_id.begin() + 15, new_id.end());
		if (new_id.size() != 0 && new_id[new_id.size() - 1] == '.')new_id.erase(new_id.begin() + new_id.size() - 1);//마지막 점 제거

	}
	//7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.
	if (new_id.size() <= 2) {
		char cs = new_id[new_id.size() - 1];//마지막 값 저장
		while (new_id.size() < 3) {
			new_id.push_back(cs);
		}
	}
	return answer = new_id;
}
int main(void) {
	//string a = solution("...!@BaT#*..y.abcdefghijklm.");
	//a = solution("z-+.^.");
	//string a = solution("=.=");
	//a = solution("123_.def");
	string a = solution("abcdefghijklmn.p");
}
