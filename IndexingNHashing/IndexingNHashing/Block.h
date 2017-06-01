#pragma once
#include "Student.h"
#include <vector>

class Block {
public:
	vector<Students> studentVector;

	Block() {
		studentVector.reserve(128);
	}
	int insert(Students s) {
		studentVector.push_back(s);
		if (studentVector.size() == 128)
			return 1;
		return 0;
	}
};