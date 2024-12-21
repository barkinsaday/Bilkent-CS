//@author: Barkýn Saday
//@Student ID: 21902967
//CS201 Homework 1

#ifndef CABINET_H
#define CABINET_H
class Cabinet
{

public:
    Cabinet();
    Cabinet(int id, int rows, int columns);
    ~Cabinet();

    void printCabinet();
    void addChem(int row, int col, bool chem_type, int chem_id);
    void removeChem(int chem_id);
    bool findChem(int chem_id, int& returnRow, int& returnCol); //printlerken cabinet id de bak (ne demek istedim???)
    int getCabinetID();
    int getCabinetRows();
    int getCabinetColumns();
    int getCabinetEmptySlots();
    Cabinet& operator= ( const Cabinet&);


private:

    int m_id;
    int m_numRow;
    int m_numCol;
    bool** m_chemicals;
    bool** m_states;
    int** m_chem_ids;

};


#endif // CABINET_H_INCLUDED
