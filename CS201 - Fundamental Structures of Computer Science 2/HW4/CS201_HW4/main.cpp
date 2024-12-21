#include <iostream>
#include "AlgebraicExpression.h"
using namespace std;
int main()
{
    cout << "Start main..." << endl;

    string str1 = "( 12 + 5 ) - 20 * 4";
    string str2 = "(7 - 5) * 11 + 4";

    cout << "Inix to Postfix " << str1 << ": " << infix2postfix(str1) << endl;
    cout << "Inix to Prefix " << str1 << ": " << infix2prefix(str1) << endl;
    cout << "Inix to Postfix " << str2 << ": " << infix2postfix(str2) << endl;
    cout << "Inix to Prefix " << str2 << ": " << infix2prefix(str2) << endl;
    cout << prefix2infix("- 5 7 * 13") << endl;
    cout << postfix2prefix("abc") << endl;











    cout << "====================================================" << endl;



    cout << "End main..." << endl;
    return 0;
}
