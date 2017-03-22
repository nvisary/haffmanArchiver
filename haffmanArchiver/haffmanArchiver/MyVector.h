#ifndef MYVECTOR_H
#define MYVECTOR_H

class MyVector {
private:
	bool* array;
	int MySize;
	int cur;
	void ReSize();
public:
	MyVector();
	~MyVector();
	MyVector& operator= (const MyVector &a);
	bool operator==(const MyVector &a);
	void push_back(bool value);
	int size();
	void clear();
};


#endif