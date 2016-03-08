#include "stack.h"


bool Stack::IsEmpty() const
{
	return (top == -1);
}

bool Stack::IsFull() const 
{
  return (top == max_depth-1);
}



