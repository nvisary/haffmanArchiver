#include "Decompressor.h"


Decompressor::Decompressor(FILE* _in, FILE* _out)
{
	fpin = _in;
	fpout = _out;
}

Decompressor::~Decompressor()
{

}

void Decompressor::Decompress(FILE* _table)
{
	fptable = _table;
	GetTable();
	SaveToFile();
}

std::map<char, MyVector>::iterator Decompressor::FindValue(const MyVector& a)
{
	for (auto i = table.begin(); i != table.end(); i++)
	{
		if (i->second == a) return i;
		else continue;
	}
	return table.end();
}

void Decompressor::SaveToFile()
{
	unsigned char byte = 0;
	int i = 0;
	MyVector tmp;
	byte = fgetc(fpin);
	int countOfCh = 0;

	while (!feof(fpin))
	{
		bool bit = byte & (1 << (7 - i));
		tmp.push_back(bit);
		auto rez = FindValue(tmp);

		if (rez != table.end())
		{
			fprintf(fpout, "%c", rez->first);
			countOfCh++;
			if (countOfCh == textLen) break;
			tmp.clear();
		}
		i++;

		if (i == 8)
		{
			i = 0;
			byte = fgetc(fpin);
		}
	}
}

void Decompressor::GetTable()
{
	char ch;
	int i;

	MyVector tmp;
	fscanf(fptable, "%d", &textLen);

	while (!feof(fptable))
	{
		fscanf(fptable, "%d", &i);
		fgetc(fptable);

		while (!feof(fptable))
		{
			fscanf(fptable, "%c", &ch);

			if (ch == '0')
				tmp.push_back(0);
			else if (ch == '1')
				tmp.push_back(1);
			else break;
		}

		if (tmp.size() == 0)
			break;

		table[i] = tmp;
		tmp.clear();
	}
}
