#include<string>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define NSIZE 101//Ű����ũ �ִ� ����

struct kiosk{
	int endTime; int cnt; int opretating; int num;
		//��Ī ������ �ð�, ��ĪȽ��,�Ȯ��,Ű����ũ ��ȣ
}K[NSIZE];//Ű����ũ
bool cmp(kiosk a, kiosk b) {
	if (a.endTime == b.endTime)return a.num < b.num;//���� ����
	return a.endTime > b.endTime;//���� ����
}

int solution(int n, vector<string>customers) {

	int answer = 0;
	
	for (int i = 0; i < customers.size(); i++) {
		vector<kiosk>a;
		//�ð� ����
		int time=0;
		string a1;a1+=customers[i][6]; a1+= customers[i][7];
		time += 3600 * stoi(a1);
		a1.clear(); a1 += customers[i][9]; a1 += customers[i][10];
		time += 60 * stoi(a1);
		a1.clear(); a1 += customers[i][12]; a1 += customers[i][13];
		time +=  stoi(a1);

			for (int ki = 1; ki <= n; ki++) {//��Ī�� Ű����ũ ����
				if (K[ki].opretating == 0) {//��� �ƴ϶��

					a.push_back({ time - 0,0,K[ki].opretating,ki });
				}
				if (K[ki].opretating == 1) {//����ð��ΰ��
					if(K[ki].endTime<=time)K[ki].opretating = 0;
				}
			}
			if (a.size() >= 2) {//������ �ΰ��
				sort(a.begin(), a.end(), cmp);
				a1.clear();
				a1 += customers[i][15]; a1 += customers[i][16];
				time += stoi(a1);
				K[a.front().num].endTime = time;
				K[a.front().num].cnt++;
				K[a.front().num].opretating = 1;\
			}
			else if (a.size() == 0) {// ����ΰ� ������
				sort(a.begin(), a.end(), cmp);
				a1.clear();
				a1 += customers[i][15]; a1 += customers[i][16];
				time += stoi(a1);
				K[a.front().num].endTime = time;
				K[a.front().num].cnt++;
				K[a.front().num].opretating = 1; 
			}
		
	}
	return answer;
}
int main(void) {
	cout << solution(3, { "10/01 23:20:25 30","10/01 23:25:50 26" ,
		"10/01 23:31:00 05" ,"10/01 23:33:17 24" ,"10/01 23:50:25 13" ,
		"10/01 23:55:45 20" ,"10/01 23:59:39 03" ,"10/02 00:10:00 10" });
	return 0;
}