//@author: Barkın Saday
//@Student ID: 21902967
//CS201 Homework 1

#include "Cabinet.h"
#include <iostream>
using namespace std;

Cabinet::Cabinet()
{
    m_id = 0;
    m_numCol = 0;
    m_numRow = 0;

    m_chemicals = NULL;
    m_states = NULL;
    m_chem_ids = NULL;
}//End of default consturctor


Cabinet::Cabinet(int id, int rows, int columns)
{
    m_id = id;
    m_numCol = columns;
    m_numRow = rows;

    //Initialize all arrays to 0
    m_chemicals = new bool* [rows];
    m_states = new bool* [rows];
    m_chem_ids = new int* [rows];

    for(int i=0; i<rows; i++)
    {
        m_chemicals[i] = new bool [columns];
        m_states[i] = new bool[columns];
        m_chem_ids[i] = new int[columns];
    }

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            m_chemicals[i][j] = 0;
            m_states[i][j] = 0;
            m_chem_ids[i][j] = 0;
        }
    }
}//End of Cabinet constructor

Cabinet::~Cabinet()//is this right?
{
    for(int i=0; i<m_numRow; i++)
    {

        delete[] m_states[i];
        delete[] m_chemicals[i];
        delete[] m_chem_ids[i];
    }
    delete[] m_states;
    delete[] m_chem_ids;
    delete[] m_chemicals;
}

void Cabinet::printCabinet()
{
    cout << "   "; //sað üstü boþ býrak
    for(int i=1; i<=m_numCol; i++)
        cout << i << " ";
    cout << endl; // üsteki sayýlarý printle

    for(int i=0; i<m_numRow; i++)
    {
        switch(i+1)
        {
        case 1:
            cout << "A| ";
            break;
        case 2:
            cout << "B| ";
            break;
        case 3:
            cout << "C| ";
            break;
        case 4:
            cout << "D| ";
            break;
        case 5:
            cout << "E| ";
            break;
        case 6:
            cout << "F| ";
            break;
        case 7:
            cout << "G| ";
            break;
        case 8:
            cout << "H| ";
            break;
        case 9:
            cout << "I| ";
            break;
        }

        for( int j=0; j<m_numCol; j++)
        {
            if(m_states[i][j])
            {
                if(m_chemicals[i][j])
                    cout << "c ";
                else
                    cout << "r ";
            }

            else
                cout << "+ ";
        }
      cout << endl;
    }
} //end of printCabinet()

void Cabinet::addChem(int row, int col, bool chem_type, int chem_id)
{
    //Cheking ID is done in "LabOrganizer" class
    //we check whether the neighbors exist or not
    bool upperRow, underRow, leftCol, rightCol;
    upperRow = row-1 >= 0;
    underRow = row+1 < m_numRow;
    leftCol = col-1 >= 0;
    rightCol = col+1 < m_numCol;

    if( m_states[row][col] )
    {
        cout << "This place is occupied" << endl;

        return;
    }

    else //if the place is empty
    {
        if( !(chem_type) ) //if the type we add is R there is no problem as long as that space is empty
        {
            m_states[row][col] = 1;//state is filled
            m_chemicals[row][col] = chem_type; //type: R(0) in this case
            m_chem_ids[row][col] = chem_id; // add the id to list

            cout << "Retardant chemical with ID: " << chem_id << " has been placed at location ";
            switch(row+1) //+1 because row and col are indexes of the array
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
                cout << col+1 << " in cabinet " << m_id << endl;
                return;
        }
        else // if the type is Combustible we should check around for other combustibles before adding
        {
            if(upperRow)//check up
            {
                if(m_chemicals[row-1][col] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(underRow)//check down
            {
                if(m_chemicals[row+1][col] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(rightCol)//check right
            {
                if(m_chemicals[row][col+1] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(leftCol)//check left
            {
                if(m_chemicals[row][col-1] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(upperRow && rightCol)//check up-right
            {
                if(m_chemicals[row-1][col+1] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(upperRow && leftCol)//check up-left
            {
                if(m_chemicals[row-1][col-1] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(underRow && rightCol)//check down-right
            {
                if(m_chemicals[row+1][col+1] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            if(underRow && leftCol)//check down-left
            {
                if(m_chemicals[row+1][col-1] == 1)
                {
                    cout << "Combustible chemicals can not be near each other, the chemical is not added." << endl;
                    return;
                }
            }

            //if near columns are available
            m_states[row][col] = 1;//state is filled
            m_chemicals[row][col] = chem_type; //type: is given
            m_chem_ids[row][col] = chem_id; // add the id to list

            cout << "Combustive chemical with ID: " << chem_id << " has been placed at location ";
            switch(row+1) //+1 because row and col are indexes of the array
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
                cout << col+1 << " in cabinet " << m_id << endl;
        }
    }//end of else: empty situation
}//end of "addChem()" method

bool Cabinet::findChem(int id, int& rowOfChem, int& colOfChem) // 3 returns if it is found, row = -1 col = -1 if not found
{
    for(int i=0; i<m_numRow; i++)
    {
        for(int j=0; j< m_numCol; j++)
        {
            if(m_chem_ids[i][j] == id)
            {
                rowOfChem = i;
                colOfChem = j;
                return true;
            }
        }
    }
    rowOfChem = -1;
    colOfChem = -1;
    return false;
}

void Cabinet::removeChem(int id) //LabOrganizer: find the correct cabinet than use this method (correct.removeChem()) (first need to find correct cabinet)
{
    for(int i=0; i<m_numRow; i++)
    {
        for(int j=0; j<m_numCol; j++)
        {
            if(m_chem_ids[i][j]==id)
            {
               //delete here ??
                m_states[i][j] = 0;
                m_chem_ids[i][j] = 0;
                m_chemicals[i][j] = 0; //type is set to R so that we do not have a problem while checking for Combustible availablety
                cout << "Chemical " << id << " is removed from cabinet " << m_id << endl;
                return;
            }
        }
    }
    cout << "Chemical " << id << " is not in the system so it is not removed" << endl;
}

int Cabinet::getCabinetID()
{
    return m_id;
}

int Cabinet::getCabinetRows()
{
    return m_numRow;
}

int Cabinet::getCabinetColumns()
{
    return m_numCol;
}

int Cabinet::getCabinetEmptySlots()
{
    int counter = 0;
    for(int i=0; i<m_numRow; i++)
    {
        for( int j=0; j<m_numCol; j++)
        {
            if( !(m_states[i][j]) )
                counter++;
        }
    }
    return counter;
}

Cabinet& Cabinet::operator=(const Cabinet& right)
{
    if(&right != this)
    {
        m_numCol = right.m_numCol;
        m_numRow = right.m_numRow;
        m_id = right.m_id;

        if(m_numRow>0)
        {
            m_chemicals = new bool* [m_numRow];
            m_states = new bool* [m_numRow];
            m_chem_ids = new int* [m_numRow];

            for(int i=0; i<m_numRow; i++)
            {
                m_chemicals[i] = new bool [m_numCol];
                m_states[i] = new bool[m_numCol];
                m_chem_ids[i] = new int[m_numCol];
            }
        }

        for(int i=0; i<m_numRow; i++)
        {
            for(int j=0; j<m_numCol; j++)
            {
                m_chemicals[i][j] = right.m_chemicals[i][j];
                m_chem_ids[i][j] = right.m_chem_ids[i][j];
                m_states[i][j] = right.m_states[i][j];
            }
        }
    }
    return *this;
}













