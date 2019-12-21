#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>	
using namespace std;
int ret;
int dy[] = { 1,-1,0,0 };
int dx[] = { 0,0,-1,1 };
struct Data {
	int y, x, dir, k;
};
bool cmp(Data a, Data b) {
	if (a.y == b.y)return a.x < b.x;
	return a.y < b.y;
}
vector<Data>v;
bool safeRange(int idx) {
	if (v[idx].y < -4000 || v[idx].y>4000 || v[idx].x < -4000 || v[idx].x>4000)return true;
	else return false;
}
void move() {
	for (int i = 0; i < v.size(); i++){
		v[i].y += dy[v[i].dir]; v[i].x += dx[v[i].dir];
		if(safeRange(i)){
			v.erase(v.begin() + i);
			i--;
		}
		//범위 넘었을때 지워주기 함수 짜기
	} 
}
void touchChk() {
	sort(v.begin(), v.end(),cmp);
	for (int i = 0; i < v.size(); i++) {
		int sum = v[i].k; int flag = 0;
		for (int j = i + 1; j < v.size(); j++) {
			if (!(v[i].y == v[j].y&&v[i].x == v[j].x))break;
			sum += v[j].k;//에너지 생성 저장
			v.erase(v.begin()+j);//원자 소멸
			j--;
			flag = 1;
		}
		if (flag) { ret += sum; v.erase(v.begin() + i); i--; }//부딪친 원자 지우기
	}
}
void playEnergy() {
	while (v.size() != 0) {
		move();//원자 이동
		touchChk();//원자 소멸 확인
	}
}
void init() {
	ret = 0;
	v.clear();
	int x, y, dir, k;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> dir >> k;
		v.push_back({ y * 2,x * 2,dir,k });
	}
	playEnergy();
}
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		cout << '#' << tc << " " << ret << endl;
	}
	return 0;
}