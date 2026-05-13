/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will output blocks of characters generated based on character length pairings. The program will randomly
 * generate 10 to 20 blocks and will randomly generate a character A to Z and a length each character should repeat
 * between 2 and 10. The program will also generate a width value for each line. Each character-length block will be
 * printed and if the sum of each block's character length exceeds the width value a new line is started.
 */


#include "headers.h"

// defining child and parent value for semaphores
#define CHILD 0
#define PARENT 1

// struct for shared memory
struct mSeg
{
    int blocks;
    int length;
    char symbol;
};
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
// better rand function for generating random integers
int randInt(int low, int high)
{
    int rng = high - low + 1;
    double scl = (((double) rand()) / ((double) RAND_MAX + 1));
    int offset = scl * rng;
    return low + offset;
}

void child_func(struct mSeg *mem, int shmID, int semID)
{
    // attach shared memory to child
    mem = (struct mSeg *) shmat(shmID, NULL, 0);
    if (mem == (void*) -1) { checkCall(-1, "shmat"); }

    srand(time(NULL));
    reserveSem(semID, CHILD);
    // generate number of blocks for each character-length pairing
    mem->blocks = randInt(10, 20);
    // generate character-length pairings per number of blocks
    for (int i = 0; i < mem->blocks; i++)
    {
        mem[i].length = randInt(2, 10);
        mem[i].symbol = randInt(65, 90);
    }
    releaseSem(semID, PARENT);
    reserveSem(semID, CHILD);
    // detach child from shared memory
    shmdt(mem);
    releaseSem(semID, PARENT);
    // exit child
    exit(EXIT_SUCCESS);
}

void parent_func(struct mSeg *mem, int shmID, int semID)
{
    int width;
    int count = 0;
    // attach shared memory to parent
    mem = (struct mSeg *) shmat(shmID, NULL, 0);
    if (mem == (void*) -1) { checkCall(-1, "shmat"); }

    srand(time(NULL));
    reserveSem(semID,PARENT);

    // generate width length limit for each line
    width = randInt(10, 15);
    // loop for printing A-Z characters for number of blocks
    for (int i = 0; i < mem->blocks; i++)
    {
        // each character for a given length pairing
        for (int j = 0; j < mem[i].length; j++)
        {
            // if sum length of characters reaches width limit
            // start new line
            if (count >= width)
            {
                printf("\n");
                count = 0;
            }
            printf("%c", mem[i].symbol);
            count ++;
        }
    }
    printf("\n");

    releaseSem(semID, CHILD);
    reserveSem(semID, PARENT);
    // detach shared memory and delete shared memory and semaphore set
    shmdt(mem);
    checkCall(semctl(semID, IPC_RMID, 0), "semctl");
    checkCall(shmctl(shmID, IPC_RMID, NULL), "shmctl");
    // exit parent
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    int shmID, semID;
    int pid;
    struct mSeg *mem = NULL;
    mode_t perms = S_IRUSR | S_IWUSR;
    // creating and setting availability of semaphore set
    checkCall(semID = semget(IPC_PRIVATE, 2, IPC_CREAT | perms), "semget");
    initSemInUse(semID, PARENT);
    initSemAvailable(semID, CHILD);
    // creating shared memory
    checkCall(shmID = shmget(IPC_PRIVATE, sizeof(struct mSeg), IPC_CREAT | perms), "shmget");

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
        child_func(mem, shmID, semID);
    }
    // parent process
    else
    {
        parent_func(mem, shmID, semID);
    }
    exit(EXIT_SUCCESS);
}
