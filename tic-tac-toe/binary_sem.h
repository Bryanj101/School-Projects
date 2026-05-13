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

#ifndef PROGRAM4_BINARY_SEM_H
#define PROGRAM4_BINARY_SEM_H
# include <errno.h>
#include <sys/types.h>
#include <sys/sem.h>
#include "semun.h"

extern int bsUseSemUndo;
extern int bsRetryOnEintr;

int initSemAvailable (int semId, int semNum);
int initSemInUse (int semId, int semNum);
int reserveSem (int semId, int semNum);
int releaseSem (int semId, int semNum);

#endif
