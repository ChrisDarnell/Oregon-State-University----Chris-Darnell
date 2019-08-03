// Author: Chris Darnell
// Date: 3/17/17
// CS344(400)
// Description: otp_enc.c

// This program connects to otp_enc_d, and asks it to perform a one-time pad style encryption as detailed above. 
// By itself, otp_enc doesn’t do the encryption - otp_end_d does. The syntax of otp_enc is as follows:
//  otp_enc plaintext key port In this syntax, plaintext is the name of a file in the current directory that 
//  contains the plaintext you wish to encrypt. Similarly, key contains the encryption key you wish to use to encrypt the text. Finally, port is the port that otp_enc should attempt to connect to otp_enc_d on.
// When otp_enc receives the ciphertext back from otp_enc_d, it should output it to stdout. Thus, otp_enc can 
// be launched in any of the following methods, and should send its output appropriately:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "otp.h"
// Bool for encryption choice 1/encode
#define CHOICE_CLIENT 1  




///
////                MAIN
/// 




int main(int argc, char **argv)


{

// Variables used in main


    int    sock;                   
    long   inputSize, keySize; 
    int    inputFp, keyFp;            
    int    inChars, keyChars;      
    long   receivedData;             
    int    typeServer;            
    char   *inputContent, *keyContent; 
    char   buf[MAXIMUM_SIZE];            
    struct sockaddr_in myServ;   
    struct hostent *server;        
    struct stat inFile, keyFile;    


// If not 4 items, error


    if(argc < 4)
    
    {

        fprintf(stderr, "Usage: %s [input file] [key file] [port]\n", argv[0]);
        exit(1);
    
    }

// Get input file size


    stat(argv[1], &inFile);
    stat(argv[2], &keyFile);
    inputSize = inFile.st_size;
    keySize = keyFile.st_size;
 
// Key file must be less than input
    
    if(keySize < inputSize)
    
    {

        fprintf(stderr, "ERROR: Key file is too short.\n");
        exit(1);
    
    }


// Open input, create buffer for read


    inputFp = open(argv[1], O_RDONLY);
    if(inputFp == -1)
    
    {

        perror("Error opening input file");
        exit(1);
    
    }


    inputContent = malloc(sizeof(char) * inputSize);
   
// Read input


    inChars = read(inputFp, inputContent, inputSize);
    if(inChars == -1)
    
    {

        perror("Error reading input file");
        exit(1);
    
    }

// Set null terminate


    inputContent[inputSize - 1] = '\0';
    close(inputFp);

// Validate char input


    if(!inputVerification(inputContent))
    
    {

        fprintf(stderr, "ERROR: %s contains invalid characters (only A-Z and spaces allowed)\n", argv[1]);
        exit(1);
    
    }

 // Open key file, same process as input above


    keyFp = open(argv[2], O_RDONLY);
    if(keyFp == -1)
    

    {

        perror("Error opening key file");
        exit(1);
    
    }

  
    keyContent = malloc(sizeof(char) * keySize);
    keyChars = read(keyFp, keyContent, keySize);
    if(keyChars == -1)
   
    {

        perror("Error reading key file");
        exit(1);
    
    }


    keyContent[keySize - 1] = '\0';
    close(keyFp);

// Set up socket


    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    
    {

        perror("Socket failed");
        exit(1);
    
    }

 // localhost, per assignment prompt


    if((server = gethostbyname("localhost")) == NULL)
    
    {

        perror("gethostbyname failed");
        exit(1);
    
    }

    memset((char *)&myServ, 0, sizeof(myServ));

 // Fill socket with server info 

    myServ.sin_family = AF_INET;
    myServ.sin_port = htons(atoi(argv[3])); 
    memcpy(&myServ.sin_addr, server->h_addr_list[0], server->h_length);

// Connect server

    if(connect(sock, (struct sockaddr *)&myServ, sizeof(myServ)) == -1)
    
    {

        perror("connect failed");
        exit(1);
    
    }
    
 // Validate connection


    typeServer = getNumber(&sock);
    if(typeServer != CHOICE_CLIENT)
    
    {

        fprintf(stderr, "ERROR: %s cannot find %s_d.\n", argv[0], argv[0]);

// Close socket/free pointers/mem

        close(sock);
        free(inputContent);
        inputContent = 0;
        free(keyContent);
        keyContent = 0;

        exit(1);
    
    }

// Send input file size


    inputSize -= 1;
    sendNumber(&sock, &inputSize);
    
// Read input


    memset((char *)&buf, '\0', sizeof(buf));
    getText(&sock, buf);

// Repeat wit key file...


    keySize -= 1;
    sendNumber(&sock, &keySize);
    memset((char *)&buf, '\0', sizeof(buf));
    getText(&sock, buf);

// Send input

    sendText(&sock, inputContent);
    memset((char *)&buf, '\0', sizeof(buf));
    getText(&sock, buf);

// Send key

    sendText(&sock, keyContent);

// Receive, set null to find end of file

    receivedData = readInputStream(&sock, inputContent, inputSize);
    inputContent[receivedData] = '\0';

 // Print encode


    printf("%s\n", inputContent);

// Close socket, free pointers, mem before exit
    
    close(sock);
    free(inputContent);
    inputContent = 0;
    free(keyContent);
    keyContent = 0;

    return 0;

}
