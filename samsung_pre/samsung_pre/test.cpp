#include<stdio.h>
#include<iostream>
using namespace std;
class Parent {
public:
	int age;
	char name[11];
	Parent() {}
		Parent(int age, const char name[11]) {
			printf("���� : %d, �̸� : %s\n", age, name);
		}
};
class Child : public Parent {
public :
	int weight;
	int height;
	Child(){}
	Child(int age, const char name[11], int weight, int height) {
		this->age = age;
		strcpy(this->name, name);
		this->weight = weight;
		this->height = height;
		printf("���� : %d, �̸� : %s, ������ : %d, Ű : %d", this->age, this->name, this->weight, this->height);
	}
};
int main(void) {
	Parent parent(20, "3DPIT");
	Child child1(30, "4DPIT", 73, 178);
	return 0;
}