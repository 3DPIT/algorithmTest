//#include<stdio.h>
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<string>
//#include<map>
//using namespace std;
//#define ARRSIZE 500001 //�迭 ������
//int dNum[ARRSIZE] = { 0, };//������ ������� ������ ���� �迭
//int solution(int k, vector<int>score) {
//	int answer = -1;//�����
//	map<int, int>chk;//�������� k�� �ݺ��Ǵ��� Ȯ��
//	for (int i = 2; i < score.size(); i++) {
//		dNum[i] = score[i - 1] - score[i];//�� ������ ������
//		chk[dNum[i]]++;
//	}
//	map<int, int>k_remove;//�������°� ��� ����
//	for (auto it : chk) {//k���̻��� �� �����ϱ� 
//		if (it.second >= k) {//k�� �̻��� ������ ã��
//			for (int i = 2; i < score.size(); i++) {
//				if (dNum[i] == it.first) {//������ k���̻��� �׸��̸� k_remove�� ������ѳ���
//					k_remove[i - 1]++;//k���̻��� �������� 2�϶� 1-2���ΰ��
//					k_remove[i]++;
//				}
//			}
//		}
//	}
//	answer = score.size() - k_remove.size();
//	return answer;
//}
//int main(void) {
//	cout << solution(3, { 2000000000,24, 22, 20, 10, 5, 3, 2, 1 }) << "\n";
//	cout << solution(2, { 1300000000,700000000,668239490,618239490,568239490,568239486,518239486,157658638,157658634,100000000,100 }) << "\n";
//	return 0;
//}
//
//
/////-------------------------------------------------------------------
//#include<string>
//#include<vector>
//#include<iostream>
//#include<map>
//using namespace std;
//#define CITY_NUM 10005//�ִ� ������ ����
//vector<int> G[CITY_NUM];//�׷��� �����ϱ�
//int ret = 0;//���� ���� ������ ��
//int visit[CITY_NUM];//�湮 üũ
//int chkPoint[2];//����Ȯ���� ����
//int chkidx;//���� �ľ��ϱ�����
//int destNum;//���� �ѹ�
//int hubNum;//��� �ѹ�
//void init() {//�ʱ�ȭ
//	ret = chkidx = destNum = hubNum = 0;
//	for (int i = 0; i < CITY_NUM; i++)G[i].clear();
//	memset(visit, 0, sizeof(visit, 0, sizeof(visit)));
//	memset(chkPoint, 0, sizeof(chkPoint));
//}
//void dfs(int idx, int cnt) {//���� Ž��
//	if (cnt == 2) {//�����Ұ� ���ļ� �°�� �´ٸ�
//		if (chkPoint[0] < chkPoint[1]) {//��� �湮�ѵڿ� ������ Ȯ���Ѱ��
//			ret++;
//			ret = ret % 10007;
//		}
//		return;
//	}
//	for (int i = 0; i < G[idx].size(); i++) {
//		int n = G[idx][i];
//		if (visit[n] == 0) {
//			if (destNum == n) {
//				chkPoint[1] = chkidx++;
//				cnt++;
//				visit[n] = 1;
//				dfs(n, cnt);//���� ��ġ�� �ѱ��
//				cnt--;
//				visit[n] = 0;//��Ʈ��ŷ
//				chkPoint[1] = 0;
//
//			}
//			else if (hubNum == n) {
//				chkPoint[0] = chkidx++;
//				cnt++;
//				visit[n] = 1;
//				dfs(n, cnt);//���� ��ġ�� �ѱ��
//				cnt--;
//				visit[n] = 0;//��Ʈ��ŷ
//				chkPoint[0] = 0;
//			}
//			else {
//				visit[n] = 1;
//				dfs(n, cnt);//���� ��ġ�� �ѱ��
//				visit[n] = 0;//��Ʈ��ŷ
//			}
//		}
//	}
//}
//int solution(string depar, string hub, string dest, vector<vector<string>>roads) {
//	init();//���� �ʱ�ȭ
//	int answer = -1;//�����
//	map<string, int>m;//���� ���� �˾Ƴ���
//	int idx = 0;
//	for (int i = 0; i < roads.size(); i++) {//���� �̸���� ��ȣ �ű��
//		if (m[roads[i][0]] == 0) m[roads[i][0]] = idx++;
//		if (m[roads[i][1]] == 0)m[roads[i][1]] = idx++;
//	}
//	for (int i = 0; i < roads.size(); i++) {//�׷��� �����س���
//		G[m[roads[i][0]]].push_back({ m[roads[i][1]] });
//	}
//	int start_idx = m[depar];//���� ���� ��ġ �ε���
//	hubNum = m[hub];//��� ��ȣ
//	destNum = m[dest];//���� ��ȣ
//	dfs(start_idx, 0);//dfs Ž��
//	return answer = ret;//��� ����
//}
//int main(void) {
//	cout << solution("SEOUL", "DAEGU", "YEOSU", { {"ULSAN","BUSAN"},{"DAEJEON","ULSAN"},
//		{"DAEJEON","GWANGJU"},{"SEOUL","DAEJEON"},
//		{"SEOUL","ULSAN"},{"DAEJEON","DAEGU"},
//		{"GWANGJU","BUSAN"},{"DAEGU","GWANGJU"},
//		{"DAEGU","BUSAN"},{"ULSAN","DAEGU"},
//		{"GWANGJU","YEOSU"},{"BUSAN","YEOSU"} }) << endl;
//	cout << solution("ULSAN", "SEOUL", "BUSAN", { {"SEOUL","DEAJEON"},{"ULSAN","BUSAN"},
//		{"DAEJEON","ULSAN"},{"DAEJEON","GWANGJU"},{"SEOUL","ULSAN"},{"DAEJEON","BUSAN"}
//		,{"GWANGJU","BUSAN"} }) << endl;
//
//	return 0;
//}