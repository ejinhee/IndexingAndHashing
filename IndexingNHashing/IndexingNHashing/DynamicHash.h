#pragma once
#include "HashAddressTable.h"

class DynamicHash {
private:
	Block* b;
	HashAddressTable* hat;
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
		cout << hat->hat_size << endl;
		for (int i = 0; i < hat->hat_size; i++)
			cout << hat->table[i]->v.size() << endl;
	}
};