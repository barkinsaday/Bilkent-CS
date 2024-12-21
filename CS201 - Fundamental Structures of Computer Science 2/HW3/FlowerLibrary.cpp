/*
@Barkýn Saday
@21.12.2021
@CS201 HomeWork 3
@ID:21902967
@Section: 1
*/
#include "FlowerLibrary.h"
#include <iostream>

FlowerLibrary::FlowerLibrary()
{

}

FlowerLibrary::~FlowerLibrary()
{

}

void FlowerLibrary::addFlower(string name)
{
    name = toLowerCase(name);
    if(flowers.add(name))
    {
        cout << name << " has been added into the library." << endl;
        return;
    }
    cout << name << " cannot be added into the library, it already exists" << endl;
}

void FlowerLibrary::removeFlower(string name)
{
    name = toLowerCase(name);
    if(flowers.remove(name))
    {
        cout << name << " has been removed from the library." << endl;
        return;
    }
    cout << name << " cannot be removed because it's not in the library" << endl;
}

void FlowerLibrary::listFlowers() const
{
   cout << "---List Of Flowers---" << endl;
   flowers.printFlowersC();
}

void FlowerLibrary::listFeatures(string name) const
{
    //name = toLowerCase(name);
    flowers.printOneFlower(name);
}

void FlowerLibrary::addFeature(string name, string feature)
{
    name = toLowerCase(name);
    feature = toLowerCase(feature);
    flowers.addFeature(name, feature);
}

void FlowerLibrary::removeFeature(string name, string feature)
{
    name = toLowerCase(name);
    feature = toLowerCase(feature);
    flowers.removeFeature(name, feature);
}

void FlowerLibrary::findFlowers(string feature) const
{
    flowers.findFlower(feature);
}

string FlowerLibrary::toLowerCase(string word)
{
    string result = word;
    for(int i=0; i<word.length(); i++)
    {
        if(word[i]>=65 && word[i]<=90)
            result[i] = word[i] + 32;
    }
    return result;
}

















