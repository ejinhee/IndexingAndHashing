#pragma once
#include "HashAddressTable.h"
#include <fstream>

// 사실상 Hash Table 에 대한 연산을 여기에다 뭉쳐놓음
// 실제 Hash Table 에는 resize 밖에 없음.

class DynamicHash {
private:
	Block* b; // 초기화를 위하여 존재??
	HashAddressTable* hat; // 이걸 통하여 HashTable 접근 할것.
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
			cout << hat->table[i]->studentVector.size() << endl;
	}

	void fprint() {
		fstream fout("Students.hash", ios_base::out | ios_base::binary);

		for (int i = 0; i < hat->hat_size; i++) {				// 블락 단위 순회
			if (fout.write((char*)&i, sizeof i));				// 블락 넘버 쓰기  ->> 이부분 reference 붙이면 주소가되고 안붙이면 에러남 수정필요
			
			for (int j = 0; j < hat->table[i]->studentVector.size(); j++) {		// 레코드 단위 순회
				if (fout.write((char*)&hat->table[i]->studentVector[j], sizeof hat->table[i]));
			}

			if (fout.write("\n\n", sizeof "\n\n" ));							// 블락 마다 개행문 추가
		}
	}
};