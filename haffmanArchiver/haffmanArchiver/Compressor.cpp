#include "Compressor.h"
/**
* Constructor
* @param _in pointer to in file (file for compressing)
* @param _out pointer to out file (compressing file)
*/
Compressor::Compressor(FILE* _in, FILE* _out)
{
	fpin = _in;
	fpout = _out;
}

Compressor::~Compressor()
{

}

/**
* Gets symbols and calculates weights
*/
void Compressor::GetWeights()
{
	unsigned char ch = 0;

	while (!feof(fpin))
	{
		ch = getc(fpin);
		if (feof(fpin))
			break;

		text.push_back(ch);
		map_weights[ch]++;
	}

	if (map_weights.empty() == true)
		std::cout << "File is empty!";
}
/**
* Ñreates a Huffman tree
*/
void Compressor::CreateTree()
{
	GetWeights(); //O(n)

	for (auto it = map_weights.begin(); it != map_weights.end(); ++it)  //O(n)
	{
		Node* tmp = new Node;

		tmp->ch = it->first;
		tmp->weight = it->second;
		tmp->is_good = true;
		tree.push_back(tmp);
	}

	while (tree.size() != 1)
	{
		tree.sort(comp());

		Node* NL = tree.front();
		tree.pop_front();

		Node* NR = tree.front();
		tree.pop_front();

		Node* parent = new Node;

		parent->weight = NL->weight + NR->weight;
		parent->left = NL;
		parent->right = NR;
		parent->ch = 0;

		tree.push_back(parent);
	}
}
/**
* Save table of weights to file
*/
void Compressor::SaveTableToFile()
{
	fprintf(fptable, "%d \n", text.size());

	for (auto i = table.begin(); i != table.end(); i++)
	{
		fprintf(fptable, "%d ", i->first);
		for (int j = 0; j < (i->second).size(); j++)
		{
			if ((i->second)[j] == true)
			{
				fprintf(fptable, "1");
			}
			else
			{
				fprintf(fptable, "0");
			}
		}
		fprintf(fptable, "\n");
	}
}
void Compressor::Compress(FILE* _table)
{
	CreateTree();

	Node* head = tree.front();

	if (text.size() == 1)
	{
		code.push_back(0);
		code.push_back(1);
		table[text[0]] = code;
	}
	else
	{
		CreateTable(head);
	}
	fptable = _table;
	SaveTableToFile();
	SaveToFile();

}

void Compressor::CreateTable(Node* head)
{
	if (head->left != NULL)
	{
		code.push_back(0);
		CreateTable(head->left);
	}

	if (head->right != NULL)
	{
		code.push_back(1);
		CreateTable(head->right);
	}
	if (head->is_good == true)   //head->ch
		table[head->ch] = code;


	if (code.size() == 0)
		return;

	code.pop_back();
}

void Compressor::SaveToFile()
{
	int count = 0;
	char byte = 0;

	for (int i = 0; i < text.size(); i++)
	{
		code = table[text[i]];

		for (int n = 0; n < code.size(); n++)
		{
			byte = byte | code[n] << (7 - count);
			count++;

			if (count == 8)
			{
				count = 0;
				fputc(byte, fpout);
				byte = 0;
			}
		}

	}

	if (count != 0)
	{
		fputc(byte, fpout);
	}
	fclose(fpout);
}