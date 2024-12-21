/*
* Title: Trees
* Author: Barkýn Saday
* ID: 21902967
* Section: 2
* Assignment: 2
* Description: BST.h
*/
#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include <iostream>
#include "BinaryNode.h"
using namespace std;
class BinarySearchTree
{
public:
    //Constructors/Destructor
    BinarySearchTree();
    BinarySearchTree(int newEntry);
    ~BinarySearchTree();

    //Methods
    bool isEmpty();
    int getHeight();
    int getNumberOfNodes();
    bool add(int newEntry);
    bool remove(int anEntry);
    bool contains(int anEntry);
    void inorderTraverse();
    int getWidth();
    int count(int a, int b);
    int select(int anEntry);
    int successor(int anEntry);

private:
    //Data members
    int numberOfNodes;
    int height;
    BinaryNode *root;
};



#endif // BINARYSEARCHTREE_H_INCLUDED
