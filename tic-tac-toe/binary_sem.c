/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will simulate a game of tic-tac-toe between two players using a fifo, shared memory, and semaphores.
 * If -1 is used as a command line argument player 1 is called and if -2 is used, player 2 is called. Player 1 goes first
 * and plays as X starting the center. Player 2 goes second and plays as O, which starts in a random corner. The game
 * continues until a player wins or a draw. The game should always result in a draw.
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