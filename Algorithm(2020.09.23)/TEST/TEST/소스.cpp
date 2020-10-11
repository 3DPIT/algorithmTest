//#include<stdio.h>
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<string>
//#include<map>
//using namespace std;
//#define ARRSIZE 500001 //배열 사이즈
//int dNum[ARRSIZE] = { 0, };//인접된 등수사이 점수차 저장 배열
//int solution(int k, vector<int>score) {
//	int answer = -1;//결과값
//	map<int, int>chk;//점수차이 k번 반복되는지 확인
//	for (int i = 2; i < score.size(); i++) {
//		dNum[i] = score[i - 1] - score[i];//각 인접된 점수차
//		chk[dNum[i]]++;
//	}
//	map<int, int>k_remove;//지워지는거 등수 저장
//	for (auto it : chk) {//k번이상인 것 제거하기 
//		if (it.second >= k) {//k번 이상인 점수차 찾기
//			for (int i = 2; i < score.size(); i++) {
//				if (dNum[i] == it.first) {//점수차 k번이상인 항목이면 k_remove에 저장시켜놓기
//					k_remove[i - 1]++;//k번이상인 점수차가 2일때 1-2등인경우
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
//#define CITY_NUM 10005//최대 도시의 개수
//vector<int> G[CITY_NUM];//그래프 구현하기
//int ret = 0;//최종 으로 나오는 값
//int visit[CITY_NUM];//방문 체크
//int chkPoint[2];//순서확인을 위함
//int chkidx;//순서 파악하기위함
//int destNum;//도착 넘버
//int hubNum;//허브 넘버
//void init() {//초기화
//	ret = chkidx = destNum = hubNum = 0;
//	for (int i = 0; i < CITY_NUM; i++)G[i].clear();
//	memset(visit, 0, sizeof(visit, 0, sizeof(visit)));
//	memset(chkPoint, 0, sizeof(chkPoint));
//}
//void dfs(int idx, int cnt) {//깊이 탐색
//	if (cnt == 2) {//도착할것 거쳐서 온경우 맞다면
//		if (chkPoint[0] < chkPoint[1]) {//허브 방문한뒤에 도착지 확신한경우
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
//				dfs(n, cnt);//다음 위치로 넘기기
//				cnt--;
//				visit[n] = 0;//백트래킹
//				chkPoint[1] = 0;
//
//			}
//			else if (hubNum == n) {
//				chkPoint[0] = chkidx++;
//				cnt++;
//				visit[n] = 1;
//				dfs(n, cnt);//다음 위치로 넘기기
//				cnt--;
//				visit[n] = 0;//백트래킹
//				chkPoint[0] = 0;
//			}
//			else {
//				visit[n] = 1;
//				dfs(n, cnt);//다음 위치로 넘기기
//				visit[n] = 0;//백트래킹
//			}
//		}
//	}
//}
//int solution(string depar, string hub, string dest, vector<vector<string>>roads) {
//	init();//변수 초기화
//	int answer = -1;//결과값
//	map<string, int>m;//현재 도시 알아내기
//	int idx = 0;
//	for (int i = 0; i < roads.size(); i++) {//도시 이름대신 번호 매기기
//		if (m[roads[i][0]] == 0) m[roads[i][0]] = idx++;
//		if (m[roads[i][1]] == 0)m[roads[i][1]] = idx++;
//	}
//	for (int i = 0; i < roads.size(); i++) {//그래프 생성해놓음
//		G[m[roads[i][0]]].push_back({ m[roads[i][1]] });
//	}
//	int start_idx = m[depar];//현재 시작 위치 인덱스
//	hubNum = m[hub];//허브 번호
//	destNum = m[dest];//도착 번호
//	dfs(start_idx, 0);//dfs 탐색
//	return answer = ret;//결과 리턴
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