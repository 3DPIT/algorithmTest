#include <string>
#include <vector>
#include <string.h>
using namespace std;
string num[50001];//��������
int chk[50001];//�����ϴ� �� Ȯ�� �迭
vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;
	int size = info.size();
	char cInfo[50001][5];//������ ���� �����ϴ� ����
	for (int i = 0; i < info.size(); i++) {//ǥ�� �����
		cInfo[i][0] = info[i][0];
		int idx = 1;
		for (int j = 0; j < info[i].size(); j++) {
			if (info[i][j] == ' ') {//�����̽� ����
				if ('0' <= info[i][j+1] && info[i][j+1] <= '9') {//���ڶ��
					for (int k = j+1; k < info[i].size(); k++) {
						num[i] += info[i][k];//���� ���� ����
					}
					break;
				}
				else {
					cInfo[i][idx++] = info[i][j + 1];//���ڸ� ����
					j++;
				}
			}
		}
	}
	for (int i = 0; i < query.size(); i++) {
		int cnt = 0;//���� ��� �´��� �ľ�
		int acnt = 0;//������ �����ϴ� �� ī��Ʈ
		string a;//������ ���� ����
		int k = 0;//�ε��� �ѱ������ ����
		for (int j = 0; j < query[i].size(); j++) {
			char chkChar;
			//���� �� ���� ã��
			if (j == 0) {//�ʱⰪ ����
				chkChar = query[i][j];
			}
			else if (j != 0) {
					while (query[i][j] != ' ') {
						j++;
					}
					if ('0' <= query[i][j + 1] && query[i][j + 1] <= '9') {//������ ��ġ���
						for (; j < query[i].size(); j++) {
							a += query[i][j];
						}
					}
					else {
						j += 5;
						chkChar = query[i][j];//�� ����
					}
			}
			
			for (int i = 0; i < info.size(); i++) {//��� üũ
				if(k<=3)
					if (chkChar=='-'||chkChar == cInfo[i][k])chk[i]++;
				if (k == 4)
					if (stoi(num[i]) >= stoi(a))chk[i]++;
				if (chk[i] == 5)acnt++;//�����ϴ°� ī��Ʈ�ϱ�
			}
			k++;
		}

		memset(chk, 0, sizeof(chk));//�ʱ�ȭ
		answer.push_back(acnt);//���ϰ� ����
	}
	return answer;
}
int main(void) {
	solution({"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"},
		{"cpp and - and senior and pizza 250","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"});
}