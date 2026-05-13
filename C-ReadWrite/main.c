/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will read lines from two files containing questions and answers. It will read these files one line at a
 * time on a 30 sec timer. The user will be asked to input an answer to each question. The program will compare the user
 * inputted answer to the one in the answer text file and records if it is correct or not.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 1024 // defining buffer size to be used with char arrays

static int timed; // declare a static timed variable to be used as a flag

// check call function to check for system call errors
void checkCall(int val, const char *msg)
{
    if (val == -1)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}
// a printing function using the write system call to output a string to the terminal
int myPrint(const char* str)
{
    ssize_t print;
    print = write(STDOUT_FILENO, str, strlen(str));
    if (print == -1)
    {
        perror("write");
        return 0;
    }
    return 1;
}
// similar to myPrint, but converts an integer to a string
int myPrintInt(const int val)
{
    ssize_t printInt;
    char val_str[BUF_SIZE];
    sprintf(val_str, "%d", val); // converts integer to string
    printInt = write(STDOUT_FILENO, val_str, strlen(val_str));
    if (printInt == -1)
    {
        perror("write");
        return 0;
    }
    return 1;
}
// signal handler function
void sigHandler(int sig)
{
    // If the signal received is SIGINT, handle it with this function
    if (sig == SIGINT)
    {
        char tmp[BUF_SIZE];
        while(1)
        {
            // prompts user during interrupt with an exit prompt
            checkCall(write(STDOUT_FILENO, "\nDo you want to exit Y/n ? ", 27), "write");
            checkCall(read(STDIN_FILENO, tmp, sizeof(tmp)), "read");
            if (strcmp(tmp, "Y\n") == 0) // user inputs Y the program exits with exit success flag
            {
                exit(EXIT_SUCCESS);
            }
            if (strcmp(tmp, "n\n") == 0) // user inputs n the program continues
            {
                return;
            }
        }

    }
    // if the signal received is SIGALRM, handle it with this
    if (sig == SIGALRM)
    {
        timed = 1; // sets timed flag to 1
    }
}

// function for reading a line from text file
int readLine(int fd, char* line)
{
    int i = 0;
    line[0] = '\0';
    while (read(fd, &line[i], 1)) // reads line byte by byte
    {
        if (line[i] == '\n' || line[i] == '\r') // detects a line break and returns string
        {
            line[i] = 0;
            return 1;
        }
        if (fd == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return 0; // if no characters read returns 0
}
// function for reading the paired question and answer lines from text files
int readQA(int questFd, int ansFd, char *quest, char *ans)
{
    if (readLine(questFd, quest) == 0) return 0;
    if (readLine(ansFd, ans) == 0) return 0;
    return 1;
}

int main(int argc, char* argv[])
{
    // declaring structs for signal handler, active timer, and delayed timer
    struct sigaction hndlr;
    struct itimerval tvOn;
    struct itimerval tvOff;

    int numRead = 0;
    int numWrite = 0;
    int question = 1;
    int correct = 0;

    char buf[BUF_SIZE];
    char quest[BUF_SIZE];
    char ans[BUF_SIZE];

    int questFd; int ansFd;

    // declaring sigaction struct to handle signals in sigHandler function
    hndlr.sa_handler = sigHandler;
    // initializing mask as an empty set and adding SIGINT and SIGALRM to mask
    sigemptyset(&hndlr.sa_mask);
    sigaddset(&hndlr.sa_mask, SIGINT);
    sigaddset(&hndlr.sa_mask, SIGALRM);
    // setting sigaction flags to none
    hndlr.sa_flags = 0;

    // initializing timer values for tvOn active timer
    tvOn.it_interval.tv_sec = 0;
    tvOn.it_interval.tv_usec = 0;
    tvOn.it_value.tv_sec = 30;
    tvOn.it_value.tv_usec = 0;

    // initializing timer values for tvOff delayed timer
    tvOff.it_interval.tv_sec = 0;
    tvOff.it_interval.tv_usec = 0;
    tvOff.it_value.tv_sec = 0;
    tvOff.it_value.tv_usec = 0;

    // set actions for SIGINT AND SIGALRM to be handled by signal handler
    checkCall(sigaction(SIGINT, &hndlr, NULL), "sigaction");
    checkCall(sigaction(SIGALRM, &hndlr, NULL), "sigaction");
    // open questions and answers files to read
    checkCall(questFd = open("quest.txt", O_RDONLY), "opening");
    checkCall(ansFd = open("ans.txt", O_RDONLY), "opening");
    // if no characters are read from a file, user is informed and files are closed and exits with exit failure flag
    if (readQA(questFd, ansFd, quest, ans) == 0)
    {
        myPrint("Empty file\n");
        close(questFd);
        close(ansFd);
        exit(EXIT_FAILURE); // exit failure since the program failed to read any characters and can't continue
    }
    // main loop for program to handle questions and answers
    while(1)
    {
        myPrint("#");
        myPrintInt(question);
        myPrint(" ");
        myPrint(quest);
        myPrint("? ");
        timed = 0; // timed flag set to 0 since timer is not active
        // activates timer of 30 sec
        checkCall(setitimer(ITIMER_REAL, &tvOn, NULL), "setitimer");
        numRead = read(STDIN_FILENO, buf, sizeof(buf)); // reads user input
        if (numRead == 0) {break;}
        if (numRead == -1)
        {
            // if read returns -1 it checks for signal interrupt error number as a part of program functionality
            if (errno == EINTR)
            {
                // if timed flag is set to 1 do this, exits loop if EOF after timer goes off
                if (timed)
                {
                    myPrint("\nTime's up next question\n");
                    if (readQA(questFd, ansFd, quest, ans) == 0)
                    {
                        break;
                    }
                    question++;
                }
                // if error is not caused by signal interrupt do read error message and exit
                if (errno != EINTR)
                {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                continue;
            }
        }
        // setting timer to delayed timer as checking user input takes time
        checkCall(setitimer(ITIMER_REAL, &tvOff, NULL), "setitimer");
        // conditionals to check if user input was correct or not
        buf[numRead - 1] = 0;
        if (strcmp(buf, ans) == 0) {
            correct++;
            myPrint("correct\n");
        }
        if (strcmp(buf, ans) != 0)
        {
            myPrint(ans);
            myPrint("\nwrong\n");
        }
        // reads next pair of questions and answers from text files, unless EOF
        if(readQA(questFd, ansFd, quest, ans) == 0) {break;}
        question++;
    }
    // once main loop reaches EOF the final score is printed
    myPrint("Out of questions\n");
    myPrint("Final score is: ");
    myPrintInt(correct);
    myPrint(" out of ");
    myPrintInt(question);
    myPrint("\n");
    // files are closed
    close(questFd);
    close(ansFd);
    // program exits with exit success flag
    exit(EXIT_SUCCESS);
}
