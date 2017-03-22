#include "MyVector.h"
#include <stdlib.h>
#include <stdio.h>

MyVector::MyVector()
{
	cur = 100;
	array = (bool*)malloc(cur * sizeof(bool));
	MySize = 0;
}

MyVector::~MyVector()
{
	free(array);
}

void MyVector::push_back(bool value)
{
	if (MySize == cur || array == NULL)
		ReSize();

	array[MySize] = value;
	MySize++;
}

MyVector& MyVector::operator=(const MyVector &a)
{
	MySize = a.MySize;

	for (int i = 0; i < MySize; i++)
	{
		array[i] = a.array[i];
	}

	return *this;
}

bool MyVector::operator==(const MyVector &a)
{
	if (MySize == a.MySize)
	{
		for (int i = 0; i < MySize; i++)
		{
			if (array[i] == a.array[i]) continue;
			else return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}
void MyVector::ReSize()
{

	if (array == NULL)
	{
		array = (bool*)malloc(sizeof(bool) * cur);
	}
	else
	{
		cur *= 2;
		array = (bool*)realloc(array, sizeof(bool)* cur);
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