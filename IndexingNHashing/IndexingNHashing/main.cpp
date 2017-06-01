#include "Student.h"
#include "Block.h"
#include "HashAddressTable.h"
#include "DynamicHash.h"
#include "InternalNode.h"
#include "LeafNode.h"
#include "BpTree.h"

#include <fstream>
#include <string>
#include <string.h>
#include "main.h"

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

	BpTree BplusTree;
	LeafNodeElement* newRecord_Btree;

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

		newRecord_Btree = new LeafNodeElement;
		newRecord_Btree->blockNum = stu.getID() % 32;
		newRecord_Btree->score = score;
		BplusTree.insert(*newRecord_Btree);

		fout.write((char*)&stu, sizeof stu);
		num++;
		hashBlocks.insert(stu);
	}

	hashBlocks.hash_print();			//Students.Hash 출력

	ofstream fout2("Students_score.idx", ios_base::out | ios_base::binary);
	BplusTree.printInternal();
	
	//while (BplusTree.getLeafNode()->nextLeafNode) {
	//	BplusTree.getLeafNode()->printAll();
	//	BplusTree.setLeafNode(BplusTree.getLeafNode()->nextLeafNode);
	//}
	//BplusTree.getLeafNode()->printAll();
	
	BplusTree.getRootNode()->interNode_child_v[0]->printAll();
	BplusTree.getRootNode()->interNode_child_v[1]->printAll();
	BplusTree.getRootNode()->interNode_child_v[2]->printAll();
	BplusTree.getRootNode()->interNode_child_v[3]->printAll();
	BplusTree.getRootNode()->interNode_child_v[4]->printAll();
	BplusTree.getRootNode()->interNode_child_v[5]->printAll();
	BplusTree.getRootNode()->interNode_child_v[6]->printAll();
	BplusTree.getRootNode()->interNode_child_v[7]->printAll();
	BplusTree.getRootNode()->interNode_child_v[8]->printAll();
	BplusTree.getRootNode()->interNode_child_v[9]->printAll();
	BplusTree.getRootNode()->interNode_child_v[10]->printAll();
	BplusTree.getRootNode()->interNode_child_v[11]->printAll();



	return 0;
}