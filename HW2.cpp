#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>


#define TOKEN ","

using namespace std;

int num = 0;
class Students {
private:
	char name[20];
	unsigned studentID;
	float score;
	unsigned advisorID;
public:
	Students();
	void setName(char src[20]);
	void setStuID(unsigned stuid);
	void setScore(float score);
	void setAdvisorID(unsigned advid);
	void printInfo();

	unsigned getID() {
		return studentID;
	}
};
Students::Students() {

}
void Students::setName(char src[20]) {
	copy(src, src + 20, name);
}
void Students::setStuID(unsigned stuid) {
	this->studentID = stuid;
}
void Students::setScore(float score) {
	this->score = score;
}
void Students::setAdvisorID(unsigned advid) {
	this->advisorID = advid;
}
void Students::printInfo() {
	cout << this->name << " " << this->studentID << " " << this->score << " " << this->advisorID;
}

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
			if (table[i]->v.size() == 128) {
				idx = i;
				break;
			}
		}
		if (count[idx] ==0) { // ppt 밑에 2개중 하나 꽉찰 때 사이즈 2배
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
			for (vector<Students>::iterator it = table[idx]->v.begin(); it != table[idx]->v.end(); it++) {
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
				if (table[i]->v.size() == 128) {
					idx = i;
					break;
				}
			}
			Block* newblock1 = new Block;
			Block* newblock2 = new Block;
			for (vector<Students>::iterator it = table[idx]->v.begin(); it != table[idx]->v.end(); it++) {
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
int main() {
	ifstream fin("sampleData.csv");
	ofstream fout("Students.DB", ios_base::out | ios_base::binary);

	Students stu;
	string name;
	unsigned stuid, advid;
	float score;

	
	char temp[50];
	char *token;
	char* context;
	int n;
	fin >> n;
	fin.getline(temp, 50); // 개행
	
	Block b;
	HashAddressTable hat;
	DynamicHash dh(b, hat);
	for (int i = 0; i < n; i++) {
		fin.getline(temp, 50);
		token = strtok_s(temp, TOKEN, &context);
		stu.setName(token);
		token = strtok_s(NULL, TOKEN, &context);
		stuid = stoul(token, nullptr, 0);
		stu.setStuID(stuid);
	
		token = strtok_s(NULL, TOKEN, &context);
		score = strtof(token, 0);
		stu.setScore(score);
		token = strtok_s(NULL, TOKEN, &context);
		advid = stoul(token, nullptr, 0);
		stu.setAdvisorID(advid);
		
		if(fout.write((char*)&stu, sizeof stu));
		num++;
		dh.insert(stu);

	}
	
	fout.close();
	//stu.printInfo();
	return 0;
}