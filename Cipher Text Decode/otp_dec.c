// Author: Chris Darnell
// Date: 3/17/17
// CS344(400)
// Description: otp_dec.c

// Similarly, this program will connect to otp_dec_d and will ask it to decrypt ciphertext using a passed-in 
// ciphertext and key, and otherwise performs exactly like otp_enc, and must be runnable in the same three 
// ways. otp_dec should NOT be able to connect to otp_enc_d, even if it tries to connect on the correct port - 
// you'll need to have the programs reject each other, as described in otp_enc.


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
// bool for encryption
#define CHOICE_CLIENT 0  



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

// If 4 items not received, push to error

    if(argc < 4)
    
    {

        fprintf(stderr, "Usage: %s [input file] [key file] [port]\n", argv[0]);
        exit(1);
    
    }

// Get file/key size

    stat(argv[1], &inFile);
    stat(argv[2], &keyFile);
    inputSize = inFile.st_size;
    keySize = keyFile.st_size;
 

// Key must be less than input

// Short error if no from grading pdf


    if(keySize < inputSize)
    
    {

        fprintf(stderr, "ERROR: key file is too short.\n");
        exit(1);
    
    }

// Open input file

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

// Verify valid char


    if(!inputVerification(inputContent))
    
    {

        fprintf(stderr, "ERROR: %s contains invalid characters (only A-Z and spaces allowed)\n", argv[1]);
        exit(1);
    
    }

// Open key file

    keyFp = open(argv[2], O_RDONLY);
    if(keyFp == -1)
    
    {

        perror("Error opening key file");
        exit(1);
    
    }

    keyContent = malloc(sizeof(char) * keySize);

// Read key file

    keyChars = read(keyFp, keyContent, keySize);
    if(keyChars == -1)
    
    {

        perror("Error reading key file");
        exit(1);
    
    }

// Set null terminate for key...


    keyContent[keySize - 1] = '\0';
    close(keyFp);

// Set up socket...

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    
    {

        perror("Socket failed");
        exit(1);
    
    }

// localhost, from assignment prompt


    if((server = gethostbyname("localhost")) == NULL)
    
    {

        perror("gethostbyname failed");
        exit(1);
    
    }

// init socket

    memset((char *)&myServ, 0, sizeof(myServ));


// fill domain/network 

    myServ.sin_family = AF_INET;
    myServ.sin_port = htons(atoi(argv[3])); 
    memcpy(&myServ.sin_addr, server->h_addr_list[0], server->h_length);

// Connect server

    if(connect(sock, (struct sockaddr *)&myServ, sizeof(myServ)) == -1)
    
    {

        perror("connect failed");
        exit(1);
    
    }
    
// Verify connection, push to err if no


    typeServer = getNumber(&sock);
    if(typeServer != CHOICE_CLIENT)
    
    {

        fprintf(stderr, "ERROR: %s cannot find %s_d.\n", argv[0], argv[0]);

// Close/free pointers/memory
        
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
    
// Read sent verification


    memset((char *)&buf, '\0', sizeof(buf));
    getText(&sock, buf);

// Send/read key file info 
   
    keySize -= 1;
    sendNumber(&sock, &keySize);
    memset((char *)&buf, '\0', sizeof(buf));
    getText(&sock, buf);
    sendText(&sock, inputContent);
    memset((char *)&buf, '\0', sizeof(buf));
    getText(&sock, buf);
    sendText(&sock, keyContent);

 
// Get response


    receivedData = readInputStream(&sock, inputContent, inputSize);

// Set null terminate
// Print decode

    inputContent[receivedData] = '\0';
    printf("%s\n", inputContent);

// Close socket/free pointers/mem
   
    close(sock);
    free(inputContent);
    inputContent = 0;
    free(keyContent);
    keyContent = 0;
   
    return 0;

}
