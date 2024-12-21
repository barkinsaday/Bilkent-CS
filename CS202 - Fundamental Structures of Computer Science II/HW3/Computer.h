/*
* Title: Heaps, Priority Queues
* Author: Barkin Saday
* ID: 21902967
* Section: 1
* Assignment: 3
* Description: Computer Class Header File
*/

#ifndef COMPUTER_H_INCLUDED
#define COMPUTER_H_INCLUDED

#include <iostream>
using namespace std;

class Computer
{
private:
    //Data Members
    int id;
    int time;
    bool available;

public:
    Computer();
    Computer(int id, int time, bool available);

    void setId(const int& id);
    void setTime(const int& time);
    void setAvailable(const int& available);

    int getId() const;
    int getTime() const;
    bool isAvailable() const;
    void printComputer() const;
};

#endif // COMPUTER_H_INCLUDED
