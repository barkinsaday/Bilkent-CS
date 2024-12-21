/*
@Barkýn Saday
@21.12.2021
@CS201 HomeWork 3
@ID:21902967
@Section: 1
*/
#include "Flower.h"
#include <iostream>
using namespace std;
//Remember: Flower has the data member head which is a featureNode
Flower::Flower()
{
    size = 0;
    flowerName = "-";// no name
    head = NULL;// no head
}

Flower::Flower(string name)
{
    size = 0;
    flowerName = name;
    head = NULL;
}

Flower::Flower(const Flower& aFlower)
{
    size = aFlower.size;
    flowerName = aFlower.flowerName;

    if(aFlower.head == NULL)
    {
        head = NULL;
        return;
    }

    //copy the first node
    head = new FeatureNode;
    head->feature = (aFlower.head)->feature;

    //copy rest
    FeatureNode *newptr = head;

    for(FeatureNode *original = aFlower.head->next;
        original != NULL;
        original = original->next)
    {
        newptr->next = new FeatureNode;
        newptr = newptr->next;
        newptr->feature = original->feature;
    }
    newptr->next = NULL;
}

Flower::~Flower()
{
    FeatureNode *temp = head;
    while(temp != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

bool Flower::isEmpty() const
{
    return size == 0;
}

int Flower::getLength() const
{
    return size;
}

bool Flower::add(string feature)
{
    feature = toLowerCase(feature);
    if(head == NULL)
    {
        head = new FeatureNode;
        head->feature = feature;
        head->next = NULL;
        size++;
        return 1;
    }

    FeatureNode *curr = head;

    while(curr != NULL)
    {
       if(curr->feature == feature)//check if the feature already exists
           return 0; // only case we return false: feature already exists (print it in FlowerLibrary addFeature())
       curr = curr->next;
    }

    if(feature < head->feature)//add before head (head will change)
    {
        FeatureNode *newPtr = new FeatureNode;
        newPtr->feature = feature;
        newPtr->next = head;
        head = newPtr;
        size++;
        return 1;
    }

    FeatureNode *prev = head;
    curr = head->next;

    while(curr != NULL)//add somewhere after the head
    {
        if(feature < curr->feature)
        {
            FeatureNode *newPtr = new FeatureNode;
            newPtr->feature = feature;
            newPtr->next = curr;
            prev->next = newPtr;
            size++;
            return 1;
        }
        curr = curr->next;
        prev = prev->next;
    }

    //if we exit loop without returning or didn't enter the loop at all than we must add to end
    //this means our curr is NULL right now and prev is the last element which is definetely not NULL since we know there exists a head at least
    FeatureNode *newPtr = new FeatureNode;
    newPtr->feature = feature;
    newPtr->next = NULL;
    prev->next = newPtr;
    size++;
    return 1;
}

bool Flower::remove(string feature)
{
    feature = toLowerCase(feature);
    if(head == NULL)//no node no feature
        return 0;

    if(head->feature == feature)//if head is what we want to delete  (need to change head)
    {
        FeatureNode *temp = head;
        head = head->next;
        delete temp;
        size--;
        return 1;
    }

    FeatureNode *curr = head->next;//can be NULL which is ok
    FeatureNode *prev = head;//definitely not NULL

    while(curr != NULL)
    {
        if(curr->feature == feature)
        {
            prev->next = curr->next;
            delete curr;
            curr = NULL;//just in case
            size--;
            return 1;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return 0;//if "if statement" never executed it means "feature" does not exists in the list so return false
}

string Flower::printFlower() const
{
    if(head == NULL)
        return flowerName + ": No Feature";

    string result = flowerName + ": ";
    FeatureNode *curr = head;
    while(curr != NULL)
    {
        if(curr->next == NULL)//if this is the last feature do not print comma
            result = result + (curr->feature);
        else
            result = result + (curr->feature) + ", ";
        curr = curr->next;
    }
    return result;
}

string Flower::getFlowerName()
{
    return flowerName;
}

void Flower::setName(string name)
{
    flowerName = name;
}

bool Flower::containsFeature(string feature)
{
    if(head == NULL)
        return 0;

    FeatureNode *curr = head;
    while(curr != NULL)
    {
        if(curr->feature == feature)
            return 1;
        curr = curr->next;
    }
    return 0;
}

string Flower::toLowerCase(string word)
{
    string result = word;
    for(int i=0; i<word.length(); i++)
    {
        if(word[i]>=65 && word[i]<=90)
            result[i] = word[i] + 32;
    }
    return result;
}





