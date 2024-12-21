/*
@author: Barkýn_Saday
@date: 05.01.2022
@title: CS201_HW4
*/
#include "AlgebraicExpression.h"
// It converts an infix expression exp to its equivalent prefix form.
string infix2postfix(const string exp)
{
    Stack s;
    string result = "";

    for(int i=0; i<exp.length(); i++)
    {
        switch(exp[i]) //default: operand
        {
         case '+': case '-': //operator case (precedence +, -)
             while( (!s.isEmpty()) &&
                    (s.getTop() != '(') &&
                    (s.getTop()=='+'||s.getTop()=='-'||s.getTop()=='*'||s.getTop()=='/'))
             {
                 result = result + s.getTop();
                 s.pop();
             }

             s.push(exp[i]);
             break;

         case '*': case '/'://operator case (precedence *, /)
            while( (!s.isEmpty()) &&
                    (s.getTop() != '(') &&
                    (s.getTop()=='*'||s.getTop()=='/') )
            {
                result = result + s.getTop();
                s.pop();
            }

             s.push(exp[i]);
            break;

         case '(':
            s.push(exp[i]);
            break;

         case ')':
            while(s.getTop() != '(')
            {
                result = result + s.getTop();
                s.pop();
            }
            s.pop();//pop '('
            break;

         default://operand or space
            result = result + exp[i];
            break;
        }//end of switch
    }//end of for loop
    while(!s.isEmpty())
    {
        result = result + s.getTop();
        s.pop();
    }

    for(int i=0; i<result.length(); i++)
    {
        if(result[i] == ' ' && i < result.length()-2)
        {
            if(result[i+1] == ' ')
            {
                result = result.substr(0,i+1) + result.substr(i+2, result.length());
            }
        }
    }
    return result;
}

string infix2prefix(const string exp)
{
   return myReverse(infix2postfix(myReverse(exp)));
}

string prefix2infix(string exp)
{
    string result = "";
    Stack s;
    int len = exp.length();

    for(int i=len-1; i>=0; i--)
    {
        if(isOperand(exp[i]))
        {
            string temp1 = "";
            string temp2 = "";
           while(s.getTop() == ' ')
           {
               s.pop();
           }

           temp1 = s.getTop() + temp1;
           s.pop();
           while(s.getTop() == ' ')
           {
               s.pop();
           }
           if(s.getTop() != ' ')
           {
               temp1 = temp1 + s.getTop();
               s.pop();
           }
           else
            {
                temp2 = s.getTop() + temp2;
                s.pop();
            }

           result = "( " + temp1 + " " + exp[i] + " " + temp2 + " ) " + result;
        }

        else
        {
            s.push(exp[i]);
        }
    }
    while(!s.isEmpty() && s.getTop() == ' ')
    {
        s.pop();
    }
    return result;
}

string prefix2postfix( const string exp )
{
    return myReverse(exp);
}

string postfix2prefix( const string exp)
{
    return myReverse(exp);
}

string postfix2infix( const string exp )
{
    return "";
}


//myFunctions:
string myReverse(string exp)
{
   string result = "";
   for(int i=exp.length()-1; i>=0; i--)
   {
       if(exp[i] == '(')
            result = result + ')';
       else if(exp[i] == ')')
        result = result + '(';
       else
        result =  result + exp[i];
   }
   return result;
}

bool isOperand(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}














































