#include <iostream>
#include "DynStack.h"
using namespace std;

/* Begin: code taken from DynIntStack.cpp and updated */ 

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynStack::DynStack()
{
	top = NULL;
}

//************************************************
// Destructor
//************************************************
DynStack::~DynStack()
{
	StackNode* nodePtr;

   // Position nodePtr at the top of the stack.
   nodePtr = top;

   // Traverse the list deleting each node.
   while (nodePtr != NULL)
   {
	  StackNode* temp;
	  temp = nodePtr;
      nodePtr = nodePtr->next;
      delete temp;
      
   }
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynStack::push(int x, int y)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->rowNum = x;
	newNode->colNum = y;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynStack::pop(int &numX, int &numY)
{
	StackNode *temp;

	if (isEmpty()); 
	
	else // pop value off top of stack
	{
		numX = top->rowNum;
		numY = top->colNum;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

/* End: code taken from DynIntStack.cpp and updated */ 