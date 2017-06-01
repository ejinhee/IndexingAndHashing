#pragma once
#include "Block.h"
#include "InternalNode.h"
#include <vector>
struct LeafNodeElement {
	float score; 
	Block* bptr; // ���̳��� �ؽ��� ���� ��������Ͱ� �����ϸ� �ɵ�
};
class LeafNode {
public:
	LeafNode* nextLeafNode; // ����LeafNode ����Ű�� ptr 
	InternalNode* parentNode; // overflow �߻� �� �÷��ٶ�
	vector<LeafNodeElement> leafNode_record;
	LeafNode() {
		leafNode_record.reserve(3); // ���� 3�� �����°� ����?
		nextLeafNode = NULL;
		parentNode = NULL;
	}
};