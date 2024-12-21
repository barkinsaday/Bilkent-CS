/*
* Title: Trees
* Author: Barkýn Saday
* ID: 21902967
* Section: 2
* Assignment: 2
* Description: binary node
*/
#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED
#include <iostream>
struct BinaryNode
{
    //Constructors
    BinaryNode();
    BinaryNode(int val);

    //Data-members
    BinaryNode *left;
    BinaryNode *right;
    int data;
    BinaryNode *parent;
    int size;
};


#endif // BINARYNODE_H_INCLUDED
