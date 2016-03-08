#ifndef STACK_H
#define STACK_H


class Stack
{
    public:
        Stack();
        bool IsEmpty() const;
        bool IsFull() const;
        void Push(int n);
        void Pop();
        int Top() const;
        ~Stack();
        
    protected:
    private:
    	NodeType * top;
};

#endif // STACK_H
