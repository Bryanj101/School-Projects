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

#ifndef TESTPROGRAM3_BINARY_SEM_H
#define TESTPROGRAM3_BINARY_SEM_H
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
