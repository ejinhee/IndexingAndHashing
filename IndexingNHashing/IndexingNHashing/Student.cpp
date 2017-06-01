#pragma once
#include "Student.h"
#include <iostream>
#define InfoSIZE 50

using namespace std;

Students::Students() {

}
void Students::setName(char src[20]) {
	copy(src, src + 20, name);
}
void Students::setStuID(unsigned stuid) {
	this->studentID = stuid;
}
void Students::setScore(float score) {
	this->score = score;
}
void Students::setAdvisorID(unsigned advid) {
	this->advisorID = advid;
}
void Students::printInfo() {
	cout << this->name << " " << this->studentID << " " << this->score << " " << this->advisorID;

	cout << endl<<endl;
	cout << name << (char*)&studentID << (char*)&score << (char*)&advisorID;
}
char* Students::outputInfo() {
	char* Info = new char[InfoSIZE];

	strcat_s(Info, 50, name);
	strcat_s(Info, 50, (char*)&studentID);
	strcat_s(Info, 50, (char*)&score);
	strcat_s(Info, 50, (char*)&advisorID);

	return Info;
}