#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>


#define TOKEN ","

using namespace std;
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
		if (v.capacity() == 128)
			return 1;
		return 0;
	}
};
class HashAddressTable {
public:
	Block** table;
	int* prefix;
	int hat_size = 1;
	int hat_cnt = 0;
	HashAddressTable() {
	}
	void resize() { // 블록중에 하나 꽉찰 때
		int idx;
		bool doubling;
		for (int i = 0; i < hat_size; i++) {
			if (table[i]->v.capacity() == 128) {
				idx = i;
				break;
			}
		}
		if (pow(2, idx) == (double)hat_size) { // ppt 밑에 2개중 하나 꽉찰 때 사이즈 2배
			Block **temp = new Block*[2 * hat_size]; // table doubling
			int *temp2 = new int[2 * hat_size]; //prefix doubling
			for (int i = 0; i < hat_size; i++) {
				temp[2 * i] = table[i];
				temp[2 * i + 1] = table[i];
				temp2[2 * i] = prefix[i];
				temp2[2 * i + 1] = prefix[i];
				temp2[2 * idx]++;
				temp2[2 * idx+1]++;
				Block newblock1,newblock2;
				for (vector<Students>::iterator it = table[idx]->v.begin(); it != table[idx]->v.end(); it++) {
					if ((int)pow(2, (prefix[idx] - 1)) & it->getID())
						newblock2.insert(*it);
					else
						newblock1.insert(*it);
				}
				temp[2 * idx] = &newblock1;
				temp[2 * idx + 1] = &newblock2;
	
				delete table;
				table = temp;
				delete prefix;
				prefix = temp2;
			}
			hat_size *= 2;
			hat_cnt++;
		}
		else { //  ppt 위에 2개 꽉찰때
			for (int i = 0; i < hat_size; i++) {
				if (table[i]->v.capacity() == 128) {
					idx = i;
					break;
				}
			}
			int diff = hat_cnt - prefix[idx]; // ppt 위에가 2개가 아닐 경우를 위해
			for (int i = 0; i < diff; i++) {
				prefix[idx+i]++;
			}
			Block newblock1, newblock2;
			for (vector<Students>::iterator it = table[idx]->v.begin(); it != table[idx]->v.end(); it++) {
				if ((int)pow(2, (prefix[idx] - 1)) & it->getID())
					newblock2.insert(*it);
				else
					newblock1.insert(*it);
			}
			delete table[idx];
			for(int i=0; i< (int)pow(2,diff)/2;i++ )
				table[idx+i] = &newblock1;
			for (int i = (int)pow(2,diff)-1; i>= (int)pow(2, diff) / 2; i--)
				table[idx + i] = &newblock2;	
		}
	}
};

class DynamicHash {
private:
	Block b;
	HashAddressTable hat;
public:
	DynamicHash(Block &b, HashAddressTable &hat) {
		this->b = b;
		this->hat = hat;

		hat.table = new Block*[1];
		hat.table[0] = &b;
		hat.prefix = new int[1];
		hat.prefix[0] = 0;
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
	
	HashAddressTable hat;
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


		

	
		
	}
	
	//Students stuarr[4000];
	//ifstream inf("Students.DB", ios_base::in | ios_base::binary);
	//int count = 0;

	
	//while (inf.read((char*)&stuarr, 128000)) 
	int *a;
	a = new int[3];
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	cout << a[0] << endl;
	int *t = new int[6];
	t[0] = 2;
	delete a;
	a = t;
	cout << sizeof(a);
	
	fout.close();
	//stu.printInfo();
	return 0;
}