#include "myvector.h"
#include <stdlib.h>
#include <stdio.h>

MyVector::MyVector()
{
	tec = 100;
	massiv = (bool*)malloc(tec * sizeof(bool));
	MySize = 0;
}

MyVector::~MyVector()
{
	free(massiv);
}

void MyVector::push_back(bool value)
{
	if (MySize == tec || massiv == NULL)
		ReSize();

	massiv[MySize] = value;
	MySize++;
}

MyVector& MyVector::operator=(const MyVector &a)
{
	MySize = a.MySize;

	for (int i = 0; i < MySize; i++)
	{
		massiv[i] = a.massiv[i];
	}

	return *this;
}

bool MyVector::operator==(const MyVector &a)
{
	if (MySize == a.MySize)
	{
		for (int i = 0; i < MySize; i++)
		{
			if (massiv[i] == a.massiv[i]) continue;
			else return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}
void MyVector::print()
{
	for (int i = 0; i < MySize; i++)
	{
		printf("%d", massiv[i]);
	}

}
void MyVector::ReSize()
{

	if (massiv == NULL)
	{
		massiv = (bool*)malloc(sizeof(bool)*tec);
	}
	else
	{
		tec *= 2;
		massiv = (bool*)realloc(massiv, sizeof(bool)* tec);
	}
}

int MyVector::size()
{
	return MySize;
}

void MyVector::clear()
{
	MySize = 0;
}