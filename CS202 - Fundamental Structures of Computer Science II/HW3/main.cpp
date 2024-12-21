/*
* Title: Heaps, Priority Queues
* Author: Barkin Saday
* ID: 21902967
* Section: 1
* Assignment: 3
* Description: main file for testing the classes
*/

#include <iostream>
using namespace std;
#include "Computer.h"
#include "Request.h"
#include "HBPQ.h"
#include <cstdlib> // DELETE AFTER TEST


int main()
{
    int reqNum;
    cout << "Enter number of requests: ";
    cin >> reqNum;
    cout << endl;

    HBPQ* q = new HBPQ(reqNum);

    for(int i=1; i<=reqNum; i++)
    {
        int id = rand() % 100 +1;
        int prio = rand() % 100 +1;
        int startT = rand() % 100 +1;
        int processT = rand() % 100 +1;
        q->insertHBPQ(id, prio, startT, processT);
        cout << "Item inserted, priority: " << prio << endl;
    }

    cout << "Printing..." << endl;
    q->printHBPQ();
    cout << "End of print..." << endl;

    //TEST REMOVE
    for(int i=0; i<5; i++)
    {
        q->removeTop();
    }

    cout << "Print After Remove..." << endl;
    q->printHBPQ();
    cout << "End of TEST" << endl;
    return 0;
}
