#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <iostream>
#include <cstdio>
#include <map>
#include <list>
#include <vector>
/**
* Need to compressing files
*/
class Compressor{
private:
	class Node
	{
	public:
		char ch;
		int weight;
		Node *right, *left;
		bool is_good;
		Node()
		{
			right = NULL;
			left = NULL;
			is_good = false;
		}
	};

	FILE* fpin;
	FILE* fpout;
	FILE* fptable;

	std::list <Node*> tree;
	std::map<int, int> map_weights;
	std::vector<bool> code;
	std::map<char, std::vector<bool> > table;
	std::vector<int> text;

	void GetWeights();
	void CreateTable(Node* head);
	void CreateTree();
	void SaveToFile();
	void SaveTableToFile();

	struct comp
	{
		bool operator()(Node* a, Node* b) const
		{
			return a->weight < b->weight;
		}
	};
public:
	Compressor(FILE* _in, FILE* _out);
	~Compressor();
	void Compress(FILE* _table);
};


#endif 