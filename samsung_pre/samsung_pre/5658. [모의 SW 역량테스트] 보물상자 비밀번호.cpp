#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<string>
#include<math.h>
#include<algorithm>
using namespace std;
vector<string>v;
int ret;
int N, K;
char sNumber[100];
int dlwls[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
//map<string, int>m;

	void init() {
		ret = 0;
		memset(sNumber, 0, sizeof(sNumber));
		v.clear();
	}
	void simul() {
		int cFinal = N / 4;
		int c = 0;
		int idx = 0;
		int idx1 = 0;
		string s;
		string sS[4][2];
		int ii = 0;
		for (int i = 0; i < N; i++) {// 초기 번호 추출
			s.push_back(sNumber[i]);
			c++;
			if (c == cFinal) {
				c = 0;
				int flag = 0;
				for (int j = 0; j < v.size(); j++) {
					if (v[j]== s) {
						flag = 1;
					}
				}
				if (flag==0) {
					v.push_back(s);
				}
				sS[idx1++][0] = s;
				s.clear();
			}
		}
		int cCnt = 0;
		int sidx = N-1;
		idx = N-2;
		while (1) {
			idx = (++idx) % N;
			s.push_back(sNumber[idx]);
			c++;
			if (c == cFinal) {
				sS[cCnt++][1] = s;
				c = 0;
				
				int flag = 0;
				for (int j = 0; j < v.size(); j++) {
					if (v[j] == s) {
						flag = 1;
					}
				}
				if (flag == 0) {
					v.push_back(s);
				}
				s.clear();
			}
			if (cCnt == 4) {
				int cc = 0;
				int visit[4] = { 0, };
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (sS[i][0] == sS[j][1]&&visit[i]==0) {
						visit[i] = 1;
							cc++;
						}
					}
				}
				for (int i = 0; i < 4; i++)
					sS[i][1].clear();
				if (cc == 4) break;
				cCnt = 0;
				sidx = (++sidx) % N;
				 idx = sidx;

			}
		}
	}


int main(void) {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		scanf("%d %d", &N, &K);
		scanf("%s", sNumber);
		simul();
		int c = 0;
		sort(v.begin(), v.end());
		int r = 0;
		for (int i = v.size() - 1; i >= 0; i--) {
			c++;
			if (c == K) {
				char s[1000];

				string s1 = v[i];
				;					/*for (int i = 0; i < s1.size(); i++) {
										s[i] = s1[i];
									}
				*/
				vector<int>vv;
				for (int i = s1.size() - 1; i >= 0; i--) {
					int nu = 0;
					if ('A' <= s1[i] && s1[i] <= 'F') {
						nu = (s1[i] - 'A') + 10;
					}
					else {
						nu = s1[i] - '0';
					}
					int c = 0;
					while (nu != 0) {
						c++;
						vv.push_back(nu % 2);
						nu /= 2;
					}
					while (c != 4) {
						vv.push_back(0);
						c++;
					}
				}
				for (int i = 0; i < vv.size(); i++) {
					r += vv[i] * pow(2, i);
				}
			}
		}
		printf("#%d %d\n", t, r);
	}
	return 0;
}
//
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
////int a = 536870911;
//// 최대값 : 536870911 2^28승까지
//int T, N, K;
//int ret = 0;
//char num[1][40];
//int dlwls[40];
//int result[40];
//int re_idx = 0;
//bool cmp(int a, int b)
//{
//	return a > b;
//}
//int two[30] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,
//				262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456 };
//void rot()
//{
//	char a = num[0][N - 1];
//	for (int i = N - 2; i >= 0; i--)
//	{
//		num[0][i + 1] = num[0][i];
//	}
//	num[0][0] = a;
//}
//int main(void)
//{
//	// 16진법을 10진법으로 변환을 시킨다.
//	// 배열에 저장한다(저장하면서 중복 확인 하고 절대 같은 값은 넣지 않는다.
//
//// 회전을 다하고 마지막에 sort 를 한다.
//// 그냥 k-1 인덱스 위치의 배열을 출력한다. 끝
//	scanf("%d", &T);
//	for (int t = 1; t <= T; ++t)
//	{
//
//		for (int i = 0; i < 40; i++)
//		{
//			num[0][i] = 0;
//			dlwls[i] = result[i] = 0;
//		}
//		scanf("%d %d", &N, &K);
//		scanf("%s", num[0]);
//		ret = 0;
//		for (int i = 0; i < N; i++)
//		{
//			if ('A' <= num[0][i] && num[0][i] <= 'F')
//			{
//				num[0][i] = num[0][i] - '7';
//			}
//			else
//			{
//				num[0][i] = num[0][i] - '0';
//
//			}
//		}
//		int n = N / 4;
//		int cnt = 0;
//		int idx = 0;
//		for (int k = 0; k < n + 1; k++) {
//
//			for (int i = N - 1; i >= 0; i--)
//			{
//				++cnt;
//				/*  if (k == 0)n = n + 1;
//					else n = N / 4;*/
//				if (cnt == n + 1) {
//					for (int li = 0; li < idx; li++)
//					{
//						if (dlwls[li] == 1)
//						{
//							ret += two[li];
//						}
//						dlwls[li] = 0;
//					}
//
//					if (re_idx != 0) {
//						int ii = 0;
//						for (ii = 0; ii < re_idx; ii++)
//						{
//							if (result[ii] == ret)break;
//
//						}
//						if (ii == re_idx)
//						{
//							result[re_idx++] = ret;
//						}
//					}
//					else
//					{
//						result[re_idx++] = ret;
//					}
//					cnt = 1;
//					idx = 0;
//					ret = 0;
//				}
//				// 1 49
//				//A 65 -'7'
//				int a = num[0][i];
//				for (int j = 0; j < 4; j++)
//				{
//					dlwls[idx++] = a % 2;
//					a /= 2;
//				}
//			}
//
//			rot();
//
//		}
//
//		sort(result, result + re_idx, cmp);
//		printf("#%d %d\n", t, result[K - 1]);
//		idx = 0;
//		re_idx = 0;
//	}
//	return 0;
//}
