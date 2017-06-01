#pragma once
#include "Block.h"

class HashAddressTable {
public:
	Block** table;
	int* prefix; // ppt prefix ( 몇번째 비트로 나누었는지)
	int count[1000]; //check pointer direct same block
	int hat_size = 1; // hash address table 크기 ppt왼쪽
	HashAddressTable() {
		for (int i = 0; i < 1000; i++)
			count[i] = 0; // count 값이 0이 아니면 같은 블록을 가르키는 hash address table의 원소가 1개가 아닌 2개 이상. 블록이 꽉차도 hash address table의 크기는 늘어나지 않음.
	}
	void resize() { // 블록중에 하나 꽉찰 때
		int idx;
		for (int i = 0; i < hat_size; i++) {
			if (table[i]->studentVector.size() == 128) {
				idx = i;
				break;
			}
		}
		if (count[idx] == 0) { // ppt 밑에 2개중 하나 꽉찰 때 사이즈 2배
			Block **temp = new Block*[2 * hat_size]; // table doubling
			int *temp2 = new int[2 * hat_size]; //prefix table doubling
			for (int i = 0; i < hat_size; i++) {
				temp2[i] = prefix[i];
				temp2[i + hat_size] = prefix[i];
				if (i == idx || i == idx + hat_size)
					continue;
				temp[i] = table[i];
				temp[i + hat_size] = table[i];


			}
			temp2[idx]++;
			temp2[idx + hat_size]++;
			count[idx]--;
			count[idx + hat_size]--;
			Block* newblock1 = new Block;
			Block* newblock2 = new Block;
			for (vector<Students>::iterator it = table[idx]->studentVector.begin(); it != table[idx]->studentVector.end(); it++) {
				if ((int)pow(2, (prefix[idx])) & it->getID()) // 넘쳐서 분배
					newblock2->insert(*it);
				else
					newblock1->insert(*it);
			}
			temp[idx] = newblock1;
			temp[idx + hat_size] = newblock2;
			delete table;
			table = temp;
			delete prefix;
			prefix = temp2;
			hat_size *= 2;
			for (int i = 0; i < hat_size; i++)
				count[i]++;
		}
		else { //  ppt 위에 2개 꽉찰때 count 값이 0이 아니기 때문에 hat 사이즈는 늘어나지 않음.
			for (int i = 0; i < hat_size; i++) {
				if (table[i]->studentVector.size() == 128) {
					idx = i;
					break;
				}
			}
			Block* newblock1 = new Block;
			Block* newblock2 = new Block;
			for (vector<Students>::iterator it = table[idx]->studentVector.begin(); it != table[idx]->studentVector.end(); it++) {
				if ((int)pow(2, (prefix[idx])) & it->getID())
					newblock2->insert(*it);
				else
					newblock1->insert(*it);
			}
			Block* tempblockaddr;
			tempblockaddr = table[idx];
			delete table[idx];
			bool chk = false;
			for (int i = 0; i < hat_size; i++) {
				if (table[i] == tempblockaddr) {
					count[i]--;
					if (!chk) {
						table[i] = newblock1;
						chk = true;
						prefix[i]++;
					}
					else {
						table[i] = newblock2;
						chk = false;
						prefix[i]++;
					}
				}
			}
		}
	}
};