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

#ifndef PROGRAM4_SEMUN_H
#define PROGRAM4_SEMUN_H

union semun
{
    int val; /* Value for SETVAL */
    struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

#endif
