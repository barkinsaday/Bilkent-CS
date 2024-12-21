/*
@Barkýn Saday
@21.12.2021
@CS201 HomeWork 3
@ID:21902967
@Section: 1
*/
#ifndef FLOWERLIBRARY_H_INCLUDED
#define FLOWERLIBRARY_H_INCLUDED
#include "FlowerList.h"
#include <iostream>
using namespace std;
class FlowerLibrary{
public:
    FlowerLibrary();
    ~FlowerLibrary();
    void addFlower(string name);
    void removeFlower(string name);
    void listFlowers() const;
    void listFeatures(string name) const;
    void addFeature(string name, string feature);
    void removeFeature(string name, string feature);
    void findFlowers(string feature) const;
private:
    FlowerList flowers;
    // ...
    //you may define additional member functions and data members, if necessary
    string toLowerCase(string word);//added
};


#endif // FLOWERLIBRARY_H_INCLUDED
