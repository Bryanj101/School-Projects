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

// binary semaphore functions to be used with tic-tac-toe program
#include "binary_sem.h"

int bsUseSemUndo = 0;
int bsRetryOnEintr = 1;

int initSemAvailable (int semId, int semNum)
{
    union semun arg;
    arg.val = 1;
    return semctl(semId, semNum, SETVAL, arg);
}
int initSemInUse (int semId, int semNum)
{
    union semun arg;
    arg.val = 0;
    return semctl(semId, semNum, SETVAL, arg);
}
int reserveSem (int semId, int semNum)
{
    struct sembuf sops;

    sops.sem_num = semNum;
    sops.sem_op = -1;
    sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;
    while (semop(semId, &sops, 1) == -1)
    {
        if (errno != EINTR || !bsRetryOnEintr)
            return -1;
    }
    return 0;
}
int releaseSem (int semId, int semNum)
{
    struct sembuf sops;

    sops.sem_num = semNum;
    sops.sem_op = 1;
    sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;
    return semop(semId, &sops, 1);
}