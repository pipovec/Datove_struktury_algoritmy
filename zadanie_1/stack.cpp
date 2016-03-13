#include "stack.h"
#include "stddef.h"
//#include <alloc.h>


IntStack::IntStack()
{
	top = NULL;
}

bool IntStack::IsEmpty() const
{
	return (top == NULL);
}

/*bool IntStack::IsFull() const 
{
  return (coreleft () < sizeof(NodeType));
}
*/
void IntStack::Push(int newItem)
{
	NodePtr newPtr = new NodeType;
	newPtr->data = newItem;
	newPtr->next = top;
	top = newPtr;
}

int IntStack::Top() const
{
	return top->data;
}

void IntStack::Pop()
{
	NodeType* tempPtr = top;
	top = top->next;
	delete tempPtr;
}

IntStack::~IntStack()
{
	// Destructor

	NodeType * tempPtr;
	while(top != NULL)
	{
		tempPtr = top;
		top = top->next;
		delete tempPtr;
	}
}
