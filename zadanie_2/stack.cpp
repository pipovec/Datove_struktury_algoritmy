#include "stack.h"
#include <iostream>
#include <stddef.h>

using namespace std;


Queue::Queue()
{
    front = rear = NULL;
}

bool Queue::IsEmpty() const
{
  return (front == NULL);
}

void Queue::Dequeue()
{
    NodeType *tmpPtr = front;
    front  = front->next;
    delete tmpPtr;
}

void Queue::Enqueue( int  pocet, float ck)
{
    NodePtr newPtr = new NodeType;
    newPtr->pocet = pocet;
    newPtr->ck    = ck;
    newPtr->next  = NULL;

    if(front == NULL)
    {
        front = rear = newPtr;
    }
    else
    {
        rear->next = newPtr;
        rear = newPtr;
    }

}

int Queue::FrontPocet() const
{
    return front->pocet;
}

float Queue::FrontCK() const
{
    return front->ck;
}

void Queue::ListQueue()
{
    NodeType *tmp = front;

    if(front == NULL)
    {
        cout << "Nie je na sklade" << endl;
    }
    else
    {

        int i = 1;
        do
        {
            if(tmp->next == NULL){ i = 2;}

            cout << "Pocet kusov: " << tmp->pocet << " ks " << " cena za kus " << tmp->ck << endl;
            tmp = tmp->next;



        }
        while(i == 1);

    }

}

int Queue::CountPocet()
{
    int pocet = 0;
    NodeType *tmp = front;

    int i = 1;
    do
    {
        if(tmp->next == NULL){ i = 2;}
        pocet  += tmp->pocet;
        tmp = tmp->next;


    }
    while(i == 1);


    return pocet;

}

void Queue::Odpocitaj(int pocet)
{
    front->pocet -=  pocet;
}






