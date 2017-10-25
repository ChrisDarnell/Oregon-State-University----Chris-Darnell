// Author: Chris Darnell
// Date: 3/17/17
// CS344(400)
// Description: otp_functions.c


// Server/client functions 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "otp.h"


// Flesh of functions prototyped in otp.h




///
////                FUNCTIONS
///




// Validate input, push to error if 0


int inputVerification(char *str)

{

    long strLen = (long)strlen(str); 
    long idx;                       

    for(idx = 0; idx < strLen; idx++)
    
    {
        
        if((str[idx] > 90) || ((str[idx] < 65) && (str[idx] != 32)))
        
        {

            return 0; 
        
        }
    
    }

    return 1; 

}



// Send # via network 

// Convert, keep # characters, error if none

void sendNumber(int *sock, long *num)

{

    long numberBeingSent;  
    int  numberActuallySent;    
    numberBeingSent = htonl(*num);

    if((numberActuallySent = send(*sock, &numberBeingSent, sizeof(numberBeingSent), 0)) == -1)
    
    {

        perror("client send failed");
        exit(1);
    
    }

}


// Send string via network

// Get char count, error if none


void sendText(int *sock, char *str)

{

    long len;  
    int  numberActuallySent; 
    len = strlen(str);

   
    if((numberActuallySent = send(*sock, str, len, 0)) == -1)
    
    {

        perror("client send failed");
        exit(1);
    
    }

}


// Receive #/ count

int getNumber(int *sock)

{

    long numberOutput; 
    long numberInput;  
    int  receivedNumber; 

// Push to error if fail

    
    if((receivedNumber = recv(*sock, &numberInput, sizeof(numberInput), 0)) == -1)
    
    {

        perror("server recv failed (client type)");
        exit(1);
    
    }

    else if(receivedNumber == 0)
    
    {

        perror("socket closed during recv");
        exit(1);
    
    }

    numberOutput = ntohl(numberInput); 

    return numberOutput;        

}


// Receive/read String/length/error check 
// Limit length of message so it can't be eternal

void getText(int *sock, char *str)

{
    long len;     
    int  receivedNumber;  
    len = MAXIMUM_SIZE; 

    
    if((receivedNumber = recv(*sock, str, len, 0)) == -1)
    
    {

        perror("client recv failed");
        exit(1);
    
    }

}


// Receive string/count/error check 


int readInputStream(int *sock, char *str, long maxChars)

{

    int  receivedNumber    = 0;  
    long receivedData = 0;  
    char buf[MAXIMUM_SIZE];    

   
    str[0] = '\0';

// Read/count...

    while(receivedData < maxChars)
    
    {

    
       
       if((receivedNumber = recv(*sock, buf, sizeof(buf), 0)) == -1)
       
       {

           perror("server recv failed (message)");
           exit(1);
       
       }

       else if(receivedNumber == 0)
       
       {

           perror("socket closed during recv (cli)");
           exit(1);
       
       }

       else 
       
       {
        
           strncat(str, buf, receivedNumber);
           receivedData += receivedNumber;

       }

    }

// Finish with count

    return receivedData; 
}


// Search for character to decode/encode/match to key


int codeSearch(char *inString, char ch)

{

    char *startAddress;  
    char *charAddress;    

    
    startAddress = &inString[0];
    charAddress = strchr(inString, ch);
    return charAddress - startAddress;

}



// Encode Characters


void actionEncode(char *inputChars, char *keyChars)

{

    char inputValid[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
    int  inputCh;         
    int  keyCh;            
    int  sum;             
    int  modulo;              
    long charactersIn;    
    long idx = 0;         

    charactersIn = strlen(inputChars); 

    while(idx < charactersIn)
    
    {

        inputCh = codeSearch(inputValid, inputChars[idx]); 
        keyCh = codeSearch(inputValid, keyChars[idx]);        
        sum = inputCh + keyCh;  
        modulo = sum % strlen(inputValid); 

// Replace with encoded char

        inputChars[idx] = inputValid[modulo]; 
        idx++;
   
    }

}


// Decode characters


void actionDecode(char *inputChars, char *keyChars)

{

    char inputValid[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
    int  inputCh;           
    int  keyCh;           
    int  diff;             
    int  modulo;              
    long charactersIn;    
    long idx = 0;           
    charactersIn = strlen(inputChars); 

    while(idx < charactersIn)
    
    {

        inputCh = codeSearch(inputValid, inputChars[idx]); 
        keyCh = codeSearch(inputValid, keyChars[idx]);    

       
        diff = inputCh - keyCh;

       
        if(diff < 0)
        
        {

            diff += strlen(inputValid);
        
        }


        modulo = diff % strlen(inputValid);

// Replace with decoded char

        inputChars[idx] = inputValid[modulo]; 
        idx++;
   
    }

}




