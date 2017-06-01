#pragma once
#include "Block.h"
#include "InternalNode.h"
#include <vector>
#define ScoreNum 504
#define ChildNum 505

using namespace std;

struct LeafNodeElement {
	float score; 
	int blockNum;
};

class InternalNode;

class LeafNode {
public:
	LeafNode* nextLeafNode;				// ����LeafNode ����Ű�� ptr 
	InternalNode* parentNode;			// overflow �߻� �� �÷��ٶ�
	vector<LeafNodeElement> leafNode_record;

	LeafNode() {
		leafNode_record.reserve(ScoreNum);		// ���� 3�� �����°� ����?
		nextLeafNode = NULL;
		parentNode = NULL;
	}

	void printAll();
};

void LeafNode::printAll() {
	for (vector<LeafNodeElement>::iterator itr = leafNode_record.begin();
		itr != leafNode_record.end();
		itr++) {
		cout << itr->score <<":"<< itr->blockNum <<" | ";
	}
	cout << endl<<endl;
}