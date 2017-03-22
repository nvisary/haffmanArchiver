#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H
#include <iostream> 
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include "MyVector.h"

class Decompressor
{
private:
	FILE* fpin;
	FILE* fpout;
	FILE* fptable;

	int textLen;
	std::map<char, MyVector > table;
	std::map<char, MyVector>::iterator FindValue(const MyVector &a);
	void GetTable();
	void SaveToFile();
public:
	Decompressor(FILE* _in, FILE* _out);
	~Decompressor();
	void Decompress(FILE* _table);
};

#endif