#include<iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
struct Data {
	int data; int idx;//Ʈ���� ���Կ� , ���� ��ġ
};
int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;
	queue<int>passingBridge;//�������� Ʈ�� ����
	queue<int>passedBridge;//�ٸ������� Ʈ�� ����
	vector<Data>Bridge;
	int sum = 0;
	int cnt = 0;
	int size = truck_weights.size();//Ʈ������
	while (1) {
		if (passingBridge.size() >= bridge_length) {
			if (passingBridge.front() != 0)passedBridge.push(1);//Ʈ��üũ
			sum -= passingBridge.front();
			passingBridge.pop();//�ϳ� �����Ű��
		}
		if (passedBridge.size() == size)break;//�ٵ����ϸ� ����
		if (truck_weights.size()!=0&&sum + truck_weights[0] <= weight)
		{//�ö󰥼� �ִ� ����
			sum += truck_weights.front();//�ٸ� ���� ����
			Bridge.push_back({ truck_weights.front(),0});//�ٸ��� �ø���
			passingBridge.push(truck_weights.front());//�ٸ��� �������ΰ�
			truck_weights.erase(truck_weights.begin());
		}
		else
		passingBridge.push(0);//������� ������ ����
		
		answer++;//�ð� 1�� ����
	}
	return answer+1;
}
int main(void) {
	cout << solution(2, 10, { 7,4,5,6 })<<endl;
	cout << solution(100,100, { 10 })<<endl;
	cout << solution(100, 100, { 10,10,10,10,10,10,10,10,10,10 })<<endl;
	return 0;
}