//@author: Barkýn Saday
//@Student ID: 21902967
//CS201 Homework 1

#include "LabOrganizer.h"
#include "Cabinet.h"
#include <iostream>
using namespace std;

LabOrganizer::LabOrganizer()//what should we do in constructor?
{
    m_cabinetList = NULL;
    m_numOfCabinets = 0;
}

LabOrganizer::~LabOrganizer()
{
    if (m_cabinetList){
        delete[] m_cabinetList;
    }
}

void LabOrganizer::addCabinet(int id, int rows, int columns)
{
    for(int i=0; i<m_numOfCabinets; i++)
    {
        if(m_cabinetList[i].getCabinetID() == id )
        {
            cout << "Cannot add cabinet ID " << id << " already in the system" << endl;
            return;
        }
    }

    if( rows<1 || rows>9 ||columns<1 || columns>9)
    {
        cout << "Cannot add cabinet: dimension is out of bounds" << endl;
        return;
    }

    if(m_numOfCabinets == 0)
    {
        m_numOfCabinets++;
        m_cabinetList = new Cabinet[m_numOfCabinets];
        m_cabinetList[0] = Cabinet(id ,rows, columns);
        cout << "Added a cabinet with ID " << id << " and with dimensions " << rows << "x" << columns << endl;
        return;
    }//burda stackten silindi

    m_numOfCabinets++;
    Cabinet* temp = m_cabinetList;
    m_cabinetList = new Cabinet[m_numOfCabinets];

    for(int i=0; i<m_numOfCabinets-1; i++)//Copied list so far to another location
    {
      m_cabinetList[i] = temp[i];
    }

    m_cabinetList[m_numOfCabinets-1] = Cabinet(id ,rows, columns); //added new cabinet to the list
    delete[] temp;
    //temp = NULL; after we exit addCabinet() temp will get deleted
    cout << "Added a cabinet with ID " << id << " and with dimensions " << rows << "x" << columns << endl;
}

void LabOrganizer::removeCabinet(int id)
{
    bool idFound = false;
    int index;
    for(int i=0; i<m_numOfCabinets; i++)
    {
        if(m_cabinetList[i].getCabinetID() == id)
        {
            idFound = true;
            index = i;
        }
    }
    if(!idFound)
    {
        cout << "Cabinet is not removed, ID " << id << " does not exists." << endl;
        return;
    }
    //5ten 4e
    m_numOfCabinets--;// = 4
    Cabinet* temp = m_cabinetList;
    m_cabinetList = new Cabinet[m_numOfCabinets];

    for(int i=0; i<index; i++)
    {
        m_cabinetList[i] = temp[i];
    }

    for(int i=index; i<m_numOfCabinets; i++)
    {
        m_cabinetList[i] = temp[i+1];
    }

    cout << "Cabinet " << id << " has been removed from list." << endl;

    delete[] temp;
    //temp = NULL // will get deleted anyway
}

void LabOrganizer::listCabinets()
{
    cout << "List of all cabinets: " << endl;

    for(int i=0; i<m_numOfCabinets; i++)
    {
        cout << "ID: " << m_cabinetList[i].getCabinetID() << ", " << "Dim: " << m_cabinetList[i].getCabinetRows() << "x" <<
         m_cabinetList[i].getCabinetColumns() << ", Number of empty slots: " << m_cabinetList[i].getCabinetEmptySlots() << endl;
    }
}

void LabOrganizer::cabinetContents(int id)
{
    for(int i=0; i<m_numOfCabinets; i++)
    {
        if( m_cabinetList[i].getCabinetID() == id )
        {
            m_cabinetList[i].printCabinet();
            return;
        }
    }
    cout <<"Cabinet " << id << " is not in the system." << endl;
}

void LabOrganizer::findChemical( int chem_id)
{
    int rowOfChem = 0, colOfChem = 0;

    for(int i=0; i<m_numOfCabinets; i++)
    {
        if(m_cabinetList[i].findChem(chem_id, rowOfChem, colOfChem))
        {
            cout << "Chemical " << chem_id << " is at location ";
            switch(rowOfChem+1) //+1 because row and col are indexes of the array
                {
                    case 1:
                        cout << "A";
                        break;
                    case 2:
                        cout << "B";
                        break;
                    case 3:
                        cout << "C";
                        break;
                    case 4:
                        cout << "D";
                        break;
                    case 5:
                        cout << "E";
                        break;
                    case 6:
                        cout << "F";
                        break;
                    case 7:
                        cout << "G";
                        break;
                    case 8:
                        cout << "H";
                        break;
                    case 9:
                        cout << "I";
                        break;
                }
                cout << colOfChem+1 << " in cabinet " << m_cabinetList[i].getCabinetID() << endl;
                return;
        }
    }
    cout << "Chemical " << chem_id << " is not in the system." << endl;
}

void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int chem_id)
{
    int indexRow;
    int indexCol;
    bool typeOfChem;
    bool cabinetExists = false;
    int cabinetIndex = -1;

    for(int i=0; i<m_numOfCabinets; i++)
    {
        if(m_cabinetList[i].getCabinetID() == cabinetId)
        {
            cabinetExists = true;
            cabinetIndex = i;
        }

        if(m_cabinetList[i].findChem(chem_id, indexRow, indexCol))
        {
            cout << "Chemical with ID " << chem_id << " already exists in the system." << endl;
            return;
        }
    }

    if(!cabinetExists)
    {
        cout << "Cabinet with ID " << cabinetId << " does not exists in the system, chemical " << chem_id << " is not placed." << endl;
        return;
    }

    //string to integer indexes by ASCÝÝ Values
    indexRow = location[0]-65;
    indexCol = location[1]-49;

    // check type by first letter of string "chemType" (capitals included)
    if(chemType[0] == 'r' || chemType[0] == 'R')
        typeOfChem = false;
    if(chemType[0] == 'c' || chemType[0] == 'C')
        typeOfChem = true;

    // check if the cabinet we are using have the entered row/column numbers
    if(indexRow>m_cabinetList[cabinetIndex].getCabinetRows() || indexRow<0 || indexCol>m_cabinetList[cabinetIndex].getCabinetColumns() || indexCol<0)
    {
        cout << "Location is out of bounds for the cabinet " << cabinetId << ", chemical " << chem_id << " is not placed." << endl;
        return;
    }

    m_cabinetList[cabinetIndex].addChem(indexRow, indexCol, typeOfChem, chem_id);//try to add chemical
}

void LabOrganizer::removeChemical(int chem_id)
{
    int rowOfChem;
    int colOfChem;
    for(int i=0; i<m_numOfCabinets; i++)
    {
        if(m_cabinetList[i].findChem(chem_id, rowOfChem, colOfChem))
        {
            m_cabinetList[i].removeChem(chem_id);
            return;
        }
    }
    cout << "Chemical with ID " << chem_id << " is not in the system." << endl;
}














