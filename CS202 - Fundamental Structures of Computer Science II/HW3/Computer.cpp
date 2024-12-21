/*
* Title: Heaps, Priority Queues
* Author: Barkin Saday
* ID: 21902967
* Section: 1
* Assignment: 3
* Description: Computer Class cpp file
*/
#include "Computer.h"

Computer::Computer()
{
    this->id = 0;
    this->time = 0;
    this->available = true;
}

Computer::Computer(int id, int time, bool available)
{
    this->id = id;
    this->time = time;
    this->available = available;
}

    void Computer::setId(const int& id)
    {
        this->id = id;
    }

    void Computer::setTime(const int& time)
    {
        this->time = time;
    }

    void Computer::setAvailable(const int& available)
    {
        this->available = available;
    }

    int Computer::getId() const
    {
        return id;
    }

    int Computer::getTime() const
    {
        return time;
    }

    bool Computer::isAvailable() const
    {
        return available;
    }

    void Computer::printComputer() const
    {
        cout << "ID: " << id << ", Time: " << time << ", Available Status: " << available << endl;
    }










