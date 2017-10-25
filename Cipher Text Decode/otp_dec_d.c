// Author: Chris Darnell
// Date: 3/17/17
// CS344(400)
// Description: otp_dec_d.c

// This program performs exactly like otp_enc_d, in syntax and usage. In this case, however, 
// otp_dec_d will decrypt ciphertext it is given, using the passed-in ciphertext and key. 
// Thus, it returns plaintext again to otp_dec


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "otp.h"
// Bool for encryption
#define ED_CHOICE 0   



///
////        MAIN
///




int main(int argc, char **argv)


{


// Variables used in main


    int   sock, cli;              
    int   valueSocket;                
    long  typeServer;             
    long  receivedData;              
    long  inputSize, keySize;
    char  *inputContent, *keyContent; 
    pid_t pid;                     
    socklen_t myCliLen;            
    struct sockaddr_in myServ, myCli; 

// Error if not two lines
  
    if(argc < 2)
    
    {

        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(1);
    
    }

// Set socket 

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    
    { 

        perror("Socket failed");
        exit(1);
    
    }

   
// If address is in use...


    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &valueSocket, sizeof(valueSocket)) == -1)
    
    {

        perror("Setsockopt failed");
        exit(1);
    
    }

    memset((char *)&myServ, 0, sizeof(myServ));

// Fill server info
  
    myServ.sin_family = AF_INET;
    myServ.sin_port = htons(atoi(argv[1])); 
    myServ.sin_addr.s_addr = htonl(INADDR_ANY);

// Link socket to server


    if(bind(sock, (struct sockaddr *)&myServ, sizeof(myServ)) == -1)
    
    {

        perror("Bind failed");
        exit(1);
    
    }

// Wait for client...


    if(listen(sock, 5) == -1)

    {

        perror("Listen failed");
        exit(1);
   
    }

    while(1)

    {

       myCliLen = sizeof(myCli); 
       cli = accept(sock, (struct sockaddr *)&myCli, &myCliLen);
       if(cli == -1)
       {
           perror("Accept failed");
           exit(1);
       }

// Fork, suggested from assignment prompt

       pid = fork();

       if(pid < 0)      
       
       {

           close(cli);
           cli = -1;
           perror("Fork failed");
       
       }

// Child: closes socket based on pid value
       
       if(pid == 0)     
       
       {
          
           close(sock);
           sock = -1;
           typeServer = ED_CHOICE;
           sendNumber(&cli, &typeServer);
           inputSize = getNumber(&cli);

// Input file


           sendText(&cli, "I got your input file size");
           keySize = getNumber(&cli);
           sendText(&cli, "I got your key file size");
           inputContent = malloc(sizeof(char) * (inputSize + 1));

// Find start of read...

           inputContent[0] = '\0';
           receivedData = readInputStream(&cli, inputContent, inputSize);

// Find end of read

// Same process for key below...


           inputContent[receivedData] = '\0';
           sendText(&cli, "I got your input file");
           keyContent = malloc(sizeof(char) * (keySize + 1));
           keyContent[0] = '\0';
           receivedData = readInputStream(&cli, keyContent, keySize);
           keyContent[receivedData] = '\0';

// Decode call

// Send encode back

// Free/close/cleanup for exit

           actionDecode(inputContent, keyContent);
           sendText(&cli, inputContent);
           free(inputContent);
           inputContent = 0;
           free(keyContent);
           keyContent = 0;
           close(cli);
           cli = -1;

           exit(0);
       
       }

// Parent must wait for child before exiting main

       else 
       
       {

           close(cli);
           cli = -1;

           wait(NULL);

       }
    
    }

    close(sock);
    sock = -1;

    return 0;
}
