/*
@Barkýn Saday
@21.12.2021
@CS201 HomeWork 3
@ID:21902967
@Section: 1
*/
#ifndef FLOWERLIST_H_INCLUDED
#define FLOWERLIST_H_INCLUDED
#include "Flower.h"
#include <iostream>
using namespace std;
class FlowerList{
public:
    FlowerList();
    FlowerList(const FlowerList& aList);
    ~FlowerList();
    bool isEmpty() const;
    int getLength() const;
    bool retrieve(string flowerName, Flower& flower) const;
    bool add(string flowerName);
    bool remove(string flowerName);
    void printFlowers();
    void printOneFlower(string flowerName) const;//added
    void printFlowersC() const;//added
    bool addFeature(string name, string feature);//added
    bool removeFeature(string name, string feature);//added
    bool containsFlower(string name);//added
    void findFlower(string feature) const;//added
    string toLowerCase(string word);//added


private:
    struct FlowerNode{
        Flower f;
        FlowerNode* next;
    };
    int size;
    FlowerNode* head; //the flowers are stored in a sorted singly linear linked list
    // ...
    //you may define additional member functions and data members, if necessary
};



#endif // FLOWERLIST_H_INCLUDED
