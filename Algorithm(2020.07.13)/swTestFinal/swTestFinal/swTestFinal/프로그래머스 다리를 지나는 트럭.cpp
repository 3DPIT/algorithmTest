#include<iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
struct Data {
	int data; int idx;//트럭의 무게와 , 현재 위치
};
int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;
	queue<int>passingBridge;//통행중인 트럭 저장
	queue<int>passedBridge;//다리지나간 트럭 저장
	vector<Data>Bridge;
	int sum = 0;
	int cnt = 0;
	int size = truck_weights.size();//트럭개수
	while (1) {
		if (passingBridge.size() >= bridge_length) {
			if (passingBridge.front() != 0)passedBridge.push(1);//트럭체크
			sum -= passingBridge.front();
			passingBridge.pop();//하나 방출시키기
		}
		if (passedBridge.size() == size)break;//다도착하면 종료
		if (truck_weights.size()!=0&&sum + truck_weights[0] <= weight)
		{//올라갈수 있는 무게
			sum += truck_weights.front();//다리 무게 증가
			Bridge.push_back({ truck_weights.front(),0});//다리에 올리기
			passingBridge.push(truck_weights.front());//다리에 진행중인것
			truck_weights.erase(truck_weights.begin());
		}
		else
		passingBridge.push(0);//순서대로 옆으로 쌓임
		
		answer++;//시간 1초 증가
	}
	return answer+1;
}
int main(void) {
	cout << solution(2, 10, { 7,4,5,6 })<<endl;
	cout << solution(100,100, { 10 })<<endl;
	cout << solution(100, 100, { 10,10,10,10,10,10,10,10,10,10 })<<endl;
	return 0;
}