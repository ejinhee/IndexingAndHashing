#pragma once
#include "LeafNode.h"
#include "vector"
class InternalNode {
public:
	LeafNode* childLeafNode[4]; // LeafNode �ٷ� �� internalNode �� ������
	InternalNode* childNode[4]; // otherwise
	InternalNode* parentNode; // �÷��ٶ� �ʿ��ҵ�	
	vector<float> interNode_score_v;
	bool isChildLeaf; // �̰� child�� leafNode�϶��� �ƴҶ� ������

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