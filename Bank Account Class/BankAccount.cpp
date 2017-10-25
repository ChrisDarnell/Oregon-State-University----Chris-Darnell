// Author: Chris Darnell
// Date: 4/13/16
// Description: Project 3.b - BankAccount.cpp
//

#include "BankAccount.hpp"

// Get customer starting information.


string BankAccount::getCustomerID()

    {
        return customerID;
    }

string BankAccount::getCustomerName()

    {

        return customerName;
    
    }

double BankAccount::getCustomerBalance()

    {
        return customerBalance;
       
    }

// Deposit function.

void BankAccount::deposit(double& bal)

    {
        
        customerBalance += bal;
    
    }

// Withdraw function.

void BankAccount::withdraw(double& bal)

    {
       
        customerBalance -= bal;

    }





