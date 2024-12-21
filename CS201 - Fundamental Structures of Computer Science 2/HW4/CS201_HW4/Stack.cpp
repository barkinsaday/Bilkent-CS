/*
@author: Barkın_Saday
@date: 05.01.2022
@title: CS201_HW4
*/
#include "Stack.h"
Stack::Stack()
{
    topPtr = NULL;
}

Stack::Stack(const Stack& aStack)
{
    if(aStack.topPtr == NULL)
    {
        topPtr = NULL;
        return;
    }

    //Copy First Node
    topPtr = new StackNode;
    topPtr->item = aStack.topPtr->item;

    //Copy Rest
    StackNode *newPtr = topPtr;
    StackNode *origPtr = aStack.topPtr->next;

    while(origPtr != NULL)
    {
        newPtr->next = new StackNode;
        newPtr = newPtr->next;
        newPtr->item = origPtr->item;

        origPtr = origPtr->next;
    }

    newPtr->next = NULL;
}

Stack::~Stack()
{
    while(!isEmpty())
        pop();
}

bool Stack::isEmpty() const
{
    return topPtr == NULL;
}

bool Stack::pop()
{
    if(isEmpty())
        return 0;

    StackNode *temp = topPtr;
    topPtr = topPtr->next;
    temp->next = NULL;
    delete temp;
    temp = NULL;
    return 1;
}

bool Stack::pop(StackItemType& stackTop)
{
    if(isEmpty())
        return 0;
    stackTop = topPtr->item;//if item is an object might need to overload "=" operator for that object
    pop();
    return 1;
}

bool Stack::getTopR(StackItemType& stackTop) const
{
    if(isEmpty())
        return 0;
    stackTop = topPtr->item;//if item is an object might need to overload "=" operator for that object
}

bool Stack::push(StackItemType newItem)
{
    StackNode *newPtr = new StackNode;
    newPtr->item = newItem;
    newPtr->next = topPtr;
    topPtr = newPtr;
    return 1;
}

StackItemType Stack::getTop()
{
    if(topPtr == NULL)
        return NULL;
    return topPtr->item;
}
























