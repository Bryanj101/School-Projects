/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will spawn 3 children. Child 1 will open data.dat, prompt the user for a number of integers,
 * prompt the user for integers, and write those integers to the file. Child 2 and 3 will read the file for integers
 * larger and smaller than 100. If child 2 finds a value larger it will increment a counter and if child 3 finds a value
 * smaller it will increment a counter. The parent will also receive a SIGUSR1 or SIGUSR2 if larger or smaller values are found
 * and increment respective counters. After all children exit the total larger and smaller counts are printed, as well as
 * the count from the parent.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

// defining buffer size and union for writing to file
#define BUF_SIZE 1024

union ISTR
{
    int val;
    char bytes[4];
};

// declaring globals and setting filename
pid_t child1;
pid_t child2;
pid_t child3;
char *filename = "data.dat";
int fd;
int fBytes;
int larger, smaller;
int large_flag, small_flag;
union ISTR in;
char out[BUF_SIZE];

// error function for system call
int checkCall(int val, const char *msg)
{
    if (val == -1)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return val;
}
// write to STDOUT convenience function
void myPrint(const char* str)
{
    checkCall(write(STDOUT_FILENO, str, strlen(str)), "write");
}
// parent signal handler
// handles SIGCHLD and SIGUSR1 and SIGUSR2
void signalHandlerP(int sig)
{
    pid_t p;
    // after receiving SIGCHILD parent waits for children before exiting
    // when child 1 exits SIGUSR1 and SIGUSR2 are sent to child 2 and 3 respectively
    if (sig == SIGCHLD) {
        while ((p = waitpid(-1, NULL, WNOHANG)) > 0)
        {
            if (p == child1)
            {
                kill(child2, SIGUSR1);
                kill(child3, SIGUSR2);
            }
        }

        if (p == -1)
        {
            if (errno == ECHILD)
            {
                sprintf(out, "larger: %d\nsmaller: %d\n", larger, smaller);
                myPrint(out);
                exit(EXIT_SUCCESS);
            }
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
    // parent increments larger var by 1 upon receiving SIGUSR1
    if (sig == SIGUSR1)
    {
        larger++;
    }
    // parent increments smaller var by 1 upon receiving SIGUSR2
    if (sig == SIGUSR2)
    {
        smaller++;
    }
}
// child signal handler
// handlers SIGUSR1 and SIGUSR2
void signalHandlerC(int sig)
{
    // upon receiving SIGUSR1 child will set large flag to 1
    if (sig == SIGUSR1)
    {
        large_flag = 1;
    }
    // upon receiving SIGUSR2 child will set small flag to 1
    if (sig == SIGUSR2)
    {
        small_flag = 1;
    }
}

// child 1 function
// prompts user for the number of integers to write to file
// creates and opens file using filename
// prompts user for an integer to write to file
// once complete closes file and exits child 1
void child1_func()
{
    int i = 0;
    char num[BUF_SIZE];
    char num_in[BUF_SIZE];
    mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

    myPrint("Enter number of desired integers: ");
    checkCall(read(STDIN_FILENO, num, BUF_SIZE), "read");

    checkCall(fd = open(filename,  O_WRONLY | O_CREAT | O_TRUNC, perms), "open");

    while(i != strtol(num, NULL, 10))
    {
        sprintf(out, "Enter value %d: ", i + 1);
        myPrint(out);
        checkCall(read(STDIN_FILENO, num_in, BUF_SIZE), "read");
        in.val = strtol(num_in, NULL, 10);
        checkCall(write(fd, in.bytes, sizeof(int)), "write");
        i++;
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
// child 2 function
// waits until receiving SIGUSR1 and large flag has been set to 1
// afterwards opens file to read
// reads file and increments larger var for each integer larger than 100
// each integer found larger than 100 also sends SIGUSR1 to parent
// on EOF closes file and prints total number of larger integers found
void child2_func()
{
    struct sigaction saC;

    saC.sa_handler = signalHandlerC;
    sigemptyset(&saC.sa_mask);
    saC.sa_flags = 0;

    checkCall(sigaction(SIGUSR1, &saC, NULL), "sigaction");

    while (large_flag == 0)
    {
        pause();
    }

    checkCall(fd = open(filename, O_RDONLY), "open");

    while (1)
    {
        in.val = 0;
        checkCall(fBytes = read(fd, in.bytes, sizeof(int)), "reading file");
        if (fBytes == 0)
        {
            break;
        }
        if (in.val > 100)
        {
            larger++;
            kill(getppid(), SIGUSR1);
        }
    }

    close(fd);
    sprintf(out, "Total larger: %d\n", larger);
    myPrint(out);

    exit(EXIT_SUCCESS);
}
// child 3 function
// waits until receiving SIGUSR2 and large flag has been set to 1
// afterwards opens file to read
// reads file and increments smaller var for each integer larger than 100
// each integer found smaller than 100 also sends SIGUSR2 to parent
// on EOF closes file and prints total number of larger integers found
void child3_func()
{
    struct sigaction saC;

    saC.sa_handler = signalHandlerC;
    sigemptyset(&saC.sa_mask);
    saC.sa_flags = 0;

    checkCall(sigaction(SIGUSR2, &saC, NULL), "sigaction");

    while (small_flag == 0)
    {
        pause();
    }
    checkCall(fd = open(filename, O_RDONLY), "open");
    while (1)
    {
        in.val = 0;
        checkCall(fBytes = read(fd, in.bytes, sizeof(int)), "reading file");
        if (fBytes == 0)
        {
            break;
        }
        if (in.val < 100)
        {
            smaller++;
            kill(getppid(), SIGUSR2);
        }
    }
    close(fd);
    sprintf(out, "Total smaller: %d\n", smaller);
    myPrint(out);
    exit(EXIT_SUCCESS);
}
// function for forking and passing argument to a child
// the child functions will be passed to the children created by this function
pid_t hndlFork(void (*child)(void))
{
    pid_t p;
    p = fork();
    if (p == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (p == 0)
    {
        child();
    }
    return p;
}

int main()
{
    struct sigaction saP;

    saP.sa_handler = signalHandlerP;
    sigemptyset(&saP.sa_mask);
    saP.sa_flags = 0;
    // setting sigaction for SIGCHLD for parent handler as a precaution
    checkCall(sigaction(SIGCHLD, &saP, NULL), "sigaction");
    // forking child 2 and 3
    child2 = hndlFork(child2_func);
    child3 = hndlFork(child3_func);
    // setting sigaction for SIGUSR1 and SIGUSR2 for parent handler
    checkCall(sigaction(SIGUSR1, &saP, NULL), "sigaction");
    checkCall(sigaction(SIGUSR2, &saP, NULL), "sigaction");
    // forking child 1
    child1 = hndlFork(child1_func);
    // parent waits until signal
    while (1)
    {
        pause();
    }

    exit(EXIT_SUCCESS);
}
