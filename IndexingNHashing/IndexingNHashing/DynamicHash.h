#pragma once
#include "HashAddressTable.h"
#include <fstream>

// ��ǻ� Hash Table �� ���� ������ ���⿡�� ���ĳ���
// ���� Hash Table ���� resize �ۿ� ����.

class DynamicHash {
private:
	Block* b; // �ʱ�ȭ�� ���Ͽ� ����??
	HashAddressTable* hat; // �̰� ���Ͽ� HashTable ���� �Ұ�.
public:
	DynamicHash(Block &b, HashAddressTable &hat) {
		this->b = &b;
		this->hat = &hat;

		hat.table = new Block*[1];
		hat.table[0] = &b;
		hat.prefix = new int[1];
		hat.prefix[0] = 0;
	}

	void insert(Students stu) {
		int idx = stu.getID() % hat->hat_size;
		if (hat->table[idx]->insert(stu))
			hat->resize();
	}

	void print() {
		cout << "BlockSize" << hat->hat_size << endl;
		for (int i = 0; i < hat->hat_size; i++)
			cout << hat->table[i]->studentVector.size() << endl;
	}

	void hash_print() {
		fstream fout("Students.hash", ios_base::out | ios_base::binary);

		for (int i = 0; i < hat->hat_size; i++) {				// ��� ���� ��ȸ
			for (int j = 0; j < hat->table[i]->studentVector.size(); j++) {		// ���ڵ� ���� ��ȸ
				fout.write((char*)&hat->table[i]->studentVector[j], sizeof hat->table[i]->studentVector[j]);
			}

		}
	}
};