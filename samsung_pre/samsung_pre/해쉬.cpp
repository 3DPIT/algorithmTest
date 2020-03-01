// 로또
// 1~9 10~19 20~29 30~39 40~45
// 조합중 단위대 뽑고싶은 갯수 o
// 이웃수를 1개또는 2개 포함 하는 조합 o
// 전에 당첨됬던 조합을 하나만 포함하는 조합 o
// 거르고 싶은 숫자입력 o
// 꼭 포함시키고 싶은 숫자입력 o 
// 분석자료 5주차 3~4개(1개이상은 무조건나옴.) 6~10주차까지 1개(0개~3개 - 확률적음) 
// 제외수 3가지 뽑는법 - 얼토당토없지만 사용자가 확률을 줄이고 싶으면 입력하기.
// 5의 배수중 내가 맘에안드는것 제외시키기
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
#define e_a 25
#define e_b 36
#define e_c 42
vector <int>pan;
vector <int>v; // 6개숫자
vector <int>pick; // 꼭 포함시키고 싶은 숫자 입력 
int before[7]; //이전 당첨 번호 담는 배열
int number[46]; // 1~45 중 뽑힌 숫자체크, 함수들을 편하게 검사하도록 하기 위한 chk함수
int n_number[46]; //안뽑을 숫자
int daesoo[46]; //대수패턴내의 조합은 거른다.
int dan[6]; //5개의 단위중, 단위당 나왔으면 하는 숫자개수.
int suspect[46]; // 1주차 ~5주차 당첨번호 에서 제외수를 제외시킨 유력 당첨후보
int suspect2[46]; // 6주차~10주차 당첨번호에서 제외수를 제외시켜 두번째로 유력한 당첨후보
//int michul[46]; //미출
long long int result = 0;
int grade[7] = { 0,0,0,0,0,0,0 };
int g_arr[7]; //등수 각각 몇개 했는지
int g_total;

//9단패턴
bool P_1(int n)
{
	if (n == 0)return 1;
	//모두 홀수 모두 짝수는 걸러라
	int hol = 0;
	int zak = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] % 2 == 0)zak++;
		else hol++;
	}
	if (zak == 6 || hol == 6)return 0;
	return 1;
}
bool P_2(int n)
{
	if (n == 0)return 1;
	//첫번호가 16이상인것은 걸러라.
	//끝번호가 30이하인것은 걸러라.
	if (v[0] >= 16)return 0;
	if (v[5] <= 30)return 0;
	return 1;
}
bool P_3(int n)
{
	if (n == 0)return 1;
	//모서리 패턴, 모서리패턴에서 꼭 1개에서 4개사이의 번호를 선택해야한다.
	int mo[19] = { 1, 2, 8, 9, 6, 7, 13, 14, 29, 30, 34, 35, 36, 37, 41, 42, 43, 44, 45 };
	int ans = 0;
	for (int i = 0; i < 19; i++)
	{
		if (number[mo[i]] == 1)ans++;
	}
	if (1 <= ans && ans <= 4)return 1;
	return 0;
}
bool P_4(int n)
{
	if (n == 0)return 1;
	//좌우 2줄 패턴에만 조합금지 
	// 가운데 3줄패턴에서만 조합금지
	int mo[26] = { 1, 2, 6,7,8,9,13,14,15,16,20,21,22,23,27,28,29,30,34,35,36,37,41,42,43,44 };
	int mo2[18] = { 3, 4, 5, 10 ,11, 12,17, 18, 19, 24, 25, 26, 31, 32, 33, 38, 39, 40 };

	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (v[i] == mo[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans == 6)return 0;
	ans = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (v[i] == mo2[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans == 6)return 0;

	return 1;
}
bool P_5(int n)
{
	if (n == 0)return 1;
	//합성수 5개이상포함조합 피하기
	int mo[17] = { 1, 4, 8, 10, 14, 16, 20, 22, 25, 26, 28, 32, 34, 35, 38, 40, 44 };

	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (v[i] == mo[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans >= 5)return 0;
	return 1;
}
bool P_6(int n)
{
	if (n == 0)return 1;
	int sum = 0;
	int sum2 = 0;
	//직전회차 합
	for (int i = 0; i < 6; i++)sum += v[i];

	for (int i = 0; i < 6; i++)sum2 += before[i];

	if (sum == sum2)return 0;
	return 1;
}
bool P_7(int n)
{
	if (n == 0)return 1;
	// 삼각패턴 
	// 좌상삼각패턴은 몇몇 실패하기때문에
	// 좌하삼각, 우상삼각, 우하삼각 검사.
	int mo[27] = { 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 17, 18, 19, 20, 21, 25, 26, 27, 28, 33, 34, 35, 41, 42 };//우상
	int mo2[24] = { 1, 8, 9, 15, 16, 17, 22, 23, 24, 25, 29, 30, 31, 32, 33, 36, 37, 38, 39, 40, 41, 43, 44, 45 }; // 좌하
	int mo3[23] = { 7, 13, 14, 19, 20, 21, 25, 26, 27, 28, 31, 32, 33, 34, 35, 37, 38, 39, 40, 41, 42, 43, 44 }; // 우하
	int ans = 0;
	//우상
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			if (v[i] == mo[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans == 6)return 0;
	ans = 0;
	//좌하
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (v[i] == mo2[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans == 6)return 0;
	ans = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (v[i] == mo3[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans == 6)return 0;
	return 1;
}
bool P_8(int n)
{
	if (n == 0)return 1;
	//소수로 6개 고르지말자.
	int mo[14] = { 2,3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43 };
	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (v[i] == mo[j])
			{
				ans++;
				break;
			}
		}
	}
	if (ans == 6)return 0;
	return 1;
}
bool P_9(int n) //사용자정의
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 6; i++)ans += v[i];

	if (ans > 200)return 0;
	return 1;
}
void print() //뽑힌 숫자 출력 함수
{
	for (int i = 0; i < 6; i++)printf("%d ", v[i]);

	printf("\n");
}
bool Pick(int n) //포함시키고 싶은 번호가 있는 지 확인한다.
{
	if (n == 0)return 1;

	if (pick.size() == 0)return 1;
	//pick번호의 v[]는 1로 체크되어 있어야함.
	for (int i = 0; i < pick.size(); i++)if (number[pick[i]] == 0)return 0;

	return 1;
}
bool Dan(int n)//5개의 단위중, 단위당 나왔으면 하는 숫자개수를 충족하는지.
{
	if (n == 0)return 1;
	int arr[6]; //단위당 몇개 숫자 나왔는지
	memset(arr, 0, sizeof(arr));

	for (int i = 0; i < 6; i++)
	{
		if (1 <= v[i] && v[i] <= 9)arr[0]++; //단번단위
		else if (10 <= v[i] && v[i] <= 19)arr[1]++;
		else if (20 <= v[i] && v[i] <= 29)arr[2]++;
		else if (30 <= v[i] && v[i] <= 39)arr[3]++;
		else if (40 <= v[i] && v[i] <= 45)arr[4]++;
	}
	//
	int fal = 0; //함몰 구간 2개이상이면 탈락
	for (int i = 0; i < 5; i++)
	{
		if (arr[i] == 0)fal++;
	}
	if (fal >= 3)return 0;
	//단번대 시작 필터

	//if (arr[0] && arr[1] && arr[2] && arr[3] && arr[4])return 0; //다 뽑혔으면 
	if (arr[0] == 0 || arr[1] == 0)return 0;

	//if (arr[2] >= 2)
	//{
	//   int hol = 0;
	//   int zak = 0;

	//   for (int i = 0; i < 6; i++)
	//   {
	//      if (20 <= v[i] && v[i] <= 29)
	//      {
	//         if (v[i] % 2 == 0)zak++;
	//         else hol++;

	//      }
	//   }
	//   if (arr[2] == hol)return 0; //모두 홀이면
	//}
	for (int i = 0; i < 5; i++)
	{
		if (2 <= i && i <= 4)
		{
			if (arr[i] >= 4)return 0; //2,3, 4번단위는 4개이상출현을 방지한다.
		}
		else
		{
			if (arr[i] >= 3)return 0; // 0,1,단위에서는 3개이상출현을 방지한다.
		}
		//if (arr[4] == 2)return 0; // 40번대는 2개 나오지 않게한다. 확률떨어지므로 
		if (dan[i] == 7)continue; // 7은 여러개 나와도 되는 랜덤
		if (dan[i] != arr[i])return 0; //사용자 원하는 자릿대갯수 안나오면 done
	}
	return 1;

	//for (int i = 0; i < 5; i++)
	//{
	//   if (dan[i] != 7 && arr[i] >= 4)return 0; // 한구간에서 4수 이상출현 x
	//   if (dan[i] == 7)continue; // 7은 여러개 나와도 되는 랜덤
	//   if (dan[i] != arr[i])return 0; //사용자 원하는 자릿대갯수 안나오면 done
	//}
	//return 1;
	//2 1 7 1 0
}
bool Before(int n, int s, int e) //전에 나왔던 숫자중 1개를 포함시킨다.
{
	if (n == 0)return 1;
	//1개 이상은 안됨.
	int ans = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (v[i] == before[j])
			{
				ans++;
				break;
			}
		}
	}
	if (s <= ans && ans <= e)return 1;
	return 0;
}
bool Side(int n, int s, int e)// 전 회차 당점수중  이웃수를 하나라도 포함 하는 조합 1~2개만 적용.이게 확률이 높았던듯 
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 7; i++)
	{
		int left = before[i] - 1;
		int right = before[i] + 1;
		if (left == 0)left = 45;
		if (right == 46)right = 1;

		if (number[left] == 1 && number[right] == 1)return 0;//한숫자 양사이드 둘다 뽑혔으면 확률 적어지니까 return 0;

		if (number[left] == 1)ans++;
		if (number[right] == 1)ans++;

	}
	if (s <= ans && ans <= e)return 1;

	return 0;
}
bool Term_2(int n, int s, int e) // 11 12 연달아 나오는 번호가 나오는 건 10%내 - 사용자 지정, 하는게 우세. 경우의수 -100정도 걸러줌 //하지만 요즘추세가 나올수도있으니 1개정도는 두자.
{
	//연속수 안나왔으면 좋겠으면 0 0, 0또는 1이면0 1 ,1개는 나왔으면 좋겠으면 1 
	if (n == 0)return 1;
	int ans = 0;
	int ans_4 = 0;

	for (int i = 0; i < 5; i++)
	{
		if (v[i + 1] - v[i] == 1)
		{
			if (40 <= v[i + 1] && 40 <= v[i])ans_4++;
			else ans++;
		}
	}
	//40번대에서 연번대가 나왔다.
	if (s <= ans && ans <= e)return 1;
	if (1 <= ans_4)return 1; // 40번대 연번대는 가능
	return 0;
}
bool Term_3(int n) // 1 2 3 또는 21 22 23 와 같은 세개 연속의 확률이 낮은 수는 제외한다.
{
	if (n == 0)return 1;
	for (int i = 0; i < 4; i++)
	{
		if (v[i + 1] - v[i] == 1 && v[i + 2] - v[i + 1] == 1)
		{
			if (40 <= v[i] && 40 <= v[i + 1] && 40 <= v[i + 2])return 1;
			else return 0;
		}
	}
	return 1;
}
void Init_ds()
{
	//대수패턴에 값넣기 
	daesoo[2] = 1; daesoo[6] = 1; daesoo[9] = 1; daesoo[11] = 1;
	daesoo[13] = 1; daesoo[17] = 1; daesoo[19] = 1; daesoo[20] = 1;
	daesoo[22] = 1; daesoo[24] = 1; daesoo[25] = 1; daesoo[27] = 1;
	daesoo[28] = 1; daesoo[29] = 1; daesoo[31] = 1; daesoo[33] = 1;
	daesoo[34] = 1; daesoo[36] = 1; daesoo[39] = 1; daesoo[41] = 1;
	daesoo[42] = 1; daesoo[43] = 1; daesoo[44] = 1;
}
bool Daesoo(int n)// 대수패턴안에서 이루어진 조합이면 out. - 로또 9단
{
	if (n == 0)return 1;
	Init_ds();
	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		if (daesoo[v[i]] == 1)ans++;
	}
	if (ans == 6)return 0;
	return 1;
}
bool Suspect(int n, int s, int e) // s<= <=e 뽑을 개수 구간 확률이 높으므로 3~4개 뽑는거 권장, 5개까지 나올수있음 단, 여기서 6숫자는 금지
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		if (suspect[v[i]] == 1)ans++;
	}
	if (s <= ans && ans <= e)return 1;
	return 0;
}
bool Suspect2(int n, int s, int e) // 확률이 0<= <=3으로 낮기때문에 0<= <=1개 뽑는거 권장
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		if (suspect2[v[i]] == 1)ans++;
	}
	if (s <= ans && ans <= e)return 1;
	return 0;
}
bool Michul(int n, int s, int e)
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		if (suspect[v[i]] == 0 && suspect2[v[i]] == 0)ans++;
	}
	if (s <= ans && ans <= e)return 1;
	return 0;
}
/*
void safe()
{
   v.push_back(2);
   v.push_back(6);
   v.push_back(13);
   v.push_back(16);
   v.push_back(21);
   v.push_back(37);

   number[2] = 1;
   number[6] = 1;
   number[13] = 1;
   number[16] = 1;
   number[21] = 1;
   number[37] = 1;

   if (Term_3(0) && Dan(0) && Daesoo(0) && Before(0) && Side(0, 0, 1) && Suspect(1, 3, 5))//여러 검사들을 거친 번호만이 출력된다.//함수인자로는 0, 1을 적을수 있으며 0은 해당기능은 적용x라는 뜻이다.
   {
	  if (Pick(0) && Term_2(0, 0, 0) && Suspect2(0, 1, 1)) //사용자 맞춤검사
	  {
		 print();
	  }
   }
}*/
bool Effect(int n, int s, int e)  // 1<= <=2
{
	if (n == 0)return 1;
	//게일하워드 c추출용.
	// 뽑은 번호 중에 s<= <=e개 있어야함
	int ans = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] == e_a || v[i] == e_b || v[i] == e_c)ans++;
	}
	if (s <= ans && ans <= e)return 1;
	return 0;

}
void Grade()
{
	int ans = 0;
	int bonus = 0;
	for (int i = 0; i < 6; i++)
	{
		if (number[grade[i]] == 1)ans++;
	}
	if (number[grade[6]] == 1)bonus = 1;

	if (0 <= ans && ans <= 2)
	{
		//printf("꽝 ");
		g_arr[6]++;
	}
	else if (ans == 3)
	{
		printf("5등 ");
		g_arr[5]++;
		g_total++;
	}
	else if (ans == 4)
	{
		printf("4등 ");
		g_arr[4]++;
		g_total++;
	}
	else if (ans == 5)
	{
		if (bonus == 1)
		{
			g_arr[2]++;
			printf("**2등 ");
			g_total++;
		}
		else
		{
			g_arr[3]++;
			printf("*3등 ");
			g_total++;
		}
	}
	else
	{
		g_arr[1]++;
		printf("***1등 ");
		g_total++;
	}
}
bool Wanted(int n)
{
	if (n == 0)return 1;
	//if (v[0] / 10 == 0)//둘다 단번대
	//{
	//   if (v[1] - v[0] == 2)return 0; // 2차이이면 
	//}
	//return 1;
	//10번대 연속수는 거른다.
	for (int i = 0; i < 5; i++)
	{
		if (10 <= v[i] && v[i] <= 19 && 10 <= v[i + 1] && v[i + 1] <= 19)//둘다 십번대
		{
			if (v[i + 1] - v[i] == 1)return 0;
		}
	}
	return 1;
}
void Check()
{
	//만약에 조합중에 이번호가 있으면 확인 이라고 한다.
	int arr[6] = { 3, 9, 10, 21, 22, 29 };
	int arr2[6] = { 1, 8, 23, 26, 29, 32 };
	int arr3[6] = { 1,18, 24, 36, 39, 43 };
	int arr4[6] = { 3, 6, 25, 36, 37, 41 };

	int fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("1번 ");
	fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr2[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("2번 ");
	fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr3[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("3번 ");
	fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr4[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("4번 ");

} //번호가 당첨되었는지 확인
void start2(int idx) // v에 뽑을 수만담겨있음 
{
	if (v.size() == 6)
	{
		if (P_1(1) && P_2(1) && P_3(1) && P_4(1) && P_5(1) && P_6(1) && P_7(1) && P_8(1) && P_9(0)) //패턴검사
		{

			if (Pick(1) && Effect(1, 1, 2) && Dan(1) && Term_3(1) && Term_2(1, 0, 1) && Daesoo(0) && Before(1, 0, 1) && Side(1, 1, 4)) //0은 해당기능은 적용x라는 뜻이다. 
			{
				if (Suspect(1, 3, 4) && Suspect2(1, 0, 1) && Michul(1, 0, 1)) //사용자 맞춤검사
				{
					//suspect2는 조정 0 1 이였는데 조정하기. Term2도 연속수 조절 
					if (Wanted(1))
					{

						print();
						result++;
						Grade();

						if (result % 10 == 0)printf("\n");
					}
				}
			}
		}
		return;
	}
	if (idx + 1 < pan.size())
	{
		int n = pan[idx];
		number[n] = 1;
		v.push_back(n);
		start2(idx + 1);
		v.pop_back();
		number[n] = 0;

		start2(idx + 1); //안뽑거나

	}
}
void start3(int idx)
{
	if (v.size() == 6)
	{
		if (P_1(1) && P_2(1) && P_3(1) && P_4(1) && P_5(1) && P_6(1) && P_7(1) && P_8(1) && P_9(0)) //패턴검사
		{
			if (Pick(1) && Effect(1, 0, 1) && Dan(1) && Term_3(1) && Term_2(1, 0, 1) && Daesoo(1) && Before(1, 0, 1) && Side(1, 1, 4)) //0은 해당기능은 적용x라는 뜻이다. 
			{
				if (Suspect(1, 2, 3) && Suspect2(1, 0, 1) && Michul(1, 2, 3)) //사용자 맞춤검사
				{
					//suspect2는 조정 0 1 이였는데 조정하기. Term2도 연속수 조절 
					if (Wanted(0))
					{
						print();
						result++;
						Grade();

						if (result % 10 == 0)printf("\n");
					}
				}
			}
		}
		return;
	}
	if (idx + 1 < pan.size())
	{
		int n = pan[idx];
		number[n] = 1;
		v.push_back(n);
		start3(idx + 1);
		v.pop_back();
		number[n] = 0;

		start3(idx + 1); //안뽑거나
	}
}
void start(int K)//6개의 숫자를 뽑는다.
{
	if (v.size() == 6) //6개의 숫자를 뽑았다.
	{
		//검사에 들어간다

		if (P_1(1) && P_2(1) && P_3(1) && P_4(1) && P_5(1) && P_6(1) && P_7(1) && P_8(1) && P_9(0))
		{
			if (Pick(1) && Effect(1, 0, 1) && Dan(1) && Term_3(1) && Term_2(1, 0, 1) && Daesoo(1) && Before(1, 0, 1) && Side(1, 1, 2))//여러 검사들을 거친 번호만이 출력된다.//함수인자로는 0, 1을 적을수 있으며 0은 해당기능은 적용x라는 뜻이다. 
			{
				//side 이웃수는 그냥 한개라도 있으면 통과하게 했음.
				if (Suspect(1, 3, 5) && Suspect2(1, 0, 2) && Michul(1, 0, 2)) //사용자 맞춤검사
				{

					//suspect2는 조정 0 1 이였는데 조정하기. Term2도 연속수 조절 
					if (Wanted(1))
					{
						print();
						//printf("통 \n");
						//총합이 175초과하는건 거르자
						/*
						*Term_3 : 12 13 14 같은 연속3구간 제외
						*Daesoo : 대수로 이루어진 조합으로 하면 당첨xㄴ
						*@Side : 직전회차의 이웃수가 s<= <=e개 (1<= <= 2개(지향) 또는 1<= <=1 또는 0<= <=1)
						*+Suspect : 이전 1~5주차 로또 번호중 s<= <=e개 포함 (3<= <=5지향)
						+Suspect2 : 이전 6~10주차 로또 번호중 s<= <=e개 포함 (0<= <=1지향 또는 1<= <=2)
						@Dan : _ _ _ _ _ 각 구간 출몰갯수
						@Before : 직전 회차에 나온 숫자 1개 포함
						@Pick : 정말 나올거 같은 번호를 뽑는다
						@Term_2 : 22 23 연번이 나올것이냐 (원래는 거의 나올확률 적었는데 요즘추세는 좀 나오고는 있음 확률을 높이려면 그냥 안나오는걸루 당첨되길 기도할수밖에)
						@Effect : 번호 중 하나 또는 그이상 나오게 하는것. (게일하워드C나 정말 삘좋은 번호있으면 넣기)
						*/
						result++;
						//Check();

						Grade();
						//
						if (result % 10 == 0)printf("\n");
					}
				}
			}
		}
		return;
	}
	//현재숫자를 뽑는다 안뽑는다.

	for (int i = K; i <= 45; i++)
	{
		if (n_number[i] == 0) //뽑힌숫자가 아니고 기피숫자가 아니면
		{
			number[i] = 1;
			v.push_back(i);
			start(i + 1);
			v.pop_back();
			number[i] = 0;
		}

	}
}

// 제외수는 로또 9단한테 받아서 거기서 제외할수 제외. 남은 조합만으로 원칙대로 잘 뽑아보기.

//로또 9단의 분석번호 1~5 에서 4개 6~10에서 1개 숫자 출현.(제외수 제외한 결과) 
void Init_sus()
{
	printf("이번 회차를 예측하기 위해 지난 1~5주차의 번호를 5행 * 6열형식으로 번호를 적어주세요.\n");
	int a;
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect[a] = 1;
	}
	//
	printf("이번 회차를 예측하기 위해 지난 6~10주차의 번호를 5행 * 6열형식으로 번호를 적어주세요.\n");
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect2[a] = 1;
	}
	//
	printf("제외유력수나  제외하고 싶은 숫자의 번호를 입력하시오. 입력의 끝은 0입니다.\n");
	while (scanf("%d", &a) && a)n_number[a] = 1;
	//

	printf("제외수중에 1~5주차 유력후보가 있을 수 있습니다.\n유력후보 : ");
	for (int i = 1; i <= 45; i++)
	{
		if (suspect2[i] == 1 && suspect[i] == 1)suspect2[i] = 0; //중복제거
		if (n_number[i] == 1 && suspect[i] == 1)
		{
			printf("%d ", i);
			n_number[i] = 0; //제외수인데 유력한 후보다.
		}
	}
	printf("\n");
	printf("강력제외수를 재입력하고 화면에 출력된 수중 정말 빼고 싶은 숫자가 있다면 다시 입력해주세요.마지막 입력은 0입니다.\n");
	while (scanf("%d", &a) && a)n_number[a] = 1;
}

void One()
{
	printf("지난 회차 당첨 숫자 7개를 입력하시오 : \n");
	scanf("%d %d %d %d %d %d %d", &before[0], &before[1], &before[2], &before[3], &before[4], &before[5], &before[6]);
	//
	printf("꼭 넣고 싶은 숫자의 번호를 입력하시오. 입력의 끝은 0입니다.\n");
	int k;
	while (scanf("%d", &k) && k)pick.push_back(k);
	//
	printf("1~9, 10~19, 20~29, 30~39, 40~45 총 5개의 구간중, 구간당 나왔으면 하는 개수를 적으시오.\n");
	printf("예시 : 2 1 7 1 0은\n단번단위 : 2개\n10번단위 : 1개\n20번단위 : 상관없음\n30번단위 1개\n40번단위 0개 나오기를 원하는 것입니다.\n");
	printf("이 과정을 원치 않는 다면 7 7 7 7 7 을 입력해주세요.\n");
	printf("이제 다섯개의 숫자를 입력해주세요.\n");
	scanf("%d %d %d %d %d", &dan[0], &dan[1], &dan[2], &dan[3], &dan[4]);

	Init_sus(); //유력수 뽑기 

	//절대 빼고싶지 않은 번호는 여기에 적기
	//n_number[17] = 0; 
	//n_number[18] = 0;
	//n_number[23] = 0; 
	//n_number[28] = 0;
	//n_number[38] = 0;
	//n_number[e_a] = 0; 
	//n_number[e_b] = 0;
	//n_number[e_c] = 0;

	//n수중 추출
	printf("이 수중 조합을 추출합니다\n");
	for (int i = 1; i <= 45; i++)if (n_number[i] == 0)printf("%d ", i);

	printf("\n");
	//

	printf("번호 추출 결과입니다.\n");
}
void Result()
{
	printf("경우의수 : %lld\n", result);
	printf("조합중 %d개 당첨됬습니다\n", g_total);
	for (int i = 1; i <= 6; i++)
	{
		printf("%d등 : %d\n", i, g_arr[i]);
	}
}
int bun2[46];
void Two()
{
	printf("지난 회차 당첨 숫자 7개를 입력하시오 : \n");
	scanf("%d %d %d %d %d %d %d", &before[0], &before[1], &before[2], &before[3], &before[4], &before[5], &before[6]);
	//
	printf("꼭 넣고 싶은 숫자의 번호를 입력하시오. 입력의 끝은 0입니다.\n");
	int k;
	while (scanf("%d", &k) && k)pick.push_back(k);
	//
	printf("1~9, 10~19, 20~29, 30~39, 40~45 총 5개의 구간중, 구간당 나왔으면 하는 개수를 적으시오.\n");
	printf("예시 : 2 1 7 1 0은\n단번단위 : 2개\n10번단위 : 1개\n20번단위 : 상관없음\n30번단위 1개\n40번단위 0개 나오기를 원하는 것입니다.\n");
	printf("이 과정을 원치 않는 다면 7 7 7 7 7 을 입력해주세요.\n");
	printf("이제 다섯개의 숫자를 입력해주세요.\n");
	scanf("%d %d %d %d %d", &dan[0], &dan[1], &dan[2], &dan[3], &dan[4]);

	printf("이번 회차를 예측하기 위해 지난 1~5주차의 번호를 5행 * 6열형식으로 번호를 적어주세요.\n");
	int a;
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect[a] = 1;
	}
	//
	printf("이번 회차를 예측하기 위해 지난 6~10주차의 번호를 5행 * 6열형식으로 번호를 적어주세요.\n");
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect2[a] = 1;
	}
	//

	printf("포함할 번호를 입력하시오. 입력의 끝은 0입니다.\n");
	while (scanf("%d", &a) && a)number[a] = 1;
	//

	printf("제외수중에 1~5주차 유력후보가 있을 수 있습니다.\n유력후보 : ");
	for (int i = 1; i <= 45; i++)
	{
		if (suspect2[i] == 1 && suspect[i] == 1)suspect2[i] = 0; //중복제거
		if (n_number[i] == 1 && suspect[i] == 1)
		{
			printf("%d ", i);
			n_number[i] = 0; //제외수인데 유력한 후보다.
		}
	}
	printf("\n");

}
int main(void)
{
	int order;
	printf("로또분석 0번, 번호추출 1번, 번호추출2 2번\n");
	scanf("%d", &order);
	if (order == 0)
	{
		//로또번호분석

		printf("회차의 당첨번호 7숫자를 입력해주세요\n");
		int bun[7] = { 0,0,0,0,0,0,0 }; //분석
		scanf("%d %d %d %d %d %d %d", &bun[0], &bun[1], &bun[2], &bun[3], &bun[4], &bun[5], &bun[6]);

		for (int i = 0; i <= 6; i++)bun2[bun[i]] = 1;


		Init_sus();

		printf("\n* 1~5주차 사이 유력수를 출력합니다.\n");

		int cnt1 = 0;
		for (int i = 1; i <= 45; i++)if (suspect[i] == 1 && n_number[i] == 0)
		{
			cnt1++;
			printf("%d ", i);
		}
		printf("\n총 %d개 \n", cnt1);
		cnt1 = 0;

		printf("\n* 6~10주차 사이 유력수를 출력합니다.\n");

		for (int i = 1; i <= 45; i++)if (suspect2[i] == 1 && n_number[i] == 0)
		{
			cnt1++;
			printf("%d ", i);
		}
		printf("\n총 %d개 \n", cnt1);
		cnt1 = 0;
		//미출수
		printf("\n* 미출구간 수를 출력합니다.\n");
		for (int i = 1; i <= 45; i++)
		{
			if (!(suspect2[i] == 1) && !(suspect[i] == 1))
			{
				if (n_number[i] == 0)
				{
					cnt1++;
					printf("%d ", i);
				}
			}
		}
		printf("\n총 %d개 \n\n", cnt1);
		cnt1 = 0;

		//이번 당첨수 출력
		printf("* 지난회차 당첨번호 입니다 : ");
		for (int i = 0; i < 7; i++)
		{
			if (i == 6)printf(" +");
			printf("%d, ", bun[i]);
		}

		printf("\n\n");
		//이웃수 출력
		printf("* 다음나오는 숫자는 이웃수입니다\n이웃수 : ");

		for (int i = 0; i < 7; i++)
		{
			int left = bun[i] - 1;
			int right = bun[i] + 1;
			if (left == 0)left = 45;
			if (right == 46)right = 1;

			printf("%d, %d, ", left, right);
		}
		printf("\n");

		printf("\n당첨번호\n");

		for (int i = 0; i <= 6; i++)printf("%d ", bun[i]);


		printf("\n구간 분석결과입니다\n");
		int bonus = 0;
		vector <int>v1;
		vector <int>v2;
		vector <int>v3;
		for (int i = 1; i <= 45; i++)
		{
			if (bun2[i] == 1)
			{
				if (suspect[i] == 1)
				{
					v1.push_back(i); // 1구간에 당첨번호 포함
					if (bun[6] == i)bonus = 1;
				}
				else if (suspect2[i] == 1)
				{
					v2.push_back(i); //2구간
					if (bun[6] == i)bonus = 2;
				}
				else
				{
					v3.push_back(i); //미출
					if (bun[6] == i)bonus = 3;
				}
			}
		}
		printf("1~5주차 구간 :%d개,  ", v1.size());
		for (int i = 0; i < v1.size(); i++)printf("%d ", v1[i]);

		printf("\n6~10주차 구간 :%d개,  ", v2.size());
		for (int i = 0; i < v2.size(); i++)printf("%d ", v2[i]);

		printf("\n미출 구간 :%d개,  ", v3.size());
		for (int i = 0; i < v3.size(); i++)printf("%d ", v3[i]);

		printf("\nbonus = %d구간\n", bonus);

	}
	else if (order == 1)
	{
		One(); //자동번호
		//직접뽑은 번호안에서 직접 추출

		start(1); //추출용

		Result();
	}
	else if (order == 2)//새프로그램만들기
	{
		One(); // 유력수 뽑고

		for (int i = 1; i <= 45; i++)if (n_number[i] == 0)pan.push_back(i); //pan에 숫자담기

		sort(pan.begin(), pan.end());//정렬

		start2(0);
		Result();
		// 넣을수나 뺄수를 입력하기
		// 그중에서 뽑고, 필터거르기
	}
	else
	{
		Two(); // 유력수 뽑고

		for (int i = 1; i <= 45; i++)if (number[i] == 1)pan.push_back(i); //pan에 숫자담기

		sort(pan.begin(), pan.end());//정렬

		printf("번호를 추출합니다.\n");
		for (int i = 1; i <= 45; i++)number[i] = 0;


		start3(0);
		Result();

	}
}