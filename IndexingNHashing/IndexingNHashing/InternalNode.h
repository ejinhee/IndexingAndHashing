#pragma once
#include "LeafNode.h"
#include "vector"
class InternalNode {
public:
	LeafNode* childLeafNode[4]; // LeafNode 바로 위 internalNode 용 포인터
	InternalNode* childNode[4]; // otherwise
	InternalNode* parentNode; // 올려줄때 필요할듯	
	vector<float> interNode_score_v;
	bool isChildLeaf; // 이게 child가 leafNode일때랑 아닐때 때문에

	InternalNode() {
		interNode_score_v.reserve(3);
		for (int i = 0; i < 4; i++) {
			childLeafNode[i] = NULL;
			childNode[i] = NULL;
		}
		parentNode = NULL;
		isChildLeaf = false;
	}
};