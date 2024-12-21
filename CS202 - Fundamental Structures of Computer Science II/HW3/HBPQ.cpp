/*
* Title: Heaps, Priority Queues
* Author: Barkin Saday
* ID: 21902967
* Section: 1
* Assignment: 3
* Description: (H)eap (B)ase (P)riority (Q)ueue cpp file
                - Array based implementation for a Max-Heap
                - Max-Heap based implementation for a Priority Queue
*/
#include "HBPQ.h"
    HBPQ::HBPQ()
    {
        m_size = 0;
        m_items = new Request*[1000]; //For testing purposes, in simulation only constructor with parameter is used
    }

    HBPQ::HBPQ(int size)
    {
        m_size = 0;
        m_items = new Request*[size];
    }

    HBPQ::~HBPQ()
    {
        for(int i=0; i<m_size; i++)
        {
            delete m_items[i];
        }
        delete[] m_items;
    }

    bool HBPQ::isEmpty()
    {
        if(!m_size)
        {
            return true;
        }
        return false;
    }

    void HBPQ::insertHBPQ(int id, int priority, int startTime, int processTime)
    {
        m_size++;
        Request* temp = new Request(id, priority, startTime, processTime);
        m_items[m_size-1] = temp;

        //maintain heap
        shiftUp(m_size-1);
    }

    void HBPQ::insertHBPQ(Request* newReq)
    {
        m_size++;
        m_items[m_size-1] = newReq;

        //maintain heap
        shiftUp(m_size-1);
    }

    void HBPQ::removeTop()//we always remove from top since top has the max priority (also "first sent" if priorities are same)
    {
        if(isEmpty())
            return;
        if(m_size == 1)
        {
            delete m_items[0];
            m_size--;
            return;
        }

        if(m_size == 2)
        {
            delete m_items[0];
            //maintain heap
            m_items[0] = m_items[1];
            m_size--;
            return;
        }

        //maintain heap
        int last;
        last = m_items[m_size-1]->getPriority();
        m_items[0]->setPriority(last);

        shiftDownTop();//move the top node to bottom

        //delete
        delete m_items[m_size-1];
        m_size--;
    }

    int HBPQ::getParent(int i)
    {
        return (i-1)/2;
    }

    int HBPQ::getLeft(int i)
    {
        return (2*i) + 1;
    }
    int HBPQ::getRight(int i)
    {
        return (2*i) +2;
    }

    void HBPQ::shiftUp(int i)
    {
        while( i>0 && (m_items[getParent(i)]->getPriority()) < (m_items[i])->getPriority() ) //(i-1)/2 cant exceed boundary since i>0 and i-1/2 < i
        {
            //Swap current node with its parent
            Request* temp;
            temp = m_items[i];
            m_items[i] = m_items[getParent(i)];
            m_items[getParent(i)] = temp;

            //Update i
            i = getParent(i);
        }
    }

    void HBPQ::shiftDown(int i)
    {
        int maxMem = i;

        int left = getLeft(i);

        //Check if left is larger than root
        if (left <= m_size && m_items[left]->getPriority() >= m_items[maxMem]->getPriority())
            maxMem = left;

        int right = getRight(i);

        //Check if right is larger than root/left (largest up to now)
        if (right <= m_size && m_items[right]->getPriority() >= m_items[maxMem]->getPriority())
            maxMem = right;

        //If largest is not root keep recursively maintaining the heap
        if (i != maxMem)
        {
            //Swap
            Request* temp = m_items[i];
            m_items[i] = m_items[maxMem];
            m_items[maxMem] = temp;
            shiftDown(maxMem);
        }
    }

    void HBPQ::shiftDownTop()
    {
        shiftDown(0);
    }


    void HBPQ::printHBPQ()
    {
        if(isEmpty())
        {
            cout << "Heap is empty." << endl;
            return;
        }

        for(int i=0; i<m_size; i++)
        {
            m_items[i]->printRequest();
        }
    }

    Request* HBPQ::top()
    {
        if(!isEmpty())
            return m_items[0];
        return NULL;
    }






