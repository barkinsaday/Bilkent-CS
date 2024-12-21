/*
@author: Barkýn_Saday
@date: 05.01.2022
@title: CS201_HW4
*/
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <iostream>
using namespace std;

typedef char StackItemType;

class Stack
{
public:
    Stack();
    Stack(const Stack& aStack);
    ~Stack();
    bool isEmpty() const;
    bool pop();
    bool pop(StackItemType& stackTop);
    bool push(StackItemType newItem);
    bool getTopR(StackItemType& stackTop) const;
    StackItemType getTop();

private:
    struct StackNode
    {
        StackItemType item;
        StackNode *next;
    };
    StackNode *topPtr;
};


#endif // STACK_H_INCLUDED
