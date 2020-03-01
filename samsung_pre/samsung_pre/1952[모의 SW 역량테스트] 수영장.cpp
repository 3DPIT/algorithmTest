//#include<stdio.h>
//#include<iostream>
//#include<vector>
//#include<string.h>
//using namespace std;
//#define NS
//int ret = 0x7fffffff;
//struct Data {
//	int month, day;
//};
//struct Data1 {
//	int cost;
//};
//vector<Data1>v;
////vector<int>monthChk;
//int monthChk[15];//계획 세우기
//int monthPlan[15];
//int c;//이용달 확인위해서
//struct Honey {
//	Honey() {
//		int T;
//		scanf("%d", &T);
//		for (int t = 1; t <= T; t++) {
//			init();
//			for (int i = 0; i < 4; i++) {
//				int cost;
//				scanf("%d", &cost);
//				v.push_back({ cost });
//			}
//			for (int i = 1; i <= 12; i++) {
//				scanf("%d", &monthPlan[i]);
//				if (monthPlan[i] != 0)c++;
//			}
//			dfs(0, 0);
//			if (ret > v[3].cost)ret = v[3].cost;
//			printf("#%d %d\n", t, ret);
//		}
//	}
//	void init() {
//		ret = 0x7fffffff;
//		memset(monthChk, 0, sizeof(monthChk));
//		memset(monthPlan, 0, sizeof(monthPlan));
//		c = 0;
//		v.clear();
//	}
//	void dfs(int idx, int sum1) {
//		if (idx > 12) {
//			int sum = 0;
//			int cnt = 0;
//			for (int i = 1; i <= 12; i++) {
//				if (monthPlan[i] != 0) {
//					if (monthChk[i] == 1) {
//						cnt++;
//						sum += (v[0].cost*monthPlan[i]);
//					}
//					else if (monthChk[i] == 2) {
//						cnt++;
//						sum += v[1].cost;
//					}
//					else if (monthChk[i] == 3) {
//						sum += v[2].cost;
//						for (int j = 1; j <= 3; j++) {
//							if (monthPlan[i] == 0)break;
//							if (i <= 12)cnt++;
//							i++;
//						}
//						i--;
//					}
//				}
//			}
//			if (cnt == c && (ret > sum))ret = sum;
//			//cout << endl;
//			return;
//		}
//		for (int i = 1; i <= 3; i++) {
//			monthChk[idx] = i;
//			if (i == 3) {
//				dfs(idx + 3, sum1);
//			}
//			else {
//				dfs(idx + 1, sum1);
//			}
//			monthChk[idx] = 0;
//		}
//	}
//
//}Honey;
//int main() {
//	return 0;
//}

#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
#define NS 13
int monthCost[4];
int monthPlan[NS];
int ret;
struct Pool {
	Pool() {
		int T;
		scanf("%d", &T);
		for (int t = 1; t <= T; t++) {
			init();
			for (int i = 0; i < 4; i++) {//이용권 가격들
				scanf("%d", &monthCost[i]);
			}
			ret = monthCost[3];//1년이용권보다 작은경우가 있을수 있으니
			for (int j = 1; j < NS; j++) {//12개월 이용계획
				scanf("%d", &monthPlan[j]);
			}
			dfs(0,0);
			printf("#%d %d\n",t, ret);//결과
		}
	}
	void dfs(int idx, int sum) {
		if (sum > ret) return;//최소값보다 크면 리턴
		if (idx > 12) {// 다확인 했다면 이제 결과값 최소비교
			if (ret > sum) ret = sum;
			return;
		}
		if (monthPlan[idx] == 0) {
			dfs(idx + 1, sum);//그냥 넘겨주기;
		}
		else {
			dfs(idx + 1, sum + (monthCost[0] * monthPlan[idx]));//1일치 이용권 이용시
			dfs(idx + 1, sum + monthCost[1]);//한달 이용권 이용시
			dfs(idx + 3, sum + monthCost[2]);
		}
	}
	void init() {
		ret = 0x7fffffff;
		memset(monthCost, 0, sizeof(monthCost));
		memset(monthPlan, 0, sizeof(monthPlan));
	}

}Pool;
int main(void) {

	return 0;
}