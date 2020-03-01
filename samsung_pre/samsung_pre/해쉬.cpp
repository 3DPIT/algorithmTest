// �ζ�
// 1~9 10~19 20~29 30~39 40~45
// ������ ������ �̰���� ���� o
// �̿����� 1���Ǵ� 2�� ���� �ϴ� ���� o
// ���� ��÷��� ������ �ϳ��� �����ϴ� ���� o
// �Ÿ��� ���� �����Է� o
// �� ���Խ�Ű�� ���� �����Է� o 
// �м��ڷ� 5���� 3~4��(1���̻��� �����ǳ���.) 6~10�������� 1��(0��~3�� - Ȯ������) 
// ���ܼ� 3���� �̴¹� - ������������ ����ڰ� Ȯ���� ���̰� ������ �Է��ϱ�.
// 5�� ����� ���� �����ȵ�°� ���ܽ�Ű��
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
#define e_a 25
#define e_b 36
#define e_c 42
vector <int>pan;
vector <int>v; // 6������
vector <int>pick; // �� ���Խ�Ű�� ���� ���� �Է� 
int before[7]; //���� ��÷ ��ȣ ��� �迭
int number[46]; // 1~45 �� ���� ����üũ, �Լ����� ���ϰ� �˻��ϵ��� �ϱ� ���� chk�Լ�
int n_number[46]; //�Ȼ��� ����
int daesoo[46]; //������ϳ��� ������ �Ÿ���.
int dan[6]; //5���� ������, ������ �������� �ϴ� ���ڰ���.
int suspect[46]; // 1���� ~5���� ��÷��ȣ ���� ���ܼ��� ���ܽ�Ų ���� ��÷�ĺ�
int suspect2[46]; // 6����~10���� ��÷��ȣ���� ���ܼ��� ���ܽ��� �ι�°�� ������ ��÷�ĺ�
//int michul[46]; //����
long long int result = 0;
int grade[7] = { 0,0,0,0,0,0,0 };
int g_arr[7]; //��� ���� � �ߴ���
int g_total;

//9������
bool P_1(int n)
{
	if (n == 0)return 1;
	//��� Ȧ�� ��� ¦���� �ɷ���
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
	//ù��ȣ�� 16�̻��ΰ��� �ɷ���.
	//����ȣ�� 30�����ΰ��� �ɷ���.
	if (v[0] >= 16)return 0;
	if (v[5] <= 30)return 0;
	return 1;
}
bool P_3(int n)
{
	if (n == 0)return 1;
	//�𼭸� ����, �𼭸����Ͽ��� �� 1������ 4�������� ��ȣ�� �����ؾ��Ѵ�.
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
	//�¿� 2�� ���Ͽ��� ���ձ��� 
	// ��� 3�����Ͽ����� ���ձ���
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
	//�ռ��� 5���̻��������� ���ϱ�
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
	//����ȸ�� ��
	for (int i = 0; i < 6; i++)sum += v[i];

	for (int i = 0; i < 6; i++)sum2 += before[i];

	if (sum == sum2)return 0;
	return 1;
}
bool P_7(int n)
{
	if (n == 0)return 1;
	// �ﰢ���� 
	// �»�ﰢ������ ��� �����ϱ⶧����
	// ���ϻﰢ, ���ﰢ, ���ϻﰢ �˻�.
	int mo[27] = { 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 17, 18, 19, 20, 21, 25, 26, 27, 28, 33, 34, 35, 41, 42 };//���
	int mo2[24] = { 1, 8, 9, 15, 16, 17, 22, 23, 24, 25, 29, 30, 31, 32, 33, 36, 37, 38, 39, 40, 41, 43, 44, 45 }; // ����
	int mo3[23] = { 7, 13, 14, 19, 20, 21, 25, 26, 27, 28, 31, 32, 33, 34, 35, 37, 38, 39, 40, 41, 42, 43, 44 }; // ����
	int ans = 0;
	//���
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
	//����
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
	//�Ҽ��� 6�� ��������.
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
bool P_9(int n) //���������
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 6; i++)ans += v[i];

	if (ans > 200)return 0;
	return 1;
}
void print() //���� ���� ��� �Լ�
{
	for (int i = 0; i < 6; i++)printf("%d ", v[i]);

	printf("\n");
}
bool Pick(int n) //���Խ�Ű�� ���� ��ȣ�� �ִ� �� Ȯ���Ѵ�.
{
	if (n == 0)return 1;

	if (pick.size() == 0)return 1;
	//pick��ȣ�� v[]�� 1�� üũ�Ǿ� �־����.
	for (int i = 0; i < pick.size(); i++)if (number[pick[i]] == 0)return 0;

	return 1;
}
bool Dan(int n)//5���� ������, ������ �������� �ϴ� ���ڰ����� �����ϴ���.
{
	if (n == 0)return 1;
	int arr[6]; //������ � ���� ���Դ���
	memset(arr, 0, sizeof(arr));

	for (int i = 0; i < 6; i++)
	{
		if (1 <= v[i] && v[i] <= 9)arr[0]++; //�ܹ�����
		else if (10 <= v[i] && v[i] <= 19)arr[1]++;
		else if (20 <= v[i] && v[i] <= 29)arr[2]++;
		else if (30 <= v[i] && v[i] <= 39)arr[3]++;
		else if (40 <= v[i] && v[i] <= 45)arr[4]++;
	}
	//
	int fal = 0; //�Ը� ���� 2���̻��̸� Ż��
	for (int i = 0; i < 5; i++)
	{
		if (arr[i] == 0)fal++;
	}
	if (fal >= 3)return 0;
	//�ܹ��� ���� ����

	//if (arr[0] && arr[1] && arr[2] && arr[3] && arr[4])return 0; //�� �������� 
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
	//   if (arr[2] == hol)return 0; //��� Ȧ�̸�
	//}
	for (int i = 0; i < 5; i++)
	{
		if (2 <= i && i <= 4)
		{
			if (arr[i] >= 4)return 0; //2,3, 4�������� 4���̻������� �����Ѵ�.
		}
		else
		{
			if (arr[i] >= 3)return 0; // 0,1,���������� 3���̻������� �����Ѵ�.
		}
		//if (arr[4] == 2)return 0; // 40����� 2�� ������ �ʰ��Ѵ�. Ȯ���������Ƿ� 
		if (dan[i] == 7)continue; // 7�� ������ ���͵� �Ǵ� ����
		if (dan[i] != arr[i])return 0; //����� ���ϴ� �ڸ��밹�� �ȳ����� done
	}
	return 1;

	//for (int i = 0; i < 5; i++)
	//{
	//   if (dan[i] != 7 && arr[i] >= 4)return 0; // �ѱ������� 4�� �̻����� x
	//   if (dan[i] == 7)continue; // 7�� ������ ���͵� �Ǵ� ����
	//   if (dan[i] != arr[i])return 0; //����� ���ϴ� �ڸ��밹�� �ȳ����� done
	//}
	//return 1;
	//2 1 7 1 0
}
bool Before(int n, int s, int e) //���� ���Դ� ������ 1���� ���Խ�Ų��.
{
	if (n == 0)return 1;
	//1�� �̻��� �ȵ�.
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
bool Side(int n, int s, int e)// �� ȸ�� ��������  �̿����� �ϳ��� ���� �ϴ� ���� 1~2���� ����.�̰� Ȯ���� ���Ҵ��� 
{
	if (n == 0)return 1;
	int ans = 0;
	for (int i = 0; i < 7; i++)
	{
		int left = before[i] - 1;
		int right = before[i] + 1;
		if (left == 0)left = 45;
		if (right == 46)right = 1;

		if (number[left] == 1 && number[right] == 1)return 0;//�Ѽ��� ����̵� �Ѵ� �������� Ȯ�� �������ϱ� return 0;

		if (number[left] == 1)ans++;
		if (number[right] == 1)ans++;

	}
	if (s <= ans && ans <= e)return 1;

	return 0;
}
bool Term_2(int n, int s, int e) // 11 12 ���޾� ������ ��ȣ�� ������ �� 10%�� - ����� ����, �ϴ°� �켼. ����Ǽ� -100���� �ɷ��� //������ �����߼��� ���ü��������� 1�������� ����.
{
	//���Ӽ� �ȳ������� �������� 0 0, 0�Ǵ� 1�̸�0 1 ,1���� �������� �������� 1 
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
	//40���뿡�� �����밡 ���Դ�.
	if (s <= ans && ans <= e)return 1;
	if (1 <= ans_4)return 1; // 40���� ������� ����
	return 0;
}
bool Term_3(int n) // 1 2 3 �Ǵ� 21 22 23 �� ���� ���� ������ Ȯ���� ���� ���� �����Ѵ�.
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
	//������Ͽ� ���ֱ� 
	daesoo[2] = 1; daesoo[6] = 1; daesoo[9] = 1; daesoo[11] = 1;
	daesoo[13] = 1; daesoo[17] = 1; daesoo[19] = 1; daesoo[20] = 1;
	daesoo[22] = 1; daesoo[24] = 1; daesoo[25] = 1; daesoo[27] = 1;
	daesoo[28] = 1; daesoo[29] = 1; daesoo[31] = 1; daesoo[33] = 1;
	daesoo[34] = 1; daesoo[36] = 1; daesoo[39] = 1; daesoo[41] = 1;
	daesoo[42] = 1; daesoo[43] = 1; daesoo[44] = 1;
}
bool Daesoo(int n)// ������Ͼȿ��� �̷���� �����̸� out. - �ζ� 9��
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
bool Suspect(int n, int s, int e) // s<= <=e ���� ���� ���� Ȯ���� �����Ƿ� 3~4�� �̴°� ����, 5������ ���ü����� ��, ���⼭ 6���ڴ� ����
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
bool Suspect2(int n, int s, int e) // Ȯ���� 0<= <=3���� ���⶧���� 0<= <=1�� �̴°� ����
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

   if (Term_3(0) && Dan(0) && Daesoo(0) && Before(0) && Side(0, 0, 1) && Suspect(1, 3, 5))//���� �˻���� ��ģ ��ȣ���� ��µȴ�.//�Լ����ڷδ� 0, 1�� ������ ������ 0�� �ش����� ����x��� ���̴�.
   {
	  if (Pick(0) && Term_2(0, 0, 0) && Suspect2(0, 1, 1)) //����� ����˻�
	  {
		 print();
	  }
   }
}*/
bool Effect(int n, int s, int e)  // 1<= <=2
{
	if (n == 0)return 1;
	//�����Ͽ��� c�����.
	// ���� ��ȣ �߿� s<= <=e�� �־����
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
		//printf("�� ");
		g_arr[6]++;
	}
	else if (ans == 3)
	{
		printf("5�� ");
		g_arr[5]++;
		g_total++;
	}
	else if (ans == 4)
	{
		printf("4�� ");
		g_arr[4]++;
		g_total++;
	}
	else if (ans == 5)
	{
		if (bonus == 1)
		{
			g_arr[2]++;
			printf("**2�� ");
			g_total++;
		}
		else
		{
			g_arr[3]++;
			printf("*3�� ");
			g_total++;
		}
	}
	else
	{
		g_arr[1]++;
		printf("***1�� ");
		g_total++;
	}
}
bool Wanted(int n)
{
	if (n == 0)return 1;
	//if (v[0] / 10 == 0)//�Ѵ� �ܹ���
	//{
	//   if (v[1] - v[0] == 2)return 0; // 2�����̸� 
	//}
	//return 1;
	//10���� ���Ӽ��� �Ÿ���.
	for (int i = 0; i < 5; i++)
	{
		if (10 <= v[i] && v[i] <= 19 && 10 <= v[i + 1] && v[i + 1] <= 19)//�Ѵ� �ʹ���
		{
			if (v[i + 1] - v[i] == 1)return 0;
		}
	}
	return 1;
}
void Check()
{
	//���࿡ �����߿� �̹�ȣ�� ������ Ȯ�� �̶�� �Ѵ�.
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
	if (fal == 0)printf("1�� ");
	fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr2[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("2�� ");
	fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr3[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("3�� ");
	fal = 0;
	for (int i = 0; i < 6; i++)
	{
		if (v[i] != arr4[i])
		{
			fal = 1;
			break;
		}
	}
	if (fal == 0)printf("4�� ");

} //��ȣ�� ��÷�Ǿ����� Ȯ��
void start2(int idx) // v�� ���� ����������� 
{
	if (v.size() == 6)
	{
		if (P_1(1) && P_2(1) && P_3(1) && P_4(1) && P_5(1) && P_6(1) && P_7(1) && P_8(1) && P_9(0)) //���ϰ˻�
		{

			if (Pick(1) && Effect(1, 1, 2) && Dan(1) && Term_3(1) && Term_2(1, 0, 1) && Daesoo(0) && Before(1, 0, 1) && Side(1, 1, 4)) //0�� �ش����� ����x��� ���̴�. 
			{
				if (Suspect(1, 3, 4) && Suspect2(1, 0, 1) && Michul(1, 0, 1)) //����� ����˻�
				{
					//suspect2�� ���� 0 1 �̿��µ� �����ϱ�. Term2�� ���Ӽ� ���� 
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

		start2(idx + 1); //�Ȼ̰ų�

	}
}
void start3(int idx)
{
	if (v.size() == 6)
	{
		if (P_1(1) && P_2(1) && P_3(1) && P_4(1) && P_5(1) && P_6(1) && P_7(1) && P_8(1) && P_9(0)) //���ϰ˻�
		{
			if (Pick(1) && Effect(1, 0, 1) && Dan(1) && Term_3(1) && Term_2(1, 0, 1) && Daesoo(1) && Before(1, 0, 1) && Side(1, 1, 4)) //0�� �ش����� ����x��� ���̴�. 
			{
				if (Suspect(1, 2, 3) && Suspect2(1, 0, 1) && Michul(1, 2, 3)) //����� ����˻�
				{
					//suspect2�� ���� 0 1 �̿��µ� �����ϱ�. Term2�� ���Ӽ� ���� 
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

		start3(idx + 1); //�Ȼ̰ų�
	}
}
void start(int K)//6���� ���ڸ� �̴´�.
{
	if (v.size() == 6) //6���� ���ڸ� �̾Ҵ�.
	{
		//�˻翡 ����

		if (P_1(1) && P_2(1) && P_3(1) && P_4(1) && P_5(1) && P_6(1) && P_7(1) && P_8(1) && P_9(0))
		{
			if (Pick(1) && Effect(1, 0, 1) && Dan(1) && Term_3(1) && Term_2(1, 0, 1) && Daesoo(1) && Before(1, 0, 1) && Side(1, 1, 2))//���� �˻���� ��ģ ��ȣ���� ��µȴ�.//�Լ����ڷδ� 0, 1�� ������ ������ 0�� �ش����� ����x��� ���̴�. 
			{
				//side �̿����� �׳� �Ѱ��� ������ ����ϰ� ����.
				if (Suspect(1, 3, 5) && Suspect2(1, 0, 2) && Michul(1, 0, 2)) //����� ����˻�
				{

					//suspect2�� ���� 0 1 �̿��µ� �����ϱ�. Term2�� ���Ӽ� ���� 
					if (Wanted(1))
					{
						print();
						//printf("�� \n");
						//������ 175�ʰ��ϴ°� �Ÿ���
						/*
						*Term_3 : 12 13 14 ���� ����3���� ����
						*Daesoo : ����� �̷���� �������� �ϸ� ��÷x��
						*@Side : ����ȸ���� �̿����� s<= <=e�� (1<= <= 2��(����) �Ǵ� 1<= <=1 �Ǵ� 0<= <=1)
						*+Suspect : ���� 1~5���� �ζ� ��ȣ�� s<= <=e�� ���� (3<= <=5����)
						+Suspect2 : ���� 6~10���� �ζ� ��ȣ�� s<= <=e�� ���� (0<= <=1���� �Ǵ� 1<= <=2)
						@Dan : _ _ _ _ _ �� ���� �������
						@Before : ���� ȸ���� ���� ���� 1�� ����
						@Pick : ���� ���ð� ���� ��ȣ�� �̴´�
						@Term_2 : 22 23 ������ ���ð��̳� (������ ���� ����Ȯ�� �����µ� �����߼��� �� ������� ���� Ȯ���� ���̷��� �׳� �ȳ����°ɷ� ��÷�Ǳ� �⵵�Ҽ��ۿ�)
						@Effect : ��ȣ �� �ϳ� �Ǵ� ���̻� ������ �ϴ°�. (�����Ͽ���C�� ���� ������ ��ȣ������ �ֱ�)
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
	//������ڸ� �̴´� �Ȼ̴´�.

	for (int i = K; i <= 45; i++)
	{
		if (n_number[i] == 0) //�������ڰ� �ƴϰ� ���Ǽ��ڰ� �ƴϸ�
		{
			number[i] = 1;
			v.push_back(i);
			start(i + 1);
			v.pop_back();
			number[i] = 0;
		}

	}
}

// ���ܼ��� �ζ� 9������ �޾Ƽ� �ű⼭ �����Ҽ� ����. ���� ���ո����� ��Ģ��� �� �̾ƺ���.

//�ζ� 9���� �м���ȣ 1~5 ���� 4�� 6~10���� 1�� ���� ����.(���ܼ� ������ ���) 
void Init_sus()
{
	printf("�̹� ȸ���� �����ϱ� ���� ���� 1~5������ ��ȣ�� 5�� * 6���������� ��ȣ�� �����ּ���.\n");
	int a;
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect[a] = 1;
	}
	//
	printf("�̹� ȸ���� �����ϱ� ���� ���� 6~10������ ��ȣ�� 5�� * 6���������� ��ȣ�� �����ּ���.\n");
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect2[a] = 1;
	}
	//
	printf("�������¼���  �����ϰ� ���� ������ ��ȣ�� �Է��Ͻÿ�. �Է��� ���� 0�Դϴ�.\n");
	while (scanf("%d", &a) && a)n_number[a] = 1;
	//

	printf("���ܼ��߿� 1~5���� �����ĺ��� ���� �� �ֽ��ϴ�.\n�����ĺ� : ");
	for (int i = 1; i <= 45; i++)
	{
		if (suspect2[i] == 1 && suspect[i] == 1)suspect2[i] = 0; //�ߺ�����
		if (n_number[i] == 1 && suspect[i] == 1)
		{
			printf("%d ", i);
			n_number[i] = 0; //���ܼ��ε� ������ �ĺ���.
		}
	}
	printf("\n");
	printf("�������ܼ��� ���Է��ϰ� ȭ�鿡 ��µ� ���� ���� ���� ���� ���ڰ� �ִٸ� �ٽ� �Է����ּ���.������ �Է��� 0�Դϴ�.\n");
	while (scanf("%d", &a) && a)n_number[a] = 1;
}

void One()
{
	printf("���� ȸ�� ��÷ ���� 7���� �Է��Ͻÿ� : \n");
	scanf("%d %d %d %d %d %d %d", &before[0], &before[1], &before[2], &before[3], &before[4], &before[5], &before[6]);
	//
	printf("�� �ְ� ���� ������ ��ȣ�� �Է��Ͻÿ�. �Է��� ���� 0�Դϴ�.\n");
	int k;
	while (scanf("%d", &k) && k)pick.push_back(k);
	//
	printf("1~9, 10~19, 20~29, 30~39, 40~45 �� 5���� ������, ������ �������� �ϴ� ������ �����ÿ�.\n");
	printf("���� : 2 1 7 1 0��\n�ܹ����� : 2��\n10������ : 1��\n20������ : �������\n30������ 1��\n40������ 0�� �����⸦ ���ϴ� ���Դϴ�.\n");
	printf("�� ������ ��ġ �ʴ� �ٸ� 7 7 7 7 7 �� �Է����ּ���.\n");
	printf("���� �ټ����� ���ڸ� �Է����ּ���.\n");
	scanf("%d %d %d %d %d", &dan[0], &dan[1], &dan[2], &dan[3], &dan[4]);

	Init_sus(); //���¼� �̱� 

	//���� ������� ���� ��ȣ�� ���⿡ ����
	//n_number[17] = 0; 
	//n_number[18] = 0;
	//n_number[23] = 0; 
	//n_number[28] = 0;
	//n_number[38] = 0;
	//n_number[e_a] = 0; 
	//n_number[e_b] = 0;
	//n_number[e_c] = 0;

	//n���� ����
	printf("�� ���� ������ �����մϴ�\n");
	for (int i = 1; i <= 45; i++)if (n_number[i] == 0)printf("%d ", i);

	printf("\n");
	//

	printf("��ȣ ���� ����Դϴ�.\n");
}
void Result()
{
	printf("����Ǽ� : %lld\n", result);
	printf("������ %d�� ��÷����ϴ�\n", g_total);
	for (int i = 1; i <= 6; i++)
	{
		printf("%d�� : %d\n", i, g_arr[i]);
	}
}
int bun2[46];
void Two()
{
	printf("���� ȸ�� ��÷ ���� 7���� �Է��Ͻÿ� : \n");
	scanf("%d %d %d %d %d %d %d", &before[0], &before[1], &before[2], &before[3], &before[4], &before[5], &before[6]);
	//
	printf("�� �ְ� ���� ������ ��ȣ�� �Է��Ͻÿ�. �Է��� ���� 0�Դϴ�.\n");
	int k;
	while (scanf("%d", &k) && k)pick.push_back(k);
	//
	printf("1~9, 10~19, 20~29, 30~39, 40~45 �� 5���� ������, ������ �������� �ϴ� ������ �����ÿ�.\n");
	printf("���� : 2 1 7 1 0��\n�ܹ����� : 2��\n10������ : 1��\n20������ : �������\n30������ 1��\n40������ 0�� �����⸦ ���ϴ� ���Դϴ�.\n");
	printf("�� ������ ��ġ �ʴ� �ٸ� 7 7 7 7 7 �� �Է����ּ���.\n");
	printf("���� �ټ����� ���ڸ� �Է����ּ���.\n");
	scanf("%d %d %d %d %d", &dan[0], &dan[1], &dan[2], &dan[3], &dan[4]);

	printf("�̹� ȸ���� �����ϱ� ���� ���� 1~5������ ��ȣ�� 5�� * 6���������� ��ȣ�� �����ּ���.\n");
	int a;
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect[a] = 1;
	}
	//
	printf("�̹� ȸ���� �����ϱ� ���� ���� 6~10������ ��ȣ�� 5�� * 6���������� ��ȣ�� �����ּ���.\n");
	for (int i = 1; i <= 5; i++)for (int j = 1; j <= 6; j++)
	{
		scanf("%d", &a);
		suspect2[a] = 1;
	}
	//

	printf("������ ��ȣ�� �Է��Ͻÿ�. �Է��� ���� 0�Դϴ�.\n");
	while (scanf("%d", &a) && a)number[a] = 1;
	//

	printf("���ܼ��߿� 1~5���� �����ĺ��� ���� �� �ֽ��ϴ�.\n�����ĺ� : ");
	for (int i = 1; i <= 45; i++)
	{
		if (suspect2[i] == 1 && suspect[i] == 1)suspect2[i] = 0; //�ߺ�����
		if (n_number[i] == 1 && suspect[i] == 1)
		{
			printf("%d ", i);
			n_number[i] = 0; //���ܼ��ε� ������ �ĺ���.
		}
	}
	printf("\n");

}
int main(void)
{
	int order;
	printf("�ζǺм� 0��, ��ȣ���� 1��, ��ȣ����2 2��\n");
	scanf("%d", &order);
	if (order == 0)
	{
		//�ζǹ�ȣ�м�

		printf("ȸ���� ��÷��ȣ 7���ڸ� �Է����ּ���\n");
		int bun[7] = { 0,0,0,0,0,0,0 }; //�м�
		scanf("%d %d %d %d %d %d %d", &bun[0], &bun[1], &bun[2], &bun[3], &bun[4], &bun[5], &bun[6]);

		for (int i = 0; i <= 6; i++)bun2[bun[i]] = 1;


		Init_sus();

		printf("\n* 1~5���� ���� ���¼��� ����մϴ�.\n");

		int cnt1 = 0;
		for (int i = 1; i <= 45; i++)if (suspect[i] == 1 && n_number[i] == 0)
		{
			cnt1++;
			printf("%d ", i);
		}
		printf("\n�� %d�� \n", cnt1);
		cnt1 = 0;

		printf("\n* 6~10���� ���� ���¼��� ����մϴ�.\n");

		for (int i = 1; i <= 45; i++)if (suspect2[i] == 1 && n_number[i] == 0)
		{
			cnt1++;
			printf("%d ", i);
		}
		printf("\n�� %d�� \n", cnt1);
		cnt1 = 0;
		//�����
		printf("\n* ���ⱸ�� ���� ����մϴ�.\n");
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
		printf("\n�� %d�� \n\n", cnt1);
		cnt1 = 0;

		//�̹� ��÷�� ���
		printf("* ����ȸ�� ��÷��ȣ �Դϴ� : ");
		for (int i = 0; i < 7; i++)
		{
			if (i == 6)printf(" +");
			printf("%d, ", bun[i]);
		}

		printf("\n\n");
		//�̿��� ���
		printf("* ���������� ���ڴ� �̿����Դϴ�\n�̿��� : ");

		for (int i = 0; i < 7; i++)
		{
			int left = bun[i] - 1;
			int right = bun[i] + 1;
			if (left == 0)left = 45;
			if (right == 46)right = 1;

			printf("%d, %d, ", left, right);
		}
		printf("\n");

		printf("\n��÷��ȣ\n");

		for (int i = 0; i <= 6; i++)printf("%d ", bun[i]);


		printf("\n���� �м�����Դϴ�\n");
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
					v1.push_back(i); // 1������ ��÷��ȣ ����
					if (bun[6] == i)bonus = 1;
				}
				else if (suspect2[i] == 1)
				{
					v2.push_back(i); //2����
					if (bun[6] == i)bonus = 2;
				}
				else
				{
					v3.push_back(i); //����
					if (bun[6] == i)bonus = 3;
				}
			}
		}
		printf("1~5���� ���� :%d��,  ", v1.size());
		for (int i = 0; i < v1.size(); i++)printf("%d ", v1[i]);

		printf("\n6~10���� ���� :%d��,  ", v2.size());
		for (int i = 0; i < v2.size(); i++)printf("%d ", v2[i]);

		printf("\n���� ���� :%d��,  ", v3.size());
		for (int i = 0; i < v3.size(); i++)printf("%d ", v3[i]);

		printf("\nbonus = %d����\n", bonus);

	}
	else if (order == 1)
	{
		One(); //�ڵ���ȣ
		//�������� ��ȣ�ȿ��� ���� ����

		start(1); //�����

		Result();
	}
	else if (order == 2)//�����α׷������
	{
		One(); // ���¼� �̰�

		for (int i = 1; i <= 45; i++)if (n_number[i] == 0)pan.push_back(i); //pan�� ���ڴ��

		sort(pan.begin(), pan.end());//����

		start2(0);
		Result();
		// �������� ������ �Է��ϱ�
		// ���߿��� �̰�, ���ͰŸ���
	}
	else
	{
		Two(); // ���¼� �̰�

		for (int i = 1; i <= 45; i++)if (number[i] == 1)pan.push_back(i); //pan�� ���ڴ��

		sort(pan.begin(), pan.end());//����

		printf("��ȣ�� �����մϴ�.\n");
		for (int i = 1; i <= 45; i++)number[i] = 0;


		start3(0);
		Result();

	}
}