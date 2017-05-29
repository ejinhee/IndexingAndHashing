#include <iostream>
#include <fstream>
#include <string>
#include <string.h>



#define TOKEN ","

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
};
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
}
int main() {
	ifstream fin("sampleData.csv");
	ofstream fout("Students.DB", ios_base::out | ios_base::binary);
	int n;
	Students stu;
	string name;
	unsigned stuid, advid;
	float score;

	char temp[50];
	char *token;
	char* context;
	fin >> n;
	fin.getline(temp, 50); // °³Çà
	
	for (int i = 0; i < n; i++) {
		fin.getline(temp, 50);
		token = strtok_s(temp, TOKEN, &context);
		stu.setName(token);
		token = strtok_s(NULL, TOKEN, &context);
		stuid = stoul(token, nullptr, 0);
		stu.setStuID(stuid);
		token = strtok_s(NULL, TOKEN, &context);
		score = strtof(token, 0);
		stu.setScore(score);
		token = strtok_s(NULL, TOKEN, &context);
		advid = stoul(token, nullptr, 0);
		stu.setAdvisorID(advid);

		fout.write((char*)&stu, sizeof stu);
	}
	Students stuarr[128];
	ifstream inf("Students.DB", ios_base::in | ios_base::binary);
	inf.read((char*)&stuarr, 4096);
	//inf.read((char*)&stuarr[32], 1024);
	//inf.read((char*)&stu, sizeof stu);
	
	for (int i = 0; i < 1; i++) {
		stuarr[127].printInfo();
		cout << endl;
	}
	
	
	fout.close();
	//stu.printInfo();
	return 0;
}