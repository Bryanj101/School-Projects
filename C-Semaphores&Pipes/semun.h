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

#ifndef TESTPROGRAM3_SEMUN_H
#define TESTPROGRAM3_SEMUN_H

union semun
{
    int val; /* Value for SETVAL */
    struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

#endif
