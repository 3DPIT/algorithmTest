#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int MAX, T, N, sec = 0;
int result[10004];
typedef struct ctr
{
	int idx, time;
}ctr;
vector <ctr>L;
vector <ctr>R;

bool cmp(ctr a, ctr b)
{
	return a.idx < b.idx;

}
int main(void)
{
	scanf("%d %d %d", &MAX, &T, &N);
	for (int i = 1; i <= N; i++)
	{
		int t;
		char d[7];
		scanf("%d %s", &t, &d);
		if (d[0] == 'l')L.push_back({ i, t });
		else R.push_back({ i, t });
	}
	sort(L.begin(), L.end(), cmp);
	sort(R.begin(), R.end(), cmp);

	int na = 0; //����

	while (L.size() + R.size() != 0)//��Ծƴϸ�
	{
		int fal = 0;
		if (na == 0) //L
		{
			for (int i = 0; i < MAX; i++)
			{
				if (L.size() > 0)
				{
					if (L[i].time <= sec)
					{
						result[L[i].idx] = sec + T;
						L.erase(L.begin() + i);
						i--;
						fal = 1;
					}
					else break;
				}
				else break;
			}
			if (fal == 1) //�Ѹ��̶� �¿���
			{
				na = 1;
				sec += T;
			}
			else //�Ѹ� ���¿���
			{
				//�ݴ��� ����� ������ �����Ѵ�.
				if (R.size() > 0)
				{
					if (R[0].time <= sec)
					{
						fal = 1;
						sec += T;
						na = 1;//�ݴ������� �̵� 
					}
				}
			}
		}
		else //R
		{
			for (int i = 0; i < MAX; i++)
			{
				if (R.size() > 0)
				{
					if (R[i].time <= sec)
					{
						result[R[i].idx] = sec + T;
						R.erase(R.begin() + i);
						i--;
						fal = 1;
					}
					else break;
				}
				else break;
			}
			if (fal == 1) //�Ѹ��̶� �¿���
			{
				na = 0;
				sec += T;
			}
			else //�Ѹ� ���¿���
			{
				//�ݴ��� ����� ������ �����Ѵ�.
				if (L.size() > 0)
				{
					if (L[0].time <= sec)
					{
						fal = 1;
						sec += T;
						na = 0;//�ݴ������� �̵� 
					}
				}
			}
		}
		if (fal == 0)sec++;
	}
	for (int i = 1; i <= N; i++)printf("%d\n", result[i]);

}