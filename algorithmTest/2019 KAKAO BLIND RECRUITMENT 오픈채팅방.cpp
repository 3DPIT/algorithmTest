#include <string>
#include <vector>
#include<map>
#include<queue>
using namespace std;
vector<string> record1;
string temp;
vector<string>v;
map<string, string>m;
vector<string> answer;
struct Data {
	string statusUser, id;
};
queue<Data>q;
void queueData() {
	//Á¤¸® 
	if (v[0] == "Enter") {
		q.push({ v[0],v[1] });
		m[v[1]] = v[2];
	}
	if (v[0] == "Leave") {
		q.push({ v[0],v[1] });
	}
	if (v[0] == "Change") {
		m[v[1]] = v[2];
	}
}
void tempSplit(){
	for (int i = 0; i < record1.size(); i++) {
		temp.clear();
		v.clear();
		for (int j = 0; j < record1[i].size(); j++) {
			if (record1[i][j] == ' ') {// ºó°ø°£ÀÌ¸é ³ª´²ÁÖ±â
				v.push_back(temp);
				temp.clear();
			}
			else {
				temp.push_back(record1[i][j]);
			}
		}
		v.push_back(temp);
		queueData();
	}
}
void answer1() {
	while (!q.empty()) {
		Data c = q.front(); q.pop();
		if (c.statusUser == "Enter") {
			answer.push_back({ m[c.id] + "´ÔÀÌ µé¾î¿Ô½À´Ï´Ù." });
		}
		if (c.statusUser == "Leave") {
			answer.push_back({ m[c.id] + "´ÔÀÌ ³ª°¬½À´Ï´Ù." });
		}
	}
}
vector<string> solution(vector<string> record) {
	record1 = record;
	tempSplit();
	answer1();
	return answer;
}
int main(void) {
	solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan" });
	return 0;
}