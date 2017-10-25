// Author: Chris Darnell
// Date: 5/25/16
// Description: Project 9.b - postifxEval.cpp


#include <iostream>
#include <stack>
using namespace std;


// Write a function named postfixEval that uses a stack<double> (from the Standard Template Library) to evaluate postfix expressions.

// It should take a C-style string parameter that represents a postfix expression.  The only symbols in the string will be +, -, *, /, digits and spaces.  '+' and '-' will only appear in the expression string as binary operators - not as unary operators that indicate the sign of a number.

// The return type should be double.  You may find the isdigit() function useful in parsing the expression.  You may also use strtok() and atof().


//  Read a postfix expression from left to right.  When you read a number, push it on the stack.  When you read an operand, pop the top two numbers off the stack, apply the operator to them, and push the result on top of the stack.  At the end, the result of the expression should be the only number on the stack.


double postfixEval(char *str)

{
    stack<double> myStack;
    char *s = str;
    while(*s != '\0'){
        
        if(*s >= '0' && *s <= '9')
        {
            int number = 0;
            while(*s >= '0' && *s <= '9' && *s != '\0')
            {
                number *= 10;
                number += *s - '0';
                s++;
            }
            myStack.push(number);
        }
        
// Test for operand.
        
        
        if(*s == '+' || *s == '-' || *s == '*' || *s == '/'){
            
// Take two off top of stack, apply operand.
            
            double objectOne, objectTwo;
            objectOne = myStack.top();
            myStack.pop();
            objectTwo = myStack.top();
            myStack.pop();
            
            if(*s == '+')
            {
                myStack.push(objectTwo + objectOne);
            }
            if(*s == '-')
            {
                myStack.push(objectTwo - objectOne);
            }
            if(*s == '*')
            {
                myStack.push(objectTwo * objectOne);
            }
            if(*s == '/')
            {
                myStack.push(objectTwo / objectOne);
            }
        }
        s++;
    }

// Return top of stack.
    
    return myStack.top();
}





// Test input from assignment.
//
//int main()
//
//{
//    char x[] = "25 12 7 - 2 * /";
//    cout << "The result is: " << postfixEval(x) << "\n";
//}
