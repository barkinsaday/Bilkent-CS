/*
@Barkýn Saday
@21.12.2021
@CS201 HomeWork 3
@ID:21902967
@Section: 1
*/
#ifndef FLOWER_H_INCLUDED
#define FLOWER_H_INCLUDED
#include <iostream>
using namespace std;
class Flower{
public:
    Flower();
    Flower(string flowerName);
    Flower(const Flower& aFlower);
    ~Flower();
    bool isEmpty() const;
    int getLength() const;
    bool add(string feature);
    bool remove(string feature);
    string printFlower() const;
    string getFlowerName();//added
    void setName(string name);//added
    bool containsFeature(string feature);//added
    string toLowerCase(string word);


private:
    struct FeatureNode{
        string feature;
        FeatureNode* next;
    };
    int size;
    string flowerName;
    FeatureNode *head; //the features are stored in a sorted singly linear linked list
    // ...
    //you may define additional member functions and data members, if necessary

};
#endif // FLOWER_H_INCLUDED
