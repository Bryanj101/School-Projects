#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will use a parent and child process to handle the output of a cat execution for a given file. The child
 * process will exec a cat call for a given file and redirect the STDOUT and write it to a pipe. The parent process will
 * read the pipe and output the contents by writing to STDOUT.
 */

// error checking function for system calls
int checkCall(int val, const char *msg)
{
    if (val == -1)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return val;
}

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;

    if (argc < 2)
    {
        printf("Please provide a filename...\n");
        exit(EXIT_FAILURE);
    }

    pipe(fd);
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    // error checking for fork failure
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // child process
    if (pid == 0)
    {
        // array for exec args
        char *arg[] = {"cat", NULL};
        // close read end of pipe
        close(fd[0]);
        // redirecting STDOUT
        dup2(fd[1], STDOUT_FILENO);
        // redirecting error out
        dup2(fd[1], STDERR_FILENO);
        // loop to allow for multiple file arguments
        for (int i = 1; i < argc; i++)
        {
            arg[i] = argv[i];
            arg[i + 1] = NULL;
        }
        // execute cat on files provided in arguments
        checkCall(execvp("cat", arg), "exec");
        // close write end of pipe and exit child
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    // parent process
    else
    {
        int numRead = 0;
        char input[1024];
        // close write end pipe
        close(fd[1]);
        // read pipe and write contents to STDOUT
        while(checkCall(numRead = read(fd[0], input, sizeof(input)), "read pipe") > 0)
        {
            checkCall(write(STDOUT_FILENO, input, numRead), "write output");
        }
        // close read end of pipe and exit parent
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
