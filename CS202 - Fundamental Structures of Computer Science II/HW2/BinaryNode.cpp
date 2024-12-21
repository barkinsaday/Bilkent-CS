/*
* Title: Trees
* Author: Barkýn Saday
* ID: 21902967
* Section: 2
* Assignment: 2
* Description: binary node
*/
#include "BinaryNode.h"
using namespace std;
BinaryNode::BinaryNode()
{
    data = 0;
    size = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
}

BinaryNode::BinaryNode(int val)
{
    data = val;
    size = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
}
