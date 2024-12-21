/*
* Title: Trees
* Author: Barkýn Saday
* ID: 21902967
* Section: 2
* Assignment: 2
* Description: BST.cpp
*/
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

//Default Constructor
BinarySearchTree::BinarySearchTree() //Empty tree (no nodes)
{
    root = NULL;
    numberOfNodes = 0;
    height = 0;
}

BinarySearchTree::BinarySearchTree(int newEntry) //Root is created
{
    root = new BinaryNode(newEntry);
    numberOfNodes = 1;
    height = 0;
}

 bool BinarySearchTree::isEmpty()
 {
     return root == NULL;
 }

 int BinarySearchTree::getHeight()
 {
     return height;
 }

 int BinarySearchTree::getNumberOfNodes()
 {
     return numberOfNodes;
 }

 bool BinarySearchTree::add(int newEntry)
 {
     //Don't add if entry <= 0
     if(newEntry <= 0)
     {
         cout << "Invalid value to add" << endl;
         return 0;
     }

     //Don't add if entry already exists (implement contains() first)
     if(contains(newEntry))
     {
         cout << "The value " << newEntry << " is already in the tree" << endl;
         return 0;
     }

     //If three is empty add as root
     if(isEmpty())
     {
         root = new BinaryNode(newEntry);
         cout << newEntry << " is added as the root" << endl;
         numberOfNodes++;
         height++;
         return 1;
     }

     //Otherwise find correct position and add the new node accordingly
     BinaryNode *curr = root;
     int currentHeight = 1;
     while(curr != NULL)
     {
         currentHeight++;
         //if entry is bigger go to right sub-tree else go to left sub-tree
         if(newEntry > curr->data)
         {
             if(curr->right == NULL)//time to add
             {
                 curr->right = new BinaryNode(newEntry);
                 //Set new node's (curr->right) left/right to NULL
                 curr->right->right = NULL;
                 curr->right->left = NULL;
                 //Set parent
                 curr->right->parent = curr;
                 cout << newEntry << " is added to right of " << curr->right->parent->data << endl;
                 numberOfNodes++;
                 if(currentHeight > height)
                    height = currentHeight;
                 break;
             }
             curr = curr->right;
         }

         else
         {
             if(curr->left == NULL)//time to add
             {
                 curr->left = new BinaryNode(newEntry);
                 //Set new node's (curr->left) left/right to NULL
                 curr->left->right = NULL;
                 curr->left->left = NULL;
                 //Set parent
                 curr->left->parent = curr;
                 cout << newEntry << " is added to left of " << curr->left->parent->data << endl;
                 numberOfNodes++;
                 if(currentHeight > height)
                    height = currentHeight;
                 break;
             }
             curr = curr->left;
         }
     }
     return 1;
 }


bool BinarySearchTree::contains(int anEntry)
{
    if(root == NULL)
        return 0;
    if(anEntry <= 0)
        return 0;

    BinaryNode *curr = root;
    while(curr != NULL)
    {
        if((curr->data) == anEntry)
        {
            return 1;
        }

        if((curr->data) < anEntry)
        {
            curr = curr->right;
        }

        else if((curr->data) > anEntry)
        {
            curr = curr->left;
        }
    }
    return 0;
}

bool BinarySearchTree::remove(int anEntry)
{
    if(root == NULL)
        return 0;
    if(anEntry <= 0)
        return 0;

    BinaryNode *curr = root;
    while(curr != NULL)
    {
        if((curr->data) == anEntry)
        {
            return 1;
        }

        if((curr->data) < anEntry)
        {
            curr = curr->right;
        }

        else if((curr->data) > anEntry)
        {
            curr = curr->left;
        }
    }
    return 0;
}

























