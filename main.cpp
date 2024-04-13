#include <ctype.h>
#include <errno.h>
#include <iostream> 
#include <stdio.h> 
#include <string.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h> 

void CreatePipe(int process[])
{
    if( pipe(process) < 0 )
    {
        std::cerr << "CreatePipe() failed...\n";
        exit(EXIT_FAILURE);
    }
}

void Write(int pipe[], char output[], const int &SIZE, int &n_bytes)
{
    if( n_bytes = write(pipe[1], output, SIZE) < 0 )
    {
        std::cerr << "Write() failed...\n";
        exit(EXIT_FAILURE);        
    }
}

void Read(int pipe[], char input[], const int &SIZE, int &n_bytes)
{
    memset(input, 0, SIZE);
    if( n_bytes = read(pipe[0], input, SIZE) < 0 )
    {
        std::cerr << "Read() failed...\n";
        exit(EXIT_FAILURE);            
    }
}

int main(int argc, char *argv[])
{
    const int SIZE = 30;
    char message[] = "This is some message.";
    char response[] = "OK... response here.";

    bool is_running;
    char bufferA[SIZE];
    char bufferB[SIZE];

    int pipeA[2];        
    int pipeB[2];        
    int pid; 
    int n_bytes;
    // int length = strlen(message) + 1;

    // create pipes
    CreatePipe(pipeA);
    CreatePipe(pipeB);

    // create children
    pid = fork();

    // parent process
    if( pid > 0 )
    {
        Write(pipeA, message, SIZE, n_bytes);
        Read(pipeB, bufferA, SIZE, n_bytes);
        std::cout << "Parent received -> " << bufferA << std::endl;
    }
    else
    {
        Read(pipeA, bufferB, SIZE, n_bytes);
        std::cout << "Child received -> " << bufferB << std::endl;
        Write(pipeB, response, SIZE, n_bytes);
    }

    return EXIT_SUCCESS;
}