// Chris Darnell
// Project #2
// ftserver.c

// # FTP client/server file transfer system

//  Sources Used:
//  *  http://beej.us/guide/bgnet/
//  References Used: 
//  *  Advanced Programming in the UNIX Environment, 3rd Edition by W. Richard Stevens
//  *  https://linux.die.net/man/2/read 
//  *  https://en.wikibooks.org/wiki/A_Little_C_Primer/C_File-IO_Through_System_Calls
//  *  https://docs.python.org/2/howto/sockets.html
//  *  https://docs.python.org/2/howto/argparse.html
//  *  https://docs.python.org/2/library/socketserver.html
//  *  https://en.wikipedia.org/wiki/File_Transfer_Protocol



// Specs:
// 1. ftserver starts on Host A, and validates command-line parameters (<SERVER_PORT>).
// 2. ftserver waits on <PORTNUM> for a client request.
// 3. ftclient starts on Host B, and validates any pertinent command-line parameters.
// (<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <FILENAME>,
// <DATA_PORT>, etc...)
// 4. ftserver and ftclient establish a TCP control connection on <SERVER_PORT>. (For
// the remainder of this description, call this connection P)
// 5. ftserver waits on connection P for ftclient to send a command.
// 6. ftclient sends a command (-l (list) or -g <FILENAME> (get)) on connection P.
// 7. ftserver receives command on connection P.
// If ftclient sent an invalid command
// ftserver sends an error message to ftclient on connection P, and ftclient
// displays the message on-screen.
// otherwise
// • ftserver initiates a TCP data connection with ftclient on <DATA_PORT>. (Call this connection Q)
// • If ftclient has sent the -l command, ftserver sends its directory to ftclient on connection Q, and ftclient displays the directory on-screen.
// • If ftclient has sent -g <FILENAME>, ftserver validates FILENAME, and either
// - sends the contents of FILENAME on connection Q. ftclient saves the file in the current default directory (handling "duplicate file name" error
// or if necessary), and displays a "transfer complete" message on-screen
// - sends an appropriate error message (“File not found”, etc.) to ftclient on connection P, and ftclient displays the message on-screen.
// • ftserver closes connection Q (don’t leave open sockets!).
// 8. ftclient closes connection P (don’t leave open sockets!) and terminates.
// • Don't hard-code the port numbers
// • Don’t use the well-known FTP port numbers, or 30021 or 30020.


#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CONNECTS 10 
#define MAX_PLLENGTH 512 
#define BACKLOG      5 
#define TAG_LENGTH   8 


///
/////  		PROTOTYPES
///



void sigHandler(int sig);
int isStrInt(char *str, int *n);
char **getFileList(char *dirname, int *numFiles);
void dataReceiver(int socket, void *buffer, int size);
void packetReceiver(int socket, char *tag, char *data);
int controlSess(int controlSocket, char *commandTag, int *dataPort, char* filename);
int dataSess(int controlSocket, int dataSocket, char *commandTag, char *filename);
void dataSender(int socket, void *buffer, int numBytes);
void packetSender(int socket, char *tag, char *data);
void startFtpServer(int port);





// Handles sigalert
 
void sigHandler(int sig)
{
	int status;                  
	struct sigaction interrupt;   

	printf("\nftserver closed\n");

	interrupt.sa_handler = SIG_DFL;
	status = sigaction(SIGINT, &interrupt, 0);
	if (status == -1) {
		perror("sigaction");
		exit(1);
	}

	// Send interrupt signal 
	status = raise(SIGINT);
	if (status == -1) {
		perror("raise");
		exit(1);
	}
}


// Converts string to int
 
int isStrInt(char *str, int *n)
{

	char c;
	int matches = sscanf(str, "%d %c", n, &c);
	return matches == 1;
}

// Get list of files from which to choose for transfer


char ** getFileList(char *dirname, int *numFiles)
{
	char **fileList;     
	DIR *dir;             
	struct dirent *entry;
	struct stat info;    

	// Open directory.
	dir = opendir(dirname);
	if (dir == NULL) {
		fprintf(stderr, "ftserver: unable to open %s\n", dirname);
		exit(1);
	}

	// Get list filenames 
	*numFiles = 0;
	fileList = NULL;
	while ((entry = readdir(dir)) != NULL) {

		// Skip subdirectories.
		stat(entry->d_name, &info);
		if (S_ISDIR(info.st_mode)) {
			continue;
		}

		// Add filename to the list.
		{
		
			if (fileList == NULL) {
				fileList = malloc(sizeof(char *));
			} else {
				fileList = realloc(fileList, (*numFiles + 1) * sizeof(char *));
			}
			assert(fileList != NULL); 
			fileList[*numFiles] = malloc((strlen(entry->d_name) + 1) * sizeof(char));
			assert(fileList[*numFiles] != NULL); 

			// Store filename 
			strcpy(fileList[*numFiles], entry->d_name);
			(*numFiles)++;
		}
	}

	// Close direct
	closedir(dir);

	return fileList;
}


// Accept data


void dataReceiver(int socket, void *buffer, int numBytes)
{
	int ret;              
	int receivedBytes;    

	// Get number bytes.
	receivedBytes = 0;
	while (receivedBytes < numBytes) {
		ret = recv(socket, buffer + receivedBytes, numBytes - receivedBytes, 0);

		// Error...
		if (ret == -1) {
			perror("recv");
			exit(1);
		}

		//...or get data
		else {
			receivedBytes += ret;
		}
	}
}

// Accept packet



void packetReceiver(int socket, char *tag, char *data)
{
	unsigned short packetLength;       
	unsigned short dataLength;         
	char tmpTag[TAG_LENGTH + 1];          
	char tmpData[MAX_PLLENGTH + 1]; 

	// Receive pack length.
	dataReceiver(socket, &packetLength, sizeof(packetLength));
	packetLength = ntohs(packetLength);

	// Receive tag 
	dataReceiver(socket, tmpTag, TAG_LENGTH);
	tmpTag[TAG_LENGTH] = '\0';
	if (tag != NULL) { strcpy(tag, tmpTag); }

	// Receive data
	dataLength = packetLength - TAG_LENGTH - sizeof(packetLength);
	dataReceiver(socket, tmpData, dataLength);
	tmpData[dataLength] = '\0';
	if (data != NULL) { strcpy(data, tmpData); }
}



 // Control session established 

int controlSess(int controlSocket, char *commandTag, int *dataPort, char* filename)
{
	char indata[MAX_PLLENGTH + 1];  
	char intag[TAG_LENGTH + 1];           
	char outdata[MAX_PLLENGTH + 1]; 
	char outtag[TAG_LENGTH + 1];          

	// Receive data port from client
	printf("  Receiving data port (FTP active mode) ...\n");
	packetReceiver(controlSocket, intag, indata);
	if (strcmp(intag, "DPORT") == 0) { *dataPort = atoi(indata); }

	// Receive command/filename
	printf("  Receiving command ...\n");
	packetReceiver(controlSocket, intag, indata);
	strcpy(commandTag, intag);
	strcpy(filename, indata);

	// Bad command line arg...
	if (strcmp(intag, "LIST") != 0 && strcmp(intag, "GET") != 0) {
		printf("  Transmitting command error ...\n");
		strcpy(outtag, "ERROR");
		strcpy(outdata, "Command must be either -l or -g");
		packetSender(controlSocket, outtag, outdata);
		return -1;
	}

	//...or go.
	else {
		printf("  Transmitting data-connection go-ahead ...\n");
		strcpy(outtag, "OKAY");
		packetSender(controlSocket, outtag, "");
		return 0;
	}
}



// Data session, get filenames, transmit

int dataSess(int controlSocket, int dataSocket, char *commandTag, char *filename)
{
	int ret = 0;     
	char **fileList; 
	int numFiles;    

	// Get list filenames in direct.
	fileList = getFileList(".", &numFiles);

	// Client requests filenames
	if (strcmp(commandTag, "LIST") == 0) {

		// Transfer filename
		printf("  Transmitting file listing ...\n");
		for (int i = 0; i < numFiles; i++) {
			packetSender(dataSocket, "FNAME", fileList[i]);
		}
	}

	// Requests file.
	else if (strcmp(commandTag, "GET") == 0) {
		do {
			char buffer[MAX_PLLENGTH + 1]; 
			int bytesRead; 
			int fileExists; 
			FILE *infile;  

			// See if exists...
			fileExists = 0;
			for (int i = 0; i < numFiles && !fileExists; i++) {
				if (strcmp(filename, fileList[i]) == 0) {
					fileExists = 1;
				}
			}

		
			if (!fileExists) {
				printf("  Transmitting missing-file error ...\n");
				packetSender(controlSocket, "ERROR", "File not found");
				ret = -1;
				break;
			}

			// Open
			infile = fopen(filename, "r");
			if (infile == NULL) {
				printf("  Transmitting file-read-access error ...\n");
				packetSender(controlSocket, "ERROR", "Unable to open file");
				ret = -1;
				break;
			}

			// Transfer filename.
			packetSender(dataSocket, "FILE", filename);

			// Transfer file.
			printf("  Transmitting file ...\n");
			do {
				bytesRead = fread(buffer, sizeof(char), MAX_PLLENGTH, infile);
				buffer[bytesRead] = '\0';
				packetSender(dataSocket, "FILE", buffer);
			} while (bytesRead > 0);
			if (ferror(infile)) {
				perror("fread");
				ret = -1;
			}

			//Close
			fclose(infile);

		} while (0);
	}

	// Commands "LIST" or "GET".
	else {
		fprintf(stderr, "ftserver: command-tag must be \"LIST\" or "
		        "\"GET\"; received \"%s\"\n", commandTag            );
		ret = -1;
	}

	
	packetSender(dataSocket, "DONE", "");

	
	printf("  Transmitting connection-termination go-ahead ...\n");
	packetSender(controlSocket, "CLOSE", "");

	// Close
	for (int i = 0; i < numFiles; i++) {
		free(fileList[i]);
	}
	free(fileList);

	return ret;
}


// Send data.
 
void dataSender(int socket, void *buffer, int numBytes)
{
	int ret;         
	int sentBytes;     

	// Send number bytes.
	sentBytes = 0;
	while (sentBytes < numBytes) {
		ret = send(socket, buffer + sentBytes, numBytes - sentBytes, 0);

		// Error or...
		if (ret == -1) {
			perror("send");
			exit(1);
		}

		// Send data
		else {
			sentBytes += ret;
		}
	}
}



 
 // Send packet from socket.
 
void packetSender(int socket, char *tag, char *data)
{
	unsigned short packetLength;        
	char tagBuffer[TAG_LENGTH];           

	// Send length.
	packetLength = htons(sizeof(packetLength) + TAG_LENGTH + strlen(data));
	dataSender(socket, &packetLength, sizeof(packetLength));

	// Send tag
	memset(tagBuffer, '\0', TAG_LENGTH);  
	strcpy(tagBuffer, tag);
	dataSender(socket, tagBuffer, TAG_LENGTH);

	// Send data...
	dataSender(socket, data, strlen(data));
}



 // Listen for connects

void startFtpServer(int port)
{
	int serverSocket;                 
	int status;                       
	struct sigaction interrupt;     
	struct sockaddr_in serverAddress; 

	// Server address.
	serverAddress.sin_family = AF_INET;         
	serverAddress.sin_port = htons(port);       
	serverAddress.sin_addr.s_addr = INADDR_ANY; 

	// Server socket.
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		perror("socket");
		exit(1);
	}

	// Bind Server  socket to listening port.
	status = bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
	if (status == -1) {
		perror("bind");
		exit(1);
	}

	// Listen for connect.
	status = listen(serverSocket, BACKLOG);
	if (status == -1) {
		perror("listen");
		exit(1);
	}

	// Interrupt signal handler
	interrupt.sa_handler = &sigHandler;
	interrupt.sa_flags = 0;
	sigemptyset(&interrupt.sa_mask);
	status = sigaction(SIGINT, &interrupt, 0);
	if (status == -1) {
		perror("sigaction");
		exit(1);
	}

	// FTP open...

	printf("ftserver: FTP server open on port %d\n", port);
	while (1) {
		char *clientIPv4;               
		char commandTag[TAG_LENGTH + 1];      
		char filename[MAX_PLLENGTH + 1]; 
		int controlSocket, dataSocket;     
		int dataPort;                       
		socklen_t addrLen;                  
		struct sockaddr_in clientAddress;   

		// Establish FTP control connection.
		addrLen = sizeof(struct sockaddr_in);
		controlSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &addrLen);
		if (controlSocket == -1) {
			perror("accept");
			exit(1);
		}
		clientIPv4 = inet_ntoa(clientAddress.sin_addr);
		printf("\nftserver: FTP control connection established with \"%s\"\n", clientIPv4);

		// FTP control connection.
		status = controlSess(controlSocket, commandTag, &dataPort, filename);

		// If success...
		if (status != -1) {
			int connectionAttempts;  // Number of data connection requests

			// Create server-side endpoint of FTP data connection.
			dataSocket = socket(AF_INET, SOCK_STREAM, 0);
			if (dataSocket == -1) {
				perror("socket");
				exit(1);
			}

			// Establish data connect
			clientAddress.sin_port = htons(dataPort);
			connectionAttempts = 0;
			do {
				status = connect(dataSocket, (struct sockaddr *) &clientAddress, sizeof(clientAddress));
			} while (status == -1 && connectionAttempts < MAX_CONNECTS);
			if (status == -1) {
				perror("connect");
				exit(1);
			}
			printf("ftserver: FTP data connection established with \"%s\"\n", clientIPv4);

			// Transfer file infor
			dataSess(controlSocket, dataSocket, commandTag, filename);

			// Wait for ack
			packetReceiver(controlSocket, NULL, NULL);

			// Close
			status = close(dataSocket);
			if (status == -1) {
				perror("close");
				exit(1);
			}
			printf("ftserver: FTP data connection closed\n");
		}
	}
}




//
//// 					MAIN
//


// Reads port number to create connection, then on to chat handler.


int main(int argc, char **argv)

{
	int port;  

	// Two command-line args used
	if (argc != 2) {
		fprintf(stderr, "usage: ftserver <server-port>\n");
		exit(1);
	}

	// Port must be integer check .
	if (!isStrInt(argv[1], &port)) {
		fprintf(stderr, "ftserver: Port must an integer\n");
		exit(1);
	}

	// Port must be in range [1024, 65535].
	if (port < 1024 || port > 65535) {
		fprintf(stderr, "ftserver: Port must be in range [1024, 65535]\n");
		exit(1);
	}

	// Run until sigint 
	startFtpServer(port);

	exit(0);

}





