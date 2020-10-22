#include<stdio.h>
#include<vector>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
int B[10][10];//����
int ret1, ret2;//���������, ����� ���� ��ϼ�
int N;//����� ���� Ƚ��
int t, y, x;//ũ�⺰ ��ġ
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int numchk[10001];
struct Data {
	int y, x, num;
};
bool safe(int y, int x) {//���� ��Ż ����
	return 0 <= y && y < 10 && 0 <= x && x < 10;
}
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = t = y = x = ret1 = ret2 = 0;
	memset(B, 0, sizeof(B));
	//�ʱ��Է�
	scanf("%d", &N);//��� �Է�
}
void blueDown(int num) {
	Data c;
	c.y = y; c.x = x; int dir = 0;
	while (1) {
		Data n;
		n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
		if (!safe(n.y, n.x) || (t == 1 && B[n.y][n.x] != 0) || (t == 2 && B[n.y][n.x] != 0)
			|| (t == 3 && (B[n.y][n.x] != 0 || B[n.y + 1][n.x] != 0))) {
			n.y -= dy[dir]; n.x -= dx[dir];
			if (t == 1) {
				B[n.y][n.x] = num;
			}
			if (t == 2) {
				B[n.y][n.x - 1] = num; B[n.y][n.x] = num;
			}
			if (t == 3) {
				B[n.y][n.x] = num;
				B[n.y + 1][n.x] = num;
			}
			break;
		}
		c.y = n.y; c.x = n.x;//�̵���Ű��
	}
}
void greenDown(int num) {
	Data c;
	c.y = y; c.x = x; int dir = 1;
	while (1) {
		Data n;
		n.y = c.y + dy[dir]; n.x = c.x + dx[dir];
		if (!safe(n.y, n.x) || (t == 1 && B[n.y][n.x] != 0) || (t == 3 && B[n.y][n.x] != 0)
			|| (t == 2 && (B[n.y][n.x] != 0 || B[n.y][n.x + 1] != 0))) {
			n.y -= dy[dir]; n.x -= dx[dir];
			if (t == 1) {
				B[n.y][n.x] = num;
			}
			if (t == 2) {
				B[n.y][n.x] = num; B[n.y][n.x + 1] = num;
			}
			if (t == 3) {
				B[n.y - 1][n.x] = num;
				B[n.y][n.x] = num;
			}
			break;
		}
		c.y = n.y; c.x = n.x;//�̵���Ű��
	}
}
int visit[10][10] = { 0, };// �湮 üũ�� ��� ��������
void dfs(int y, int x, int num,int same) {
	for (int dir = 0; dir < 4; dir++) {
		Data n;
		n.y = y + dy[dir]; n.x = x + dx[dir];
		if (safe(n.y, n.x) && visit[n.y][n.x] == 0 && B[n.y][n.x]==same) {
			visit[n.y][n.x] = same;
			dfs(n.y, n.x, num,same);
		}
	}
}
void greenBreakDown() {
	memset(visit, 0, sizeof(visit));
	int cnt = 0;
	for (int i = 4; i <= 10; i++) {
		for (int j = 0; j < 4; j++) {
			if (visit[i][j] == 0 && B[i][j] != 0) {
				cnt++;
				visit[i][j] = B[i][j];
				dfs(i, j, cnt,B[i][j]);
			}
		}
	}
	int num = 1;
	memset(numchk, 0, sizeof(numchk));
	while (cnt--) {//��ϸ��� ������
		int cnum = num;
		vector<Data>v;
		v.clear();
		int c = 0;
		for (int i = 9; i >= 4; i--) {
			for (int j = 0; j < 4; j++) {
				if (visit[i][j] != 0) {
					if (numchk[visit[i][j]] == 0 && c == 0) {
						numchk[visit[i][j]] = 1;
						num = visit[i][j];
						c++;
					}
					if (c == 1 && visit[i][j] == num) {
						v.push_back({ i,j,B[i][j] });
						visit[i][j] = 0;
						B[i][j] = 0;
						cnum = num;
					}
				}
			}//for j
		}//for i
		while (1) {
			if (v.size() == 0)break;
			int flag = 0;
			for (int i = 0; i < v.size(); i++) {
				Data n;
				n.y = v[i].y + dy[1]; n.x = v[i].x + dx[1];
				if (!safe(n.y, n.x) || B[n.y][n.x] != 0) {
					for (int j = 0; j < i; j++) {
						v[j].y -= dy[1]; v[j].x -= dx[1];
					}
					flag = 1; break;
				}
				v[i].y = n.y; v[i].x = n.x;//�̵�
			}//for i
			if (flag)break;
		}//while 1
		for (int i = 0; i < v.size(); i++) {
			B[v[i].y][v[i].x] = v[i].num;
		}
	}
}
void greenChk() {
	int flag = 0;//���� ���üũ
	while (1) {
		int f = 0;
		for (int i = 4; i <= 10; i++) {
			int cnt = 0;//�� üũ
			flag = 0;
			for (int j = 0; j < 4; j++) {
				if (B[i][j] != 0)cnt++;
			}
			if (cnt == 4) {//�� ����
				for (int j = 0; j < 5; j++) {
					B[i][j] = 0;
				}
				//4. �� �Ǵ� �� ���� �� ���� +1��
				f++;ret1++;//���� �߰�
			}
			if (i == 10 && f == 0) {
				flag = -1; break;
			}
		}
		if (flag == -1)break;
			greenBreakDown();
	}
}
void blueBreakDown() {
	memset(visit, 0, sizeof(visit));
	int cnt = 0;
	for (int j = 4; j <= 10; j++) {
		for (int i = 0; i < 4; i++) {
			if (visit[i][j] == 0 && B[i][j] != 0) {
				cnt++;
				visit[i][j] = B[i][j];
				dfs(i, j, cnt, B[i][j]);
			}
		}
	}
	int num = 1;
	memset(numchk, 0, sizeof(numchk));
	while (cnt--) {//��ϸ��� ������
		vector<Data>v;
		v.clear();
		int cnum = num;
		int c = 0;
		for (int j = 9; j >= 4; j--) {
		for (int i = 0; i < 4; i++) {
				if (visit[i][j]!=0) {
					if (numchk[visit[i][j]] == 0&&c==0) {
						numchk[visit[i][j]] = 1;
						num = visit[i][j];
						c++;
					}
					if (c==1&&visit[i][j] == num) {
						v.push_back({ i,j,B[i][j] });
						visit[i][j] = 0;
						B[i][j] = 0;
						cnum = num;
					}
				}
			}//for j
		}//for i
		while (1) {
			if (v.size() == 0)break;
			int flag = 0;
			for (int i = 0; i < v.size(); i++) {
				Data n;
				n.y = v[i].y + dy[0]; n.x = v[i].x + dx[0];
				if (!safe(n.y, n.x) || B[n.y][n.x] != 0) {
					for (int j = 0; j < i; j++) {
						v[j].y -= dy[0]; v[j].x -= dx[0];
					}
					flag = 1; break;
				}
				v[i].y = n.y; v[i].x = n.x;//�̵�

			}//for i
			if (flag)break;
		}//while 1
		for (int i = 0; i < v.size(); i++) {
			B[v[i].y][v[i].x] = v[i].num;
		}
	}
}
void blueChk() {
	int flag = 0;//���� ���üũ
	while (1) {
		int f = 0;
		for (int j = 4; j <= 10; j++) {
			int cnt = 0;//�� üũ
			for (int i = 0; i < 4; i++) {
				if (B[i][j] != 0)cnt++;
			}
			if (cnt == 4) {//�� ����
				for (int i = 0; i < 4; i++) {
					B[i][j] = 0;
				}
				//4. �� �Ǵ� �� ���� �� ���� +1��
				flag = 1; f++;
				ret1++;//���� �߰�
			}
			if (j== 10 && f == 0) {
				flag = -1; break;
			}
		}
		if (flag == -1)break;
			blueBreakDown();
	}
}
void SgreenChk() {
	int flag = 0;
	for (int i = 4; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (B[i][j] != 0) {//Ư�� ��� 
				flag++;
				break;
			}
		}
	}
	if (flag != 0) {
		for (int i = 0; i < flag; i++) {
			for (int j = 0; j < 4; j++) {//����
				B[9-flag][j] = 0;
			}
		}
			greenBreakDown();
	}
}
void SblueChk() {
	int flag = 0;
	for (int j = 4; j <= 5; j++) {
		for (int i = 0; i < 4; i++) {
			if (B[i][j] != 0) {//Ư�� ��� 
				flag++;
				break;
			}
		}
	}
	if (flag!=0) {
		for (int j = 0; j < flag; j++) {
			for (int i = 0; i < 4; i++) {
				B[i][9 - j] = 0;
			}
		}
			blueBreakDown();
		}
}
void game(int i) {
	//1. �����̵�(���̳� �ٸ� ��ϱ��� �̵���Ű��)

	blueDown(i); greenDown(i);
	//2. �ʷ��� �����̸� ������
	greenChk();
	//3. �Ķ��� �����̸� ������
	blueChk();
	//5. Ư��ĭ �Ķ� ����ȣ4,5�� ��ġ�ϸ� ���� �� �� �� ���� ���� 
		//�ʷ� ���ȣ 4,5 ��ġ�ϸ� ���� �� �� �� ���� ���� 
	SgreenChk();
	SblueChk();
	//*�����ϰ� ������ �� ������ ��������(dfs�� üũ�ؾ��ҵ�)
	//�����ϰ� ������ �� �ݺ��ؼ� ���̻� �������°� ������ ���� ����

}
int main(void) {
	int T = 1;//�׽�Ʈ���̽� ����
	//scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init_input();//�ʱ�ȭ �� �ʱ��Է�
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &t, &y, &x);
			game(i+1);//���� ����
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (B[i][j] != 0)ret2++;
			}
		}
		printf("%d\n%d\n", ret1, ret2);
		//printf("#%d %d %d\n", tc, ret1, ret2);
	}
	return 0;
}
