// Author: Chris Darnell
// Date: 4/13/16
// Description: Project 3.b - BankAccount.hpp


#ifndef BankAccount_hpp
#define BankAccount_hpp

#include <stdio.h>
#include <string>
using namespace std;

// BankAccount header file.

// Class declaration.

class BankAccount

{
    
    private:
        
        double customerBalance;
        string customerName, customerID;
        
    public:
        
// Function prototypes.
    
        string getCustomerName();
        string getCustomerID();
        double getCustomerBalance();
        void withdraw(double& bal);
        void deposit(double& bal);
    
// Constructor
    
BankAccount(string name, string id, double balance)
    
    {
        customerName = name;
        customerID = id;
        customerBalance = balance;
    }
};

#endif /* BankAccount_hpp */
