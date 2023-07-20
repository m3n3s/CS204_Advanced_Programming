#include <iostream>
#include "mehmetenes_battal_mehmetenes_hw5_IntegerSet.h"

// MEHMET ENES BATTAL - HW5

using namespace std;

IntegerSet::IntegerSet()
{
	size = 0;
	setPtr = NULL;
}

IntegerSet::IntegerSet(int s)
{
	

	if(s <= 0)
	{
		size = 0;
		setPtr = NULL;
	}

	else
	{
		size = s;
		setPtr = new int[size];

		for(int i = 0; i < size; i++)
		{
			setPtr[i] = i;
		}
	}
}

IntegerSet::IntegerSet(const IntegerSet & set)
{
	size = set.size;
	setPtr = new int[size];

	for(int i = 0; i < size; i++)
	{
		setPtr[i] = set.setPtr[i];
	}
}

IntegerSet::~IntegerSet()
{
	size = 0;
	delete []setPtr;
	setPtr = NULL;
}

ostream & operator <<(ostream &output, const IntegerSet &set)
{
	int* head = set.getPtr();

	output << "{";
	for(int i = 0; i < set.getSize(); i++)
	{
		output << head[i];
		if(i != set.getSize()-1)
			output << ", ";
	}
	output << "}" ;

	return output;
}

IntegerSet IntegerSet::operator+(int rhs) 
{
	if(!inSet(rhs))
	{
		IntegerSet result;

		result.size = size + 1;
		result.setPtr = new int[result.size];

		for(int i = 0; i<size; i++)
		{
			result.setPtr[i] = setPtr[i];
		}

		result.setPtr[result.size - 1] = rhs;

		return result;
	}
	return *this;
}

IntegerSet IntegerSet::operator+(const IntegerSet &rhs)const
{
	IntegerSet result(*this);

	for(int i = 0; i < rhs.size; i++)
	{
		if(!inSet(rhs.setPtr[i]))
		{
			result = result + rhs.setPtr[i];
		}
	}
	return result;
}

IntegerSet IntegerSet::operator*(IntegerSet rhs)const
{
	IntegerSet result;
	for(int i = 0; i < rhs.getSize(); i++)
	{
		if(inSet(rhs.setPtr[i]))
			result = result + rhs.setPtr[i];
	}
	return result;
}

const IntegerSet & IntegerSet::operator=(const IntegerSet & rhs)
{
	if(this != &rhs)
	{
		delete []setPtr;

		size = rhs.size;
		setPtr = new int[size];

		for(int i = 0; i < size; i++)
		{
			setPtr[i] = rhs.setPtr[i];
		}
				
	}
	return *this;
}

const IntegerSet & IntegerSet::operator+=(const IntegerSet & rhs)
{
	if(this != &rhs)
	{
		for(int i = 0; i < rhs.size ; i++)
		{
			if(!inSet(rhs.setPtr[i]))
				*this = *this + rhs.setPtr[i];
		}
	}

	return *this;
}

bool operator!=(IntegerSet lhs, IntegerSet rhs)
{
	if(lhs.getSize() == rhs.getSize())
	{
		for(int i = 0; i < lhs.getSize(); i++)
		{
			if(!lhs.inSet(rhs.getPtr()[i]))
				return true;
		}
		return false;
	}

	else
		return true;
}

bool IntegerSet::operator<=(IntegerSet rhs)const
{
	for(int i = 0; i < size; i++)
	{
		if(!rhs.inSet(setPtr[i]))
			return false;
	}
	return true;
}

bool operator<=(int lhs, IntegerSet rhs)
{
	int* head = rhs.getPtr();
	for(int i = 0; i < rhs.getSize(); i++)
	{
		if(lhs == head[i])
			return true;
	}
	return false;
}

int IntegerSet::getSize() const
{
	return size;
}

int* IntegerSet::getPtr() const
{
	return setPtr;
}

bool IntegerSet::inSet(int n) const
{
	for(int i = 0; i < size; i++)
	{
		if(setPtr[i] == n)
			return true;
	}
	return false;
}