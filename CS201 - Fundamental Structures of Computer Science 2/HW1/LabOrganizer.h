//@author: Barkýn Saday
//@Student ID: 21902967
//CS201 Homework 1

#ifndef LABORGANIZER_H
#define LABORGANIZER_H
#include "Cabinet.h"
#include <string>
#include <iostream>
using namespace std;


class LabOrganizer{
public:
LabOrganizer();
~LabOrganizer();

void addCabinet(int id, int rows, int columns);
void removeCabinet(int id);
void listCabinets();
void cabinetContents(int id);
void placeChemical(int cabinetId, string location, string chemType, int chemID);
void findChemical(int id);
void removeChemical(int id);
// ...
//you may define additional member functions and data members, if necessary
private:
    Cabinet* m_cabinetList;
    int m_numOfCabinets;
};



#endif // LABORGANIZER_H_INCLUDED



