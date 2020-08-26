#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'priceCheck' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY products
 *  2. FLOAT_ARRAY productPrices
 *  3. STRING_ARRAY productSold
 *  4. FLOAT_ARRAY soldPrice
 */

int priceCheck(vector<string> products, vector<float> productPrices, vector<string> productSold, vector<float> soldPrice) {
	int errorChk = 0;// 에러 항목 저장
	for (int i = 0; i < productSold.size(); i++) {// 판매항목 비교
		for (int j = 0; j < products.size(); j++) {//품목 하나씩 비교하기
			if (productSold[i] == products[j]) {//같은 목룍을 찾은 경우
				if (soldPrice[i] != productPrices[j])errorChk++;//에러항목 증가
			 }
		}
	}
	return errorChk;//에러 항목 리턴
}
int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string products_count_temp;
	getline(cin, products_count_temp);

	int products_count = stoi(ltrim(rtrim(products_count_temp)));

	vector<string> products(products_count);

	for (int i = 0; i < products_count; i++) {
		string products_item;
		getline(cin, products_item);

		products[i] = products_item;
	}

	string productPrices_count_temp;
	getline(cin, productPrices_count_temp);

	int productPrices_count = stoi(ltrim(rtrim(productPrices_count_temp)));

	vector<float> productPrices(productPrices_count);

	for (int i = 0; i < productPrices_count; i++) {
		string productPrices_item_temp;
		getline(cin, productPrices_item_temp);

		float productPrices_item = stof(ltrim(rtrim(productPrices_item_temp)));

		productPrices[i] = productPrices_item;
	}

	string productSold_count_temp;
	getline(cin, productSold_count_temp);

	int productSold_count = stoi(ltrim(rtrim(productSold_count_temp)));

	vector<string> productSold(productSold_count);

	for (int i = 0; i < productSold_count; i++) {
		string productSold_item;
		getline(cin, productSold_item);

		productSold[i] = productSold_item;
	}

	string soldPrice_count_temp;
	getline(cin, soldPrice_count_temp);

	int soldPrice_count = stoi(ltrim(rtrim(soldPrice_count_temp)));

	vector<float> soldPrice(soldPrice_count);

	for (int i = 0; i < soldPrice_count; i++) {
		string soldPrice_item_temp;
		getline(cin, soldPrice_item_temp);

		float soldPrice_item = stof(ltrim(rtrim(soldPrice_item_temp)));

		soldPrice[i] = soldPrice_item;
	}

	int result = priceCheck(products, productPrices, productSold, soldPrice);

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
