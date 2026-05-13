/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will create 3 pthreads. Thread 1 will open data.dat, prompt the user for a number of integers,
 * prompt the user for integers, and write those integers to the file. Thread 2 and 3 will read the file for integers
 * larger and smaller than 100, respectively. If thread 2 finds a value larger it will increment a counter and if
 * thread 3 finds a value smaller it will increment a counter. Thread 2 and 3 will print the respective total count of
 * their counter. Thread 2 and 3 will also return their counter values to the main thread on exit.
 * The main thread prints the values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

// define buffer size and struct for thread values
#define BUF_SIZE 1024

struct t_Val
{
    int fd;
    int smaller;
    int larger;
    char out[BUF_SIZE];
    union
    {
        int val;
        char bytes[4];
    };
};

// define and initialize mutex and thread conditional
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int pred = 0; // predicate flag
char *filename = "data.dat"; // filename of file to create and read/write from


// error check function for pthread calls
void hndlError(int error, const char *str)
{
    if (error == 0)
        return;
    errno = error;
    perror(str);
    exit(EXIT_FAILURE);
}

// error check for system calls
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

// thread 1 function
// detaches itself prompts the user for a number of integers to be generated
// locks itself using a mutex and creates data.dat using filename
// prompts the user for integers to input and writes them to the file
// closes file and sets pred to 1, unlocks the mutex, broadcasts the condition to other threads
// exits and returns NULL
void *thread1_func()
{
    struct t_Val data;
    char num[BUF_SIZE];
    mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    int i = 0;

    hndlError(pthread_detach(pthread_self()), "pthread_detach");

    myPrint("Enter desired number of integers: ");
    checkCall(read(STDIN_FILENO, num, sizeof(num)), "read");

    hndlError(pthread_mutex_lock(&mtx), "pthread_lock");

    checkCall(data.fd = open(filename,  O_WRONLY | O_CREAT | O_TRUNC, perms), "open");

    while(i != strtol(num, NULL, 10))
    {
        sprintf(data.out, "Enter value %d: ", i + 1);
        myPrint(data.out);
        checkCall(read(STDIN_FILENO, data.out, BUF_SIZE), "read");
        data.val = strtol(data.out, NULL, 10);
        checkCall(write(data.fd, data.bytes, sizeof(int)), "write");
        i++;
    }

    close(data.fd);
    pred = 1;
    hndlError(pthread_mutex_unlock(&mtx), "pthread_unlock");
    pthread_cond_broadcast(&cond);

    pthread_exit(NULL);
}

// thread 2 function
// locks using a mutex and waits for condition signal
// upon receiving cond signal and setting pred flag to 1 the thread opens the file
// mutex is unlocked and thread reads the file of integers
// if an integer is above 100 the thread increments a counter by 1
// on EOF the thread closes the file, prints total number of integers larger than 100
// exits with return value of counter
void *thread2_func(void *arg)
{

    struct t_Val *data = (struct t_Val *)arg;
    int fRead;
    hndlError(pthread_mutex_lock(&mtx), "pthread_lock");

    while (pred == 0)
    {
        hndlError(pthread_cond_wait(&cond, &mtx), "pthread_cond");
    }

    checkCall(data->fd = open(filename, O_RDONLY), "open");
    hndlError(pthread_mutex_unlock(&mtx), "pthread_unlock");

    while (1)
    {
        data->val = 0;
        checkCall(fRead = read(data->fd, data->bytes, sizeof(int)), "read file");
        if (fRead == 0)
        {
            break;
        }
        if (data->val > 100)
        {
            data->larger++;
        }
    }

    close(data->fd);
    sprintf(data->out, "Total larger: %d\n", data->larger);
    myPrint(data->out);

    pthread_exit(&data->larger);
}

// thread 3 function
// locks using a mutex and waits for condition signal
// upon receiving cond signal and setting pred flag to 1 the thread opens the file
// mutex is unlocked and thread reads the file of integers
// if an integer is below 100 the thread increments a counter by 1
// on EOF the thread closes the file, prints total number of integers smaller than 100
// exits with return value of counter
void *thread3_func(void* arg)
{

    struct t_Val *data = (struct t_Val *)arg;
    int fRead;
    hndlError(pthread_mutex_lock(&mtx), "pthread_lock");

    while (pred == 0)
    {
        hndlError(pthread_cond_wait(&cond, &mtx), "pthread_cond");
    }

    checkCall(data->fd = open(filename, O_RDONLY), "open");
    hndlError(pthread_mutex_unlock(&mtx), "pthread_unlock");

    while (1)
    {
        data->val = 0;
        checkCall(fRead = read(data->fd, data->bytes, sizeof(int)), "read file");
        if (fRead == 0)
        {
            break;
        }
        if (data->val < 100)
        {
            data->smaller++;
        }
    }
    close(data->fd);
    sprintf(data->out, "Total smaller: %d\n", data->smaller);
    myPrint(data->out);

    pthread_exit(&data->smaller);
}

int main()
{
    // initialize structs and values to be passed to threads
    struct t_Val t2;
    struct t_Val t3;
    t2.larger = 0;
    t3.smaller = 0;
    // initialize number of threads in an array
    pthread_t thread[3];
    // create each thread and pass the necessary references to them
    hndlError(pthread_create(&thread[1], NULL, thread2_func, &t2), "pthread_create");
    hndlError(pthread_create(&thread[2], NULL, thread3_func, &t3), "pthread_create");
    hndlError(pthread_create(&thread[0], NULL, thread1_func, NULL), "pthread_create");
    // join threads 2 and 3 to main
    hndlError(pthread_join(thread[1], NULL), "pthread_join");
    hndlError(pthread_join(thread[2], NULL), "pthread_join");
    // print the final values of larger and smaller returned by threads and exit
    printf("larger: %d\nsmaller: %d\n", t2.larger, t3.smaller);
    exit(EXIT_SUCCESS);
}