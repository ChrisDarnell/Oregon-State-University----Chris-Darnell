// Author: Chris Darnell
// Date: 3/17/17
// CS344(400)
// Description: otp.h

// Function Prototypes for use in otp encode/decode program




#ifndef OTP_H
#define OTP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#define MAXIMUM_SIZE 4196


///
////				PROTOTYPES
///


// Some socket help from https://www.cs.rutgers.edu/~pxk/416/notes/16-sockets.html


// Input verification

// Pushes to error if 0


int inputVerification(char *str);

// Transfers number via network 


void sendNumber(int *sock, long *num);


// Transfers string via network

void sendText(int *sock, char *str);


// Gets number from network


int getNumber(int *sock);


// Gets string via network 

void getText(int *sock, char *str);



// Count of number characters received


int readInputStream(int *sock, char *str, long maxChars);



// Count of string received


int codeSearch(char *inString, char ch);



// Encode and Decode 

void actionEncode(char *inputChars, char *keyChars);
void actionDecode(char *inputChars, char *keyChars);


#endif
