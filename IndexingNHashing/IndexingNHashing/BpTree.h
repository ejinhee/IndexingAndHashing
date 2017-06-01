#pragma once
#include "InternalNode.h"
#include "LeafNode.h"
#include <vector>
#include <algorithm>

using namespace std;

#define ScoreNum 504
#define ChildNum 505
#define InternalScoreVec parentNode->interNode_score_v
#define InternalChildVec parentNode->interNode_child_v
#define WillUpScore currLeafNode->leafNode_record[ScoreNum / 2].score

bool CompareObj(LeafNodeElement &e1, LeafNodeElement &e2) {
	return e1.score < e2.score;
}


class BpTree {
private:
	InternalNode* internalNode;
	InternalNode* rootNode;
	LeafNode* leafNode;

public:
	BpTree() {
		rootNode = NULL;
		LeafNode* node = new LeafNode();
		leafNode = node;
	}
	LeafNode* getLeafNode();
	InternalNode* getRootNode();
	void setLeafNode(LeafNode* set);
	void insert(LeafNodeElement insertNode);
	void search(float score);
	void splitLeaf(LeafNode* fullOne, LeafNode* newOne);
	void printSize();
	void printInternal();
};

void BpTree::insert(LeafNodeElement insertNode) {
	int childNodeNum = 0;
	printSize();

	//root node not yet
	if (!rootNode) {
		// if size not full
		if (leafNode->leafNode_record.size() < ScoreNum) {
			leafNode->leafNode_record.push_back(insertNode);
			sort(leafNode->leafNode_record.begin(), leafNode->leafNode_record.end(), CompareObj);
		}
		// if size full
		else {
			LeafNode* newLeafNode = new LeafNode();
			InternalNode* newInternalNode = new InternalNode();
			rootNode = newInternalNode;
			internalNode = newInternalNode;
			leafNode->nextLeafNode = newLeafNode;
			leafNode->parentNode = newInternalNode;
			newLeafNode->parentNode = newInternalNode;

			newInternalNode->interNode_score_v.push_back(leafNode->leafNode_record[ScoreNum/2].score);
			newInternalNode->interNode_child_v.push_back(leafNode);
			newInternalNode->interNode_child_v.push_back(newLeafNode);
			splitLeaf(leafNode, newLeafNode);
		}
	}

	//exist root node
	else {
		LeafNode* currLeafNode = leafNode;

		while (insertNode.score >= currLeafNode->leafNode_record.back().score && currLeafNode->nextLeafNode) {
			currLeafNode = currLeafNode->nextLeafNode;
			childNodeNum++;
		}
		
		// if size not full
		if (currLeafNode->leafNode_record.size() < ScoreNum) {
			currLeafNode->leafNode_record.push_back(insertNode);
			sort(currLeafNode->leafNode_record.begin(), currLeafNode->leafNode_record.end(), CompareObj);
		}
		// if size full
		else {
			LeafNode* newLeafNode = new LeafNode();
			InternalNode* parentNode = currLeafNode->parentNode;

			newLeafNode->parentNode = parentNode;
			if (currLeafNode->nextLeafNode) 
				newLeafNode->nextLeafNode = currLeafNode->nextLeafNode;
			currLeafNode->nextLeafNode = newLeafNode;

			///////////////////////////////////////////////////////// INTERNAL NODE SCORE INSERT
			int loopCount = 0;
			vector<float>::iterator itr = InternalScoreVec.begin();
			while (itr != InternalScoreVec.end()) {
				if (*itr > WillUpScore) {
					InternalScoreVec.insert(itr, WillUpScore);
					break;
				}
				itr++;
				loopCount++;
			}
			if (InternalScoreVec.size() == loopCount)
				InternalScoreVec.push_back(WillUpScore);
			//////////////////////////////////////////////////////////



			////////////////////////////////////////////////////////// INTERNAL NODE POINTER INSERT
			parentNode->interNode_child_v.insert(InternalChildVec.begin() + loopCount + 1 , newLeafNode);
			//////////////////////////////////////////////////////////

			splitLeaf(currLeafNode, newLeafNode);
		}
	}
}

void BpTree::splitLeaf(LeafNode* fullOne, LeafNode* newOne) {
	LeafNodeElement containor;

	for (int i = 0; i < ScoreNum/2; i++) {
		containor = fullOne->leafNode_record.back();
		fullOne->leafNode_record.pop_back();
		newOne->leafNode_record.insert(newOne->leafNode_record.begin(), containor);
	}
}

void BpTree::search(float score) {

}

LeafNode* BpTree::getLeafNode() {
	return leafNode;
}

InternalNode* BpTree::getRootNode() {
	return rootNode;
}

void BpTree::setLeafNode(LeafNode* set) {
	leafNode = set;
}

void BpTree::printSize() {
	LeafNode* currLeafNode = leafNode;
	cout << currLeafNode->leafNode_record.size() << " || ";
	while(currLeafNode->nextLeafNode){
		currLeafNode = currLeafNode->nextLeafNode;
		cout << currLeafNode->leafNode_record.size() << " || ";
	}
	cout << endl;
}

void BpTree::printInternal() {
	cout << "================InternalNode Scores================" << endl;
	for (int i = 0; i < internalNode->interNode_score_v.size(); i++) {
		if (internalNode->interNode_score_v[i])
			cout << internalNode->interNode_score_v[i] << " || ";
		else
			break;
	}

	cout << endl << endl;
	cout << "============InternalNode childPt Num ::" << internalNode->interNode_child_v.size();
	cout << endl << endl;

}