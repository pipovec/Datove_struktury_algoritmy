#include "stack.h"
#include "stddef.h"

IntStack::IntStack()
{
	top = NULL;
}

bool IntStack::IsEmpty() const
{
	return (top == NULL);
}

void IntStack::Push(int newItem)
{
	NodePtr newPtr = new NodeType;
	newPtr->data = newItem;
	newPtr->next = top;
	top = newPtr;
}

// Vrati hodnotu vechneho prvku
int IntStack::Top() const
{
    //std::cout << top->data << top->next;
    return top->data;
}

// Odobratie vrachneho prvku
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
