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
		LeafNode* childLeafNode;					//ChildNode 는 또 다른 Internal 아니면 Leaf이다.
		InternalNode* childInternalNode;
	};

	InternalNode* parentNode;						// 올려줄때 필요할듯	
	vector<float> interNode_score_v;
	vector<LeafNode*> interNode_child_v;
	bool isChildLeaf;								// 이게 child가 leafNode일때랑 아닐때 때문에

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