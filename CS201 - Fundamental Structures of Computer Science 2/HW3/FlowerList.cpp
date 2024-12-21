/*
@Barkýn Saday
@21.12.2021
@CS201 HomeWork 3
@ID: 21902967
@Section: 1
*/
#include "FlowerList.h"
#include <iostream>
FlowerList::FlowerList()
{
    size = 0;
    head = NULL;
}

FlowerList::FlowerList(const FlowerList& aList)
{
    size = aList.size;

    if(aList.head == NULL)
    {
        head = NULL;
        return;
    }

    head = new FlowerNode;
    head->f = Flower(aList.head->f);

    FlowerNode *curr = head->next;
    FlowerNode *original = aList.head->next;
    while(original != NULL)
    {
       curr->f = Flower(original->f);
       curr = curr->next;
       original = original->next;
    }
}

FlowerList::~FlowerList()
{
    FlowerNode *temp = head;
    while(temp != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

bool FlowerList::isEmpty() const
{
    return size == 0;
}

int FlowerList::getLength() const
{
    return size;
}

bool FlowerList::retrieve(string flowerName, Flower& flower) const
{
   FlowerNode *curr = head;
   while(curr != NULL)
   {
       if((curr->f).getFlowerName() == flowerName)
       {
           flower = Flower(curr->f);
           return 1;
       }
       curr = curr->next;
   }
   return 0;
}

bool FlowerList::add(string flowerName)
{
    flowerName = toLowerCase(flowerName);
   if(head == NULL)
   {
       head = new FlowerNode;
       head->f = Flower(flowerName);
       head->next = NULL;
       size++;
       return 1;
   }

   FlowerNode *curr = head;

   while(curr != NULL)
   {
       if(curr->f.getFlowerName() == flowerName)
        return 0; // only case we return false: flower already exists
       curr = curr->next;
   }

   if(flowerName < head->f.getFlowerName())//instert before head (head will change)
   {
       FlowerNode *temp = new FlowerNode;
       temp->f = Flower(flowerName);
       temp->next = head;
       head = temp;
       temp = NULL;
       size++;
       return 1;
   }

   curr = head->next;
   FlowerNode *prev = head;

   while(curr != NULL)//add after head
   {
       if(flowerName < curr->f.getFlowerName())// a b c d-> e->f g h
       {
           FlowerNode *newptr = new FlowerNode;
           newptr->f = Flower(flowerName);
           newptr->next = curr;
           prev->next = newptr;
           size++;
           return 1;
       }
       curr = curr->next;
       prev = prev->next;
   }

   //if we exit the loop without returning or did not enter the loop at all "prev" is the last element and need to put out to to "prev->next"
   FlowerNode *newptr = new FlowerNode;
   newptr->f = Flower(flowerName);
   prev->next = newptr;
   newptr->next = NULL;
   size++;
   return 1;
}

bool FlowerList::remove(string flowerName)
{
    flowerName = toLowerCase(flowerName);
    if(head == NULL)
        return 0;

    if(head->f.getFlowerName() == flowerName)
    {
        FlowerNode *temp = head;
        head = head->next;
        delete temp;
        size--;
        temp = NULL;
        return 1;
    }

    FlowerNode *curr = head->next;//can be NULL which is ok
    FlowerNode *prev = head;//definitely not NULL

    while(curr != NULL)
    {
        if(curr->f.getFlowerName() == flowerName)
        {
            prev->next = curr->next;
            delete curr;
            size--;
            curr = NULL;//just in case
            return 1;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return 0;//if "if statement" never executed it means "feature" does not exists in the list so return false
}

void FlowerList::printFlowers()
{
    if(head == NULL)
        cout << "The library is empty." << endl;

    FlowerNode* curr = head;
    while(curr != NULL)
    {
        cout << curr->f.printFlower() << endl;
        curr = curr->next;
    }
}

void FlowerList::printOneFlower(string flowerName) const
{
    if(head == NULL)
    {
       cout << flowerName << " is not in the library." << endl;
       return;
    }

    FlowerNode *curr = head;
    while(curr != NULL)
    {
        if(curr->f.getFlowerName() == flowerName)
        {
            cout << curr->f.printFlower() << endl;
            return;
        }
        curr = curr->next;
    }
    cout << flowerName << " is not in the library." << endl;
}

void FlowerList::printFlowersC() const
{
    if(head == NULL)
        cout << "The library is empty." << endl;

    FlowerNode* curr = head;
    while(curr != NULL)
    {
        cout << curr->f.printFlower() << endl;
        curr = curr->next;
    }
}

bool FlowerList::addFeature(string name, string feature)
{
    name = toLowerCase(name);
    feature = toLowerCase(feature);
    if(head == NULL)
    {
        cout << name << " is not in the library." << endl;
        return 0;
    }

    FlowerNode *curr = head;
    while(curr != NULL)
    {
        if(curr->f.getFlowerName() == name)
        {
            if(curr->f.add(feature))
            {
                cout << feature << " is added to " << name << endl;
                return 1;
            }
            cout << feature << " already exists in " << name << endl;
            return 0;
        }
        curr = curr->next;
    }
    cout << name << " is not in the library." << endl;
    return 0;
}

bool FlowerList::removeFeature(string name, string feature)
{
    name = toLowerCase(name);
    feature = toLowerCase(feature);
    if(head == NULL)
    {
       cout << name << " is not in the library." << endl;
       return 0;
    }

    FlowerNode *curr = head;
    while(curr != NULL)
    {
        if(curr->f.getFlowerName() == name)
        {
            if(curr->f.remove(feature))
            {
                cout << feature << " is removed from " << name << endl;
                return 1;
            }
            cout << feature << " does not exists in " << name << endl;
            return 0;
        }
        curr = curr->next;
    }
    cout << name << " is not in the library." << endl;
    return 0;
}

bool FlowerList::containsFlower(string name)
{
    if(head == NULL)
        return 0;

    FlowerNode *curr = head;
    while( curr != NULL)
    {
        if(curr->f.getFlowerName() == name)
            return 1;
        curr = curr->next;
    }
    return 0;
}

void FlowerList::findFlower(string feature) const
{
    cout << feature << " flowers: ";
    if(head == NULL)
    {
        cout << "there is no such flower." << endl;
        return;
    }

    bool check;

    FlowerNode *curr = head;
    while(curr != NULL)
    {
        if(curr->f.containsFeature(feature))
        {
           check = 1;
           cout << curr->f.getFlowerName() + ", ";
        }
        curr = curr->next;
    }

    if(check)
    {
        cout << endl;
        return;
    }

    cout << "there is no such flower." << endl;
}

string FlowerList::toLowerCase(string word)
{
    string result = word;
    for(int i=0; i<word.length(); i++)
    {
        if(word[i]>=65 && word[i]<=90)
            result[i] = word[i] + 32;
    }
    return result;
}








