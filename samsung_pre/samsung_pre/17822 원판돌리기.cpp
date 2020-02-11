#include <stdio.h>
#include <deque>
using namespace std;
int N, M, K;
int input[54][54] = { 0, };
deque <int>deq;
int fal = 0;

void bomb(int y, int x, int tmp)
{
	int l = x - 1, r = x + 1;
	if (l == 0)l = M;
	if (r == M + 1)r = 1;
	input[y][x] = 0;
	if (input[y][l]==tmp) //왼
	{
		bomb(y, l,tmp);
	}
	if (input[y][r] == tmp)
	{
		bomb(y, r, tmp);
	}
	if (y<N && input[y + 1][x] == tmp)
	{
		bomb(y+1, x, tmp);
	}
	if (y > 0 && input[y - 1][x] == tmp) {
		bomb(y - 1, x, tmp);
	}
}
void del()
{
	fal = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (input[i][j] != 0)
			{
				int tmp = input[i][j];
				int l = j - 1, r = j + 1;
				if (l == 0)l = M;
				if (r == M + 1)r = 1;
				
				if (j>0&&input[i][l] == tmp) //왼
				{
					fal = 1;
					input[i][j] = 0;
					bomb(i, l, tmp);
				}
				if (j!=M&&input[i][r] == tmp)
				{
					fal = 1;
					input[i][j] = 0;
					bomb(i, r, tmp);
				}
				if (i != N && input[i + 1][j] == tmp)
				{
					fal = 1;
					input[i][j] = 0;
					bomb(i + 1, j, tmp);
				}
				if (i>0 && input[i - 1][j] == tmp)
				{
					fal = 1;
					input[i][j] = 0;
					bomb(i - 1, j, tmp);
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++)for (int j = 1; j <= M; j++)scanf("%d", &input[i][j]);
	
	while (K--)
	{
		int num, dir, range;
		scanf("%d %d %d", &num, &dir, &range);

		//num의배수이면 회전, 0이면 시계, 1이면 반시계,range는 횟수
		for (int i = 1; i <= N; i++)
		{
			if (i%num == 0) //배수이면 
			{
				int k = range;
				for (int j = 1; j <= M; j++)
				{
					deq.push_back(input[i][j]);
				}
				if (dir == 0)//시계
				{
					while (k--)
					{
						//deq에넣는다.
						int tmp = deq.back();
						deq.pop_back();
						deq.push_front(tmp);
					}
				}
				else
				{
					while (k--)
					{
						int tmp = deq.front(); 
						deq.pop_front();
						deq.push_back(tmp);
					}
				}
				int j = 1;
				while (deq.size() != 0)
				{
					input[i][j++] = deq.front();
					deq.pop_front();
				}
			}
		}

		del();
		if (fal == 0)
		{
			//평균구하고, 평균보다 큰수에서 1뺴고
			float sum = 0;
			float num = 0;
			for(int i = 1; i<=N; i++)
			{
				for (int j = 1; j <= M; j++)
				{
					if (input[i][j] != 0)
					{
						sum += input[i][j];
						num++;
					}
				}
			}
			float avg = (float)sum / num;
			for (int i = 1; i <= N; i++)
			{
				for (int j = 1; j <= M; j++)
				{
					if (input[i][j] != 0 )
					{
						if (input[i][j] < avg)input[i][j]++;
						else if (input[i][j] > avg)input[i][j]--;
					}
				}
			}
		}

	}
	int summ = 0;
	for (int i = 1; i <= N; i++)for (int j = 1; j <= M; j++)summ += input[i][j];
	
	printf("%d", summ);
}