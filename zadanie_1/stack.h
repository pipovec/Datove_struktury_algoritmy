#ifndef STACK_H
#define STACK_H

struct NodeType;
typedef NodeType* NodePtr;


struct NodeType
{
	int       data;
	NodePtr   next;
};

class IntStack
{
    public:

        bool IsEmpty() const;
        //bool IsFull() const;
        void Push(int n);
        void Pop();
        int Top() const;
        ~IntStack();
        IntStack(const IntStack& otherStk);
        IntStack();


    private:

    	NodeType * top;
};

#endif // STACK_H
