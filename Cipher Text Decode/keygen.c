// Author: Chris Darnell
// Date: 3/17/17
// CS344(400)
// Description: keygen.c

// This program creates a key file of specified length. The characters in the file generated will be 
// any of the 27 allowed characters, generated using the standard UNIX randomization methods. Do not 
// create spaces every five characters, as has been historically done. Note that you specifically do not 
// have to do any fancy random number generation: we’re not looking for cryptographically secure random 
// number generation! rand() is just fine. The last character keygen outputs should be a newline. 
// All error text must be output to stderr, if any.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "otp.h"





///
////                MAIN
///




int main(int argc, char **argv)

{

// Error if no length received


    if(argc == 1)
    

    {

        printf("Usage: %s length_of_key\n", argv[0]);
        exit(1);
    
    }

// Variables used in main

// Random init


    char inputValid[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int keySize = 0;  
    int seed;         
    int idx;         
    keySize = atoi(argv[1]);  
    seed = time(NULL);        
    srand(seed);  

// Print from idx until keylength reached            

    for(idx = 0; idx < keySize; idx++)
    
    {
       
        printf("%c", inputValid[rand() % (int)strlen(inputValid)]);
    
    }

    printf("\n");

    return 0;

}
