#ifndef STACK_H
#define STACK_H


struct NodeType;
typedef NodeType *NodePtr;

struct NodeType
{
	int       pocet;
	float     ck;
	NodePtr   next;
};

typedef NodeType *NodePtr;
class Queue
{
    public:
        /** Default constructor */
        Queue();

        bool   IsEmpty() const;
        bool   IsFull() const;
        void   Enqueue(int pocet, float ck);
        void   Dequeue();
        void   ListQueue();
        int    CountPocet();
        int    FrontPocet() const;
        float  FrontCK() const;
        void   Odpocitaj(int pocet); // Odpocita z vrchneho nodu pocet poloziek

    private:
        NodeType *front,*rear;
};

#endif // STACK_H
