/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will spawn a child, open flowData.dat, and start timer to read a value every 5 seconds.
 * If value is between 450-550 it sends SIGUSR1 which warns user, if value is between 1450-1550 it sends SIGUSR2 which
 * warns user.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

// setting globals and union for reading file
union ISTR
{
    int val;
    char bytes[4];
};

int count = 0;
int warn = 0;
int inBytes = 0;
union ISTR in;
pid_t childPid;
time_t start = 0;
time_t end = 0;
int fd = 0;
char *filename = "flowData.dat";

// function for checking system call for errors
int checkCall(int val, const char *msg)
{
    if (val == -1)
    {
        if (errno == EINTR)
            return val;
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return val;
}
// function for output on child exit and closes file opened by child
void exitC(void)
{
    close(fd);
    char *out = "Child is exiting...\n";
    checkCall(write(STDOUT_FILENO, out, strlen(out)), "write");
}
// function for output on parent exit
void exitP(void)
{
    char *out = "Parent is exiting...\n";
    checkCall(write(STDOUT_FILENO, out, strlen(out)), "write");
}

// function for timer
void timerOn()
{
    struct itimerval tmr;
    tmr.it_value.tv_sec = 5;
    tmr.it_value.tv_usec = 0;
    tmr.it_interval.tv_sec = 5;
    tmr.it_interval.tv_usec = 0;
    checkCall(setitimer(ITIMER_REAL, &tmr, NULL), "timer");
}
// parent handler for signals
void signalHandlerP(int sig)
{
    pid_t p;
    char out[1024];
    // after receiving SIGCHILD parent waits for child before exiting
    if (sig == SIGCHLD)
    {
        while ((p = waitpid(-1, NULL, WNOHANG)) > 0);
        if (p == -1)
        {
            if (errno == ECHILD)
            {
                checkCall(write(STDOUT_FILENO,"Warning! Pressure control monitoring has been terminated, "
                                              "exiting the system.\n",78), "write");
                exit(EXIT_SUCCESS);
            }
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

    }
    // parent outputs upon receiving SIGUSR1
    // starts tracking time and stops tracking time on receiving SIGUSR1
    // finds difference between start and end to get time between alerts in seconds
    // if no prior warning flag is set then it will be 0 seconds since last alert
    if (sig == SIGUSR1)
    {
        time(&end);
        count = difftime(end, start) * warn;
        time(&end);
        sprintf(out, "WARNING! Low Pressure! It has been %d seconds since last alert.\n", count);
        checkCall(write(STDOUT_FILENO, out, strlen(out)), "write");
        time(&start);
        warn = 1;

    }
    // parent outputs upon receiving SIGUSR2
    // starts tracking time and stops tracking time on receiving SIGUSR2
    // finds difference between start and end to get time between alerts in seconds
    // if no prior warning flag is set then it will be 0 seconds since last alert
    if (sig == SIGUSR2)
    {
        time(&end);
        count = difftime(end, start) * warn;
        sprintf(out, "WARNING! High Pressure! It has been %d seconds since last alert.\n", count);
        checkCall(write(STDOUT_FILENO, out, strlen(out)), "write");
        time(&start);
        warn = 1;
    }
    if (sig == SIGINT)
    {
        // parent prompts user to exit upon a SIGINT
        // stops child process on interrupt prompt
        // continues after interrupt prompt
        // if user says no parent returns from prompt
        // if user says yes, parent sends SIGCHLD to process group and waits for child to terminate before exiting
        char user_exit[64];
        kill(childPid, SIGSTOP);
        while (1)
        {
            char *quest = "\nDo you want to exit (Y/n)?\n";
            checkCall(write(STDOUT_FILENO, quest, strlen(quest)), "write");
            checkCall(read(STDIN_FILENO, user_exit, sizeof(user_exit)), "read");
            kill(childPid, SIGCONT);
            if (strlen(user_exit) > 1) {
                if (user_exit[0] == 'Y' || user_exit[0] == 'y')
                {
                    killpg(getpid(), SIGCHLD);
                    wait(NULL);
                    exit(EXIT_SUCCESS);
                }
                if (user_exit[0] == 'n' || user_exit[0] == 'N')
                {
                    return;
                }
            }
        }
    }
}
// child handler for signals
void signalHandlerC(int sig)
{
    // child exits on SIGTERM signal
    if (sig == SIGTERM)
    {
        exit(EXIT_SUCCESS);
    }
    //every 5 seconds the timer will send a SIGALRM
    // SIGALRM will read bytes from the file to obtain a value
    // if value is between 450-550 it sends SIGUSR1, if value is between 1450-1550 it sends SIGUSR2
    // exits child
    if (sig == SIGALRM)
    {
        // initialize value
        in.val = 0;
        // read bytes from file to get value
        inBytes = checkCall(read(fd, in.bytes, 2), "read");
        // if value is between 450-550
        if (in.val <= 550 && in.val >= 450)
        {
            kill(getppid(), SIGUSR1);
        }
        // if value is between 1450-1550
        if (in.val >= 1450 && in.val <= 1550)
        {
            kill(getppid(), SIGUSR2);
        }
        // on EOF exit child
       if (inBytes == 0)
        {
            exit(EXIT_SUCCESS);
        }
    }
}

int main(int argc, char *argv[])
{
    // initializing structs and variables for program
    struct sigaction saP;
    struct sigaction saC;
    sigset_t mask;
    // initializing masks for parent signal handlers
    saP.sa_handler = signalHandlerP;
    sigemptyset(&saP.sa_mask);
    sigaddset(&saP.sa_mask, SIGCHLD);
    saP.sa_flags = 0;
    // initializing masks for child signal handlers
    saC.sa_handler = signalHandlerC;
    sigemptyset(&saC.sa_mask);
    saC.sa_flags = 0;
    // setting mask for blocking SIGINT
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    // sigaction handler for SIGCHLD for parent handler before fork
    checkCall(sigaction(SIGCHLD, &saP, NULL), "sigaction");
    // forking and making child
    switch (childPid = fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            // file descriptor to open and read file
            checkCall(fd = open(filename, O_RDONLY), "open");
            // blocking SIGINT in child using mask set
            sigprocmask(SIG_BLOCK, &mask, NULL);
            // sigaction handlers and error checking for child
            checkCall(sigaction(SIGTERM, &saC, NULL), "sigaction");
            checkCall(sigaction(SIGALRM, &saC, NULL), "sigaction");
            // timer starts
            timerOn();
            // when child exits
            atexit(exitC);
            // pauses until a signal
            while (1)
            {
                pause();
            }
            break;
        default:
            // when parent exits
            atexit(exitP);
            // sigaction handlers and error checking for parent
            checkCall(sigaction(SIGUSR1, &saP, NULL), "sigaction");
            checkCall(sigaction(SIGUSR2, &saP, NULL), "sigaction");
            checkCall(sigaction(SIGINT, &saP, NULL), "sigaction");
            // this while loop will echo anything a user types into the command line as it waits for alerts
            while (1)
            {
                char buf[1024];
                int numRead, numWrite;
                numRead = checkCall(read(STDIN_FILENO, buf, 1024), "read");
                if (numRead == -1)
                    continue;
                while (1)
                {
                    numWrite = checkCall(write(STDOUT_FILENO, buf, numRead), "write");
                    if (numWrite == -1)
                        continue;
                    else
                        break;
                }
            }
            break;
    }
    exit(EXIT_SUCCESS);
}