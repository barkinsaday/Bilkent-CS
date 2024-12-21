/*
@author: Barkýn_Saday
@date: 05.01.2022
@title: CS201_HW4
*/
#ifndef ALGEBRAICEXPRESSION_H_INCLUDED
#define ALGEBRAICEXPRESSION_H_INCLUDED
#include <iostream>
#include "Stack.h"
using namespace std;
//defining operands might be helpful for "space problem"

// It converts an infix expression exp to its equivalent prefix form.
string infix2prefix( const string exp );
// It converts an infix expression exp to its equivalent postfix form.
string infix2postfix( const string exp );
// It converts a prefix expression exp to its equivalent infix form.
string prefix2infix( const string exp );
// It converts a prefix expression exp to its equivalent postfix form.
string prefix2postfix( const string exp );
// It converts a postfix expression exp to its equivalent infix form.
string postfix2infix( const string exp );
// It converts a postfix expression exp to its equivalent prefix form.
string postfix2prefix( const string exp );

//It evaluates an infix expression.
double evaluateInfix( const string exp );
//It evaluates a prefix expression.
double evaluatePrefix( const string exp );
//It evaluates a postfix expression.
double evaluatePostfix( const string exp );

//my functions:
string myReverse(string exp);
bool isOperand(char c);
//bool isOperand();



#endif // ALGEBRAICEXPRESSION_H_INCLUDED
