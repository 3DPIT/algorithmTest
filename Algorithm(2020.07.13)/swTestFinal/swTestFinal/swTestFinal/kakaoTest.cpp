#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'countDuplicate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY numbers as parameter.
 */

int countDuplicate(vector<int> numbers) {
	int chkNum[1001] = { 0, };
	int ret = 0;//결과값
	for (int i = 0; i < numbers.size(); i++) {//검색 하는곳
		chkNum[numbers[i]]++;
	}
	for (int i = 1; i <= 1000; i++) {//중복인것 갯수 세는곳
		if (chkNum[i] >= 2)ret++;// 중복인거면 갯수 세기
	}
	return ret;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string numbers_count_temp;
	getline(cin, numbers_count_temp);

	int numbers_count = stoi(ltrim(rtrim(numbers_count_temp)));

	vector<int> numbers(numbers_count);

	for (int i = 0; i < numbers_count; i++) {
		string numbers_item_temp;
		getline(cin, numbers_item_temp);

		int numbers_item = stoi(ltrim(rtrim(numbers_item_temp)));

		numbers[i] = numbers_item;
	}

	int result = countDuplicate(numbers);

	fout << result << "\n";

	fout.close();

	return 0;
}

string ltrim(const string &str) {
	string s(str);

	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
	);

	return s;
}

string rtrim(const string &str) {
	string s(str);

	s.erase(
		find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
		s.end()
	);

	return s;
}
