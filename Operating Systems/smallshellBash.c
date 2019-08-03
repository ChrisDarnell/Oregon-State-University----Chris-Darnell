// Author: Chris Darnell
// Date: 3/3/2017
// CS344 - Project 3
// Title: smallsh.c

// Description: a shell for use in bash. Uses re-entrancy, built-in commands, pid, dir open/create.

// Output format taken from assignment prompt. 


///
////                            LIBRARIES
///

#include <string.h>    
#include <sys/stat.h>  
#include <sys/types.h> 
#include <sys/wait.h>  
#include <unistd.h>  
#include <signal.h> 
#include <errno.h>     
#include <fcntl.h>    
#include <limits.h>    
#include <stdio.h>    
#include <stdlib.h>    
  


///
////                             VARIABLE DEFINITIONS
///


// Your shell must support command lines with a maximum length of 2048 characters, and a maximum of 512 arguments

// Arrays to hold bg, fg, completed proc.


#define DEBUG                   0 
#define MAXIMUMARGUMENTS        512 
#define MAXIMUMLENGTH           2048 
#define MAX_PIDS                1000 
typedef enum { false, true } bool;
int backgroundIndex = 0;
int currentProc = 0;                  
int signalNum = 0;
pid_t backgroundPid[MAX_PIDS];         
pid_t pidComplete[MAX_PIDS]; 
pid_t foregroundPid = INT_MAX;        





///
////                             FUNCTION PROTOTYPES
///


void signalBackground(int sig, siginfo_t* info, void* vp);
void signalForeground();





///
////                                  MAIN
///





int main(int argc, char** argv)

{

// Variables used in main

    
    pid_t childPid;
    int backgroundExit;
    int backgroundStatus; 
    int exitStatus;
    int fd;
    int fd2;
    int i;
    int j;
    int numberArguments;
    int status;
    bool checkBackground = false;
    bool checkRepeat = true;
    char *args[MAXIMUMARGUMENTS + 1];
    char input[MAXIMUMLENGTH];
    char *token;
  

// Struct background

    struct sigaction backgroundStr;
    backgroundStr.sa_sigaction = signalBackground;     
    backgroundStr.sa_flags = SA_SIGINFO|SA_RESTART;
    sigfillset(&(backgroundStr.sa_mask));
    sigaction(SIGCHLD, &backgroundStr, NULL);

//Struct foreground

    struct sigaction foregroundStr;
    foregroundStr.sa_handler = signalForeground;
    foregroundStr.sa_flags = SA_RESTART;
    sigfillset(&(foregroundStr.sa_mask));
    sigaction(SIGINT, &foregroundStr, NULL); 

// Struct Ignore Signal

    struct sigaction otherStr_act;
    otherStr_act.sa_handler = SIG_IGN;
    otherStr_act.sa_flags = SA_RESTART;
    sigfillset(&(otherStr_act.sa_mask));
    sigaction(SIGINT, &otherStr_act, NULL); 


// Allocate memory, init arrays for background

// Pointer array to arguments

// Init argument array

 
    for (i = 0; i < MAX_PIDS; i++)
    
    {

        pidComplete[i] = backgroundPid[i] = INT_MAX;
    
    }   

    
    for (i = 0; i <= MAXIMUMARGUMENTS; i++)
    
    {

        args[i] = (char *) malloc((MAXIMUMLENGTH + 1) * sizeof(char)); 
    
    }  

    do
    
    {
  
        char **next = args;


        for (i = 0; i <= MAXIMUMARGUMENTS; i++)
    
        {

            strcpy(args[i], "\n");
    
        }

    
        strcpy(input, "\0");
 
        i = 0;

    
        while (i < MAX_PIDS && pidComplete[i] != INT_MAX)
        
        {
            if (DEBUG) 
            
            {
                printf("Now cleaning up process %d\n", pidComplete[i]);
            
            }

    
            pidComplete[i] = waitpid(pidComplete[i], &backgroundStatus, 0);

// Display status/PID

            if (WIFEXITED(backgroundStatus)) 
           
            {

                backgroundExit = WEXITSTATUS(backgroundStatus);
                printf("background pid %d is done: exit value %d.\n", pidComplete[i], backgroundExit);
           
            }
            
            else
            
            {

                backgroundExit = WTERMSIG(backgroundStatus);
                printf("background pid %d is done: terminated by signal %d\n", pidComplete[i], backgroundExit);
 
            }


// Remove once done...

            j = 0;
            while (j < MAX_PIDS && backgroundPid[j] != INT_MAX)
            { 
                if (backgroundPid[j] == pidComplete[i])
                
                {

                    
                    if (DEBUG)
                    
                    {

                        printf("Now removing process %d from array.\n", backgroundPid[j]);
                    
                    }  

//...move array contents to compensate for removed entry                 

            
                    backgroundPid[j] = INT_MAX;
 
                    int k = j;                       
                    while (k + 1 < MAX_PIDS && backgroundPid[k+1] != INT_MAX)
                    
                    {

                        backgroundPid[k] = backgroundPid[k+1];
                        backgroundPid[k+1] = INT_MAX;
                        k++;
                    
                    }    
                    
                    currentProc--; 

                }
             
                j++;

            }


            pidComplete[i] = INT_MAX;

    
            i++; 
        }

// Be sure you flush out the output buffers each time you print, as the text that you're outputting may not reach 
        // the screen until you do in this kind of interactive program. To do this, call fflush() immediately after each 
        // and every time you output text.


// Reset/flush...


        backgroundIndex = 0;


        fflush(stdin);
        fflush(stdout);

// Use the colon : symbol as a prompt for each command line

    
        printf(": ");

    
        fgets(input, MAXIMUMLENGTH, stdin);

    
        fflush(stdin);

    
        if (input[0] == '\n' || input[0] == '\0')
        
        {
         
            continue;
        
        }
 
// Process input from user...


        numberArguments = 0;
        token = strtok(input, " "); 

        if (DEBUG)
        
        {

            printf("token is %s\n", token); 
        
        }

    
        while (token != NULL && numberArguments < MAXIMUMARGUMENTS)  
        
        {

 
           
            if (strlen(token) == 0)
            
            {
               
                continue;
           
            }   

            if (DEBUG)
            
            {
               
                printf("overwriting %s with %s\n", *next, token);
            
            }

// Add to arg array


            strcpy(*next, token);

            if (DEBUG)
            
            {
                
                printf("args[%d] is: %s\n", numberArguments, args[numberArguments]); 
            
            }

        
            numberArguments++;
 
// Next...
            token = strtok(NULL, " ");

    
            if (token != NULL)
            {
                *next++;
            } 
        }

        if (DEBUG)
        {
            printf("overwriting %s", *next);
        }

   
        token = strtok(*next, "\n"); 
        if (token != NULL)
        {
            strcpy(*next, token);
        }

        if (DEBUG)
        {
            printf(" with %s\n", *next);
            printf("args[%d] is: %s\n", numberArguments - 1, args[numberArguments - 1]); 
        }


// If background...

        if (strcmp(args[numberArguments - 1], "&") == 0)
        
        {
           
            checkBackground = true;

         
            numberArguments--; 

            
        }

        else

        {
           
            *next++;
       
        }

        if (DEBUG)
        
        {

            printf("overwriting %s with NULL\n", *next);
        
        }

        if (strncmp(args[0], "#", 1) == 0)
        
        {

// Finally, your shell should allow blank lines and comments. Any line that begins with the # character is a comment 
// line and should be ignored (mid-line comments, such as the C-style, will not be supported). A blank line (one 
//     without any commands) should also do nothing. Your shell should just re-prompt for another command when it 
// receives either a blank line or a comment line.
        
        }

        else if (strcmp(args[0], "exit") == 0)
        
        {

// Exit signal --> free memory
            
            i = 0;
            while (i < MAX_PIDS && backgroundPid[i] != INT_MAX)
            
            {
                if (DEBUG)
                
                {

                    printf("Now killing process %d\n", backgroundPid[i]);
               
                }
 
                kill(backgroundPid[i], SIGKILL);
                i++;
            
            }

            for (i = 0; i <= MAXIMUMARGUMENTS; i++)
            {
                if (DEBUG)
                {
                    printf("Now freeing memory for args[%d], which has a value of %s\n",i, args[i]);
                } 
                free(args[i]); 
            }  

// Exit point...


            checkRepeat = false;

        }
        else if (strcmp(args[0], "cd") == 0)
        
        {
            if (numberArguments == 1)
            
            {
             
                chdir(getenv("HOME"));
            
            }

// Directory handling...input from assignment
            
            else
            
            {

                chdir(args[1]);
            
            }
            
        }

// Print...
        
        else if (strcmp(args[0], "status") == 0)
        
        {

            if (WIFEXITED(status))
            
            {
             
                exitStatus = WEXITSTATUS(status);
                printf("exit value %d\n", exitStatus);
            
            }

            else if (signalNum != 0)
           
            {
              

                printf("terminated by signal %d\n", signalNum);
            } 

       
        }

       
        else 

// Child handling...

        {
            
            childPid = fork();

            if (childPid == 0) 
            
            {
               
                bool checkStatus = false; 
                bool pathInput = false;
                bool pathOutput = false;
                int inputOffset = 0;
                int outputOffset = 0;

// Resets flag/pushes to dir

                if (numberArguments > 4 && strcmp(args[numberArguments-4], "<") == 0)
                
                {

                    if (DEBUG)
                    
                    {
                        
                        printf("1) input pathed to %s\n", args[numberArguments-3]);     
                   
                    }

                
                    pathInput = true;

                  
                    inputOffset = 3; 
                }

                else if (numberArguments > 2 && strcmp(args[numberArguments-2], "<") == 0)
                
                {
                    
                    if (DEBUG)
                    
                    {
                       
                        printf("2) input pathed to %s\n", args[numberArguments-1]);     
                    
                    }

                 \
                    pathInput = true;

                   
                    inputOffset = 1; 
                }

                if (numberArguments > 4 && strcmp(args[numberArguments-4], ">") == 0)
                
                {
                    if (DEBUG)
                    
                    {
                     
                        printf("3) output pathed to %s\n", args[numberArguments-3]);     
                    
                    }
 
                
                    pathOutput = true;

                  
                    outputOffset = 3; 
                }

                
                else if (numberArguments > 2 && strcmp(args[numberArguments-2], ">") == 0)
                
                {

                    if (DEBUG)
                   
                    {

                        printf("4) output pathed to %s\n", args[numberArguments-1]);     
                    }
 
            
                    pathOutput = true;

                
                    outputOffset = 1; 
                }

            
                if (checkBackground == true && pathInput == false)
                
                {

                    fd = open("/dev/null", O_RDONLY);

                    checkStatus = true;      
                }

                else if (pathInput == true)
                
                {

                    fd = open(args[numberArguments - inputOffset], O_RDONLY);

                    checkStatus = true;  
                
                }


// Error Messaging

                if (checkStatus == true)
                {
                    if (fd == -1)
                    {
                        printf("smallsh: cannot open %s for input\n", args[numberArguments - inputOffset]);
                        exit(1); 
                    }

                    fd2 = dup2(fd, 0);
                    if (fd2 == -1)
                    {
                        printf("smallsh: cannot open %s for input\n", args[numberArguments - inputOffset]);
                        exit(1);
                    }   
                }

                if (pathOutput == true)
                {
                    fd = open(args[numberArguments - outputOffset], O_WRONLY|O_CREAT|O_TRUNC, 0644);

                    if (fd == -1)
                    {
                        printf("smallsh: cannot open %s for output\n", args[numberArguments - outputOffset]);
                        exit(1); 
                    }

                    fd2 = dup2(fd, 1);
                    if (fd2 == -1)
                    {
                        printf("smallsh: cannot open %s for output\n", args[numberArguments - outputOffset]);
                        exit(1);
                    }   
                }

// Compare to find largest...


                i = 0;
                if (inputOffset > outputOffset)
                {
                    i = inputOffset + 1;
                }
                else if (outputOffset > inputOffset)
                {
                    i = outputOffset + 1;
                }

              
                for (j = i; j > 0; j--)
                {
                    *next--;
                }

             
                *next = NULL;

          
                execvp(args[0], args);

// Bad filename from assignment

                printf("%s", args[0]);
                fflush(NULL);
                perror(" ");  
 
                exit(1); 
            }

// Parent proc, error if no fork

// Print PID, if background...

//...then reset for next pass, add to background array


            else if (childPid == -1) 
            
            {


                printf("%s", args[0]);
                fflush(NULL);                 
                perror(" ");
            
            } 

            else

            {
               

            
                if (checkBackground == true)
                
                {

                  
                    printf("background pid is %d\n", childPid);

                
                    checkBackground = false;

                   
                    if (currentProc < MAX_PIDS)
                    
                    { 

                        backgroundPid[currentProc++] = childPid;
                    
                    }
                
                } 

                else

// Set interrupt, reset once no active foreground
                
                {
            
                    signalNum = 0;                     

                   
                    foregroundPid = childPid;

               
                    sigaction(SIGINT, &foregroundStr, NULL);

      
                    foregroundPid = waitpid(foregroundPid, &status, 0);

               
                    sigaction(SIGINT, &otherStr_act, NULL);

               
                    foregroundPid = INT_MAX;


// 
                    if (signalNum != 0)
                    {
                        printf("terminated by signal %d\n", signalNum);
                    }   
                }
            }
        }

    }

// Your shell should just re-prompt for another command when it receives either a blank line or a comment line

    while(checkRepeat == true);

    return 0;
}




///
////                                    FUNCTIONS
///







// If a child foreground process is killed by a signal, the parent must immediately print out the number of the signal 
// that killed it's foreground child process (see the example) before prompting the user for the next command.
   
// Background processes should also not be terminated by a SIGINT signal. They will terminate themselves, continue running, 
// or be terminated when the shell exits (see below)

// Check if signal is from foreground proc...

//...if not, add to background array for main




void signalBackground(int sig, siginfo_t* info, void* vp)

{
    if (DEBUG)
    
    {
        printf("In signalBackground.\n");
    
    }

    pid_t referringPid = info->si_pid; 


    if (referringPid != foregroundPid && backgroundIndex < MAX_PIDS)
    
    {

        pidComplete[backgroundIndex++] = referringPid;
    
    } 

    return;

}


// Make sure that SIGINT does not terminate your shell, but only terminates the foreground command if one is 
// running. To do this, you'll have to create the appropriate signal handlers with sigaction(). 
// The parent should not attempt to terminate the foreground child process when the parent receives a SIGINT signal: 
// instead, the foreground child (if any) must terminate itself on receipt of this signal.

// If interrupt signaled...

// ...kill foreground process (if any), ignore interrupt for other proc.

// return

void signalForeground()

{

    if (foregroundPid != INT_MAX)
    
    {
        kill(foregroundPid, SIGKILL);
        signalNum = 2;  
    }  

   
    return;

}