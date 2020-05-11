#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>
#include<vector>
#include<math.h>
using namespace std;
int main(void) {
	int y1,y2,x1,x2;
	scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
	int d1 = abs(y1 - y2) + abs(x1 - x2);


	int m_fDegree = atan2f((float)y2 - y1, (float)x2 - x1) * 180 / 3.1415f;

	//if (m_fDegree < 0)m_fDegree = 180 + m_fDegree;
	cout <<m_fDegree <<endl;

	
}	