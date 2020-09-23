#include <string>
#include <vector>

using namespace std;
//1�ܰ� new_id�� ��� �빮�ڸ� �����Ǵ� �ҹ��ڷ� ġȯ�մϴ�.
//2�ܰ� new_id���� ���ĺ� �ҹ���, ����, ����(-), ����(_), ��ħǥ(.)�� ������ ��� ���ڸ� �����մϴ�.
//3�ܰ� new_id���� ��ħǥ(.)�� 2�� �̻� ���ӵ� �κ��� �ϳ��� ��ħǥ(.)�� ġȯ�մϴ�.
//4�ܰ� new_id���� ��ħǥ(.)�� ó���̳� ���� ��ġ�Ѵٸ� �����մϴ�.
//5�ܰ� new_id�� �� ���ڿ��̶��, new_id�� "a"�� �����մϴ�.
//6�ܰ� new_id�� ���̰� 16�� �̻��̸�, new_id�� ù 15���� ���ڸ� ������ ������ ���ڵ��� ��� �����մϴ�.
//���� ���� �� ��ħǥ(.)�� new_id�� ���� ��ġ�Ѵٸ� ���� ��ġ�� ��ħǥ(.) ���ڸ� �����մϴ�.
//7�ܰ� new_id�� ���̰� 2�� ���϶��, new_id�� ������ ���ڸ� new_id�� ���̰� 3�� �� ������ �ݺ��ؼ� ���� ���Դϴ�.

string solution(string new_id) {
	string answer = "";
	//1�ܰ� new_id�� ��� �빮�ڸ� �����Ǵ� �ҹ��ڷ� ġȯ�մϴ�.
	for (int i = 0; i < new_id.size(); i++) {
		//if ('A' <= new_id[i] && new_id[i] <= 'Z') {//�빮���̸�
		new_id[i] = tolower(new_id[i]);
		//}
	}
	//2�ܰ� new_id���� ���ĺ� �ҹ���, ����, ����(-), ����(_), ��ħǥ(.)�� ������ ��� ���ڸ� �����մϴ�.
	for (int i = 0; i < new_id.size(); i++) {
		if (!('a' <= new_id[i] && new_id[i] <= 'z')
			&& new_id[i] != '-'&&new_id[i] != '_'&&new_id[i] != '.'
			&& !('0' <= new_id[i] && new_id[i] <= '9')) {//���͵��� �ƴϸ� ����
			if (new_id.size() == 0)break;//���ŉ�µ� �ƹ����� ���°�� Ż��
			new_id.erase(new_id.begin() + i);//����
			i--;
		}
	}
	//3�ܰ� new_id���� ��ħǥ(.)�� 2�� �̻� ���ӵ� �κ��� �ϳ��� ��ħǥ(.)�� ġȯ�մϴ�.
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] == '.') {//.�� ��ġ ã��
			int j = i + 1;
			int cnt = 1;
			while (new_id[i] == new_id[j]) {//.�� ���� �ľ�
				cnt++;//.����
				j++;
			}
			if (cnt >= 2) {//2�� �̻��� ���̸�
				for (int k = 0; k < cnt - 1; k++) {//������ŭ �����
					new_id.erase(new_id.begin() + i);
				}
			}
		}
	}
	//4�ܰ� new_id���� ��ħǥ(.)�� ó���̳� ���� ��ġ�Ѵٸ� �����մϴ�.
	if (new_id.size() != 0 && new_id[0] == '.') new_id.erase(new_id.begin());// ó�� ������
	if (new_id.size() != 0 && new_id[new_id.size() - 1] == '.')new_id.erase(new_id.begin() + new_id.size() - 1);//������ �� ����
	//5�ܰ� new_id�� �� ���ڿ��̶��, new_id�� "a"�� �����մϴ�.
	if (new_id.size() == 0) {
		new_id.push_back('a');
	}
	//6�ܰ� new_id�� ���̰� 16�� �̻��̸�, new_id�� ù 15���� ���ڸ� ������ ������ ���ڵ��� ��� �����մϴ�.
	if (new_id.size() >= 16) {
		new_id.erase(new_id.begin() + 15, new_id.end());
		if (new_id.size() != 0 && new_id[new_id.size() - 1] == '.')new_id.erase(new_id.begin() + new_id.size() - 1);//������ �� ����

	}
	//7�ܰ� new_id�� ���̰� 2�� ���϶��, new_id�� ������ ���ڸ� new_id�� ���̰� 3�� �� ������ �ݺ��ؼ� ���� ���Դϴ�.
	if (new_id.size() <= 2) {
		char cs = new_id[new_id.size() - 1];//������ �� ����
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
