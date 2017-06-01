#pragma once
#include "Block.h"

class HashAddressTable {
public:
	Block** table;
	int* prefix; // ppt prefix ( ���° ��Ʈ�� ����������)
	int count[1000]; //check pointer direct same block
	int hat_size = 1; // hash address table ũ�� ppt����
	HashAddressTable() {
		for (int i = 0; i < 1000; i++)
			count[i] = 0; // count ���� 0�� �ƴϸ� ���� ����� ����Ű�� hash address table�� ���Ұ� 1���� �ƴ� 2�� �̻�. ����� ������ hash address table�� ũ��� �þ�� ����.
	}
	void resize() { // ����߿� �ϳ� ���� ��
		int idx;
		for (int i = 0; i < hat_size; i++) {
			if (table[i]->studentVector.size() == 128) {
				idx = i;
				break;
			}
		}
		if (count[idx] == 0) { // ppt �ؿ� 2���� �ϳ� ���� �� ������ 2��
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
				if ((int)pow(2, (prefix[idx])) & it->getID()) // ���ļ� �й�
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
		else { //  ppt ���� 2�� ������ count ���� 0�� �ƴϱ� ������ hat ������� �þ�� ����.
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