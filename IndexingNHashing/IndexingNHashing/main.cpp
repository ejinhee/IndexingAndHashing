#include "Student.h"
#include "Block.h"
#include "HashAddressTable.h"
#include "DynamicHash.h"

#include <fstream>
#include <string>
#include <string.h>

#define TOKEN ","

using namespace std;

int num = 0;

int main() {
	ifstream fin("sampleData.csv");
	ofstream fout("Students.DB", ios_base::out | ios_base::binary);

	Students stu;
	string name;
	unsigned stuid, advid;
	float score;

	char temp[50];
	char *token;
	char *context;
	int studentNum;
	fin >> studentNum;
	fin.getline(temp, 50); // 개행

	Block block;
	HashAddressTable hashTable;
	DynamicHash hashBlocks(block, hashTable);

	for (int i = 0; i < studentNum; i++) {
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

		if (fout.write((char*)&stu, sizeof stu));
		num++;
		hashBlocks.insert(stu);
	}

	hashBlocks.print();  //					 print each record number of hash blocks
	hashBlocks.fprint(); //					 Students.Hash 출력

	fout.open("Students_score.idx", ios_base::out | ios_base::binary);

	stu.printInfo();
	return 0;
}