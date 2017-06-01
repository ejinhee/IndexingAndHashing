#pragma once
#include "LeafNode.h"
#include <vector>

#define ScoreNum 504
#define ChildNum 505

using namespace std;

class LeafNode;

class InternalNode {
public:
	union ChildNode {
		LeafNode* childLeafNode;					//ChildNode �� �� �ٸ� Internal �ƴϸ� Leaf�̴�.
		InternalNode* childInternalNode;
	};

	InternalNode* parentNode;						// �÷��ٶ� �ʿ��ҵ�	
	vector<float> interNode_score_v;
	vector<LeafNode*> interNode_child_v;
	bool isChildLeaf;								// �̰� child�� leafNode�϶��� �ƴҶ� ������

	InternalNode() {
		interNode_score_v.reserve(ScoreNum);
		interNode_child_v.reserve(ChildNum);

		parentNode = NULL;
		isChildLeaf = false;
	}

	void sort();
	bool isFull();
};

void InternalNode::sort() {

}

bool InternalNode::isFull() {
	return 0;
}