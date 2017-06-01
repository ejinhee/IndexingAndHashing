
#pragma once
#include <iostream>

using namespace std;

class Students {
private:
	char name[20];
	unsigned studentID;
	float score;
	unsigned advisorID;
public:
	Students();
	void setName(char src[20]);
	void setStuID(unsigned stuid);
	void setScore(float score);
	void setAdvisorID(unsigned advid);
	void printInfo();
	char* outputInfo();

	unsigned getID() {
		return studentID;
	}
};