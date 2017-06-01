#pragma once
#include "Block.h"
#include "InternalNode.h"
#include <vector>
struct LeafNodeElement {
	float score; 
	Block* bptr; // 다이내믹 해싱을 통한 블락포인터값 저장하면 될듯
};
class LeafNode {
public:
	LeafNode* nextLeafNode; // 다음LeafNode 가르키는 ptr 
	InternalNode* parentNode; // overflow 발생 시 올려줄때
	vector<LeafNodeElement> leafNode_record;
	LeafNode() {
		leafNode_record.reserve(3); // 원소 3개 가지는거 ㄱㅊ?
		nextLeafNode = NULL;
		parentNode = NULL;
	}
};