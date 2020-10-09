#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define NSIZE 13//ü������ �ִ�ũ��
#define KSIZE 11//���� �ִ� ����
struct HorseData {
	int num, dir;
};//�̵���ų�� ���� ���� 
struct Data {
	int y, x, dir,num;
};//������ġ�� ���� ����
vector<HorseData>horse;//�̵��Ҷ� ���� ���� ���
vector<Data>horse_pos[KSIZE];//�� ���� ����
int chess_place[NSIZE][NSIZE];//�Է����� �־����� �迭
vector<Data>v_place[NSIZE][NSIZE];//���� �ö��ִ¼� ����
int dy[] = { 0,0,0,-1,1 };//���� 
int dx[] = { 0,1,-1,0,0 };
int N, K;//ü������ ũ��, ���� ����
int ret;//����� �Է�
void init_input() {//�ʱ�ȭ �� �ʱ� �Է�
	//�ʱ�ȭ
	N = K = ret = 0;
	memset(chess_place, 0, sizeof(chess_place));
	horse.clear();
	for (int i = 0; i <= NSIZE; i++) { for (int j = 0; j <= NSIZE; j++) { v_place[i][j].clear(); } }
	for (int i = 0; i < KSIZE; i++)horse_pos[i].clear();
	//�ʱ� �Է�
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &chess_place[i][j]);
		}
	}
	for (int i = 1; i <= K; i++) {
		int y, x, dir;//���� ��ġ y,x,����
		scanf("%d %d %d", &y, &x, &dir);
		v_place[y][x].push_back({ y,x,dir,i});//���� ������ �ö󰣰�
		horse_pos[i].push_back({ y,x,dir,0});//�� ��������
	}
}
bool safe(int y, int x) {//���� ����
	return 1 <= y && y <= N && 1 <= x && x <= N;
}
void white(int idx){//����� ���
	int cy=horse_pos[idx].front().y;
	int cx = horse_pos[idx].front().x;
	int cdir = horse_pos[idx].front().dir;
	//���� ��ġ�� �ִ� �͵� ������
	queue<Data>q;
	for (int i = 0; i < v_place[cy][cx].size(); i++) {
		if (v_place[cy][cx][i].num == idx) {
			for (int j = i; j < v_place[cy][cx].size(); j++) {
				q.push(v_place[cy][cx][j]);//��ġ�� �͵� ����
			}
			v_place[cy][cx].erase(v_place[cy][cx].begin() + i, v_place[cy][cx].end());
			//���� 
			break;
		}
	}//for i
	while (!q.empty()) {//���� ��ġ�� �����Ű��
		//���� �ٲ��ֱ�
		Data c = q.front(); q.pop();
		Data n;
		n.y = c.y + dy[cdir];
		n.x = c.x + dx[cdir];
		n.dir = c.dir;
		n.num = c.num;
		horse_pos[c.num].front().y = n.y;
		horse_pos[c.num].front().x = n.x;
		horse_pos[c.num].front().dir = n.dir;
		horse_pos[c.num].front().num = n.num;
		v_place[n.y][n.x].push_back(n);//���� �ø���
	}
}
void red(int idx) {//������ ���
	int cy = horse_pos[idx].front().y;
	int cx = horse_pos[idx].front().x;
	int cdir = horse_pos[idx].front().dir;
	//���� ��ġ�� �ִ� �͵� ������
	queue<Data>q;
	for (int i = 0; i < v_place[cy][cx].size(); i++) {
		if (v_place[cy][cx][i].num == idx) {
			for (int j = v_place[cy][cx].size()-1; j >=i; j--) {
				q.push(v_place[cy][cx][j]);//��ġ�� �͵� ����
			}
			v_place[cy][cx].erase(v_place[cy][cx].begin() + i, v_place[cy][cx].end());
			//���� 
			break;
		}
	}//for i
	while (!q.empty()) {//���� ��ġ�� �����Ű��
		//���� �ٲ��ֱ�
		Data c = q.front(); q.pop();
		Data n;
		n.y = c.y + dy[cdir];
		n.x = c.x + dx[cdir];
		n.dir = c.dir;
		n.num = c.num;
		horse_pos[c.num].front().y = n.y;
		horse_pos[c.num].front().x = n.x;
		horse_pos[c.num].front().dir = n.dir;
		horse_pos[c.num].front().num = n.num;
		v_place[n.y][n.x].push_back(n);//���� �ø���
	}
}
void blue_out(int idx){//�Ķ��� �Ǵ� ������ ���
	int cy = horse_pos[idx].front().y;
	int cx = horse_pos[idx].front().x;
	if (horse_pos[idx].front().dir == 1) { horse_pos[idx].front().dir = 2; }
	else if (horse_pos[idx].front().dir == 2) { horse_pos[idx].front().dir = 1; }
	else if (horse_pos[idx].front().dir == 3) { horse_pos[idx].front().dir = 4; }
	else if (horse_pos[idx].front().dir == 4) { horse_pos[idx].front().dir = 3; }
	int cdir= horse_pos[idx].front().dir; 
	for (int i = 0; i < v_place[cy][cx].size(); i++) {
		if (v_place[cy][cx][i].num == idx) {
			v_place[cy][cx][i].dir = cdir;
			break;
		}
	}
	if (safe(cy + dy[cdir], cx + dx[cdir]) &&(chess_place[cy + dy[cdir]][cx + dx[cdir]] == 0|| chess_place[cy + dy[cdir]][cx + dx[cdir]] == 1)) {//������ �Ѱų� �Ķ����ΰ�찡 �ƴѰ�츸 �ѱ��
		if (chess_place[cy + dy[cdir]][cx + dx[cdir]] == 0)white(idx);//������� ������
		else if (chess_place[cy + dy[cdir]][cx + dx[cdir]] == 1)red(idx);//���������� ������
	}
}
bool chkFinish() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (v_place[i][j].size() >= 4) {//Ż�� ����
				return true;
			}
		}
	}
	return false;//Ż�� ����
}
void gameStart() {
	while (ret != 1001) {
		++ret;//�ð�����
		int flag = 0;
		for(int i=1;i<=K;i++){//���� �̵�����
			Data c = horse_pos[i].front();
			int ny = c.y + dy[c.dir]; int nx = c.x + dx[c.dir];
			if (!safe(ny, nx) || chess_place[ny][nx] == 2) {
				//�Ķ��� �Ǵ� �ٱ������� ���
				blue_out(i);
			}
			else if (chess_place[ny][nx] == 0 ) {
				//����� ���
				white(i);
			}
			else if (chess_place[ny][nx] == 1) {
				//�������� ���
				red(i);
			}
			if (chkFinish()) {
				flag = 1;
				return;
			}
		}
		if (chkFinish()) {
			break;//4���̻��ΰ� �ִ��� Ȯ��
		}
	}
	if (ret == 1001)ret = -1;//������ ����ȵǴ� ���
}
int main(void) {
	int T = 1;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		//�ʱ�ȭ �� �Է�
		init_input();
		gameStart();//�˰��� ���� ����
		//���
		printf("%d\n", ret);
		printf("#%d %d\n", tc, ret);
	}
	return 0;
}