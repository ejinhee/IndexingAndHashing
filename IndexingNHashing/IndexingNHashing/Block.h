#pragma once
#include "Student.h"
#include <vector>

class Block {
public:
	vector<Students> v;

	Block() {
		v.reserve(128);
	}
	int insert(Students s) {
		v.push_back(s);
		if (v.size() == 128)
			return 1;
		return 0;
	}
};