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

// include files for tic-tac-toe program
#ifndef PROGRAM4_HEADERS_H
#define PROGRAM4_HEADERS_H
#include "binary_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>







#endif
