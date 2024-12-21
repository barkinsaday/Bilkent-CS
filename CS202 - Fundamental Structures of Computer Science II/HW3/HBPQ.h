/*
* Title: Heaps, Priority Queues
* Author: Barkin Saday
* ID: 21902967
* Section: 1
* Assignment: 3
* Description: (H)eap (B)ase (P)riority (Q)ueue header file
                - Array based implementation for a Max-Heap
                - Max-Heap based implementation for a Priority Queue
*/
#ifndef HBPQ_H_INCLUDED
#define HBPQ_H_INCLUDED
#include "Request.h"
class HBPQ
{
public:
    HBPQ();
    HBPQ(int size);
    ~HBPQ();
    bool isEmpty();
    void insertHBPQ(int id, int priority, int startTime, int processTime);
    void insertHBPQ(Request* newReq);
    void removeTop();
    int getParent(int i);//returns the index of the parent for the i'th node
    int getLeft(int i);//returns the index of the left for the i'th node
    int getRight(int i);//returns the index of the right for the i'th node
    void shiftUp(int i);//Used for rebuilding the heap after insertion
    void shiftDownTop();//Used for rebuilding the heap after removing
    void shiftDown(int i);
    void printHBPQ();
    Request* top();

private:
    Request** m_items; //dynamic array of Request items
    int m_size;
};





#endif // HBPQ_H_INCLUDED
