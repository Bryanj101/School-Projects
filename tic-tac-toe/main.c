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


#include "headers.h"

#define PLAYER1 0
#define PLAYER2 1

int fifo;
int fd;
char *filename = "xoSync";
mode_t perms = S_IRUSR | S_IWUSR;

// struct for shared memory
struct mSeg
{
    int counter;
    char board[3][3];
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
// initialize game state with empty board and counter set to 0
void EmptyBoard (struct mSeg *arg)
{
    arg->counter = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arg->board[i][j] = 0;
        }
    }
}
// function for displaying current state of the board
void DisplayBoard (struct mSeg *arg)
{
    char obx[4] = "O X";
    printf("%2c |%2c |%2c", obx[1 + arg->board[0][0]], obx[1 + arg->board[0][1]], obx[1 + arg->board[0][2]]);
    printf("\n---|---|---\n");
    printf("%2c |%2c |%2c", obx[1 + arg->board[1][0]], obx[1 + arg->board[1][1]], obx[1 + arg->board[1][2]]);
    printf("\n---|---|---\n");
    printf("%2c |%2c |%2c\n\n", obx[1 + arg->board[2][0]], obx[1 + arg->board[2][1]], obx[1 + arg->board[2][2]]);
}

// function for checking whether a player has won
// checks rows and diagonals for 3 in a row
void CheckWin (struct mSeg *arg, int player, int win_val)
{
    int row_sum;
    int column_sum;
    int dia1_sum;
    int dia2_sum;
    // loop to check if a player has won by checking rows, columns, and diagonals
    for (int i = 0; i < 3; i++)
    {
        row_sum = 0;
        column_sum = 0;
        dia1_sum = 0;
        dia2_sum = 0;
        for (int j = 0; j < 3; j++)
        {
            row_sum += arg->board[i][j];
            dia1_sum += arg->board[j][j];
            dia2_sum += arg->board[2 - j][j];
            column_sum = arg->board[0][j] + arg->board[1][j] + arg->board[2][j];

            if (row_sum == win_val || dia1_sum == win_val || dia2_sum == win_val || column_sum == win_val)
            {
                arg->counter = -1;
                printf("Player %d wins!\n", player);
                return;
            }
            // if not a win and a free space still exists the game continues
            if (arg->board[i][j] == 0)
            {
                return;
            }
        }

    }
    printf("Draw! \n");
    arg->counter = -1;
}

void player1Move (struct mSeg *arg)
{
    // starting move for player 1 is to pick the center
    if (arg->counter == 0) { arg->board[1][1] = 1; return;}
    // checks middle column for win condition
    if (arg->board[0][1] == 0 && arg->board[2][1] == 1) { arg->board[0][1] = 1; return; }
    if (arg->board[2][1] == 0 && arg->board[0][1] == 1) { arg->board[0][1] = 1; return; }
    // checks rows and columns for priority spaces to block
    for (int i = 0; i < 3; i++)
    {
        if (arg->board[i][0] == 0 && arg->board[i][1] == -1 && arg->board[i][2] == -1) { arg->board[i][0] = 1; return; }
        if (arg->board[i][0] == -1 && arg->board[i][1] == 0 && arg->board[i][2] == -1) { arg->board[i][1] = 1; return; }
        if (arg->board[i][0] == -1 && arg->board[i][1] == -1 && arg->board[i][2] == 0) { arg->board[i][2] = 1; return; }
        if (arg->board[0][i] == 0 && arg->board[1][i] == -1 && arg->board[2][i] == -1) { arg->board[0][i] = 1; return; }
        if (arg->board[0][i] == -1 && arg->board[1][i] == 0 && arg->board[2][i] == -1) { arg->board[1][i] = 1; return; }
        if (arg->board[0][i] == -1 && arg->board[1][i] == -1 && arg->board[2][i] == 0) { arg->board[2][i] = 1; return; }
    }
    // check current board and pick priority space for win possibility
    if (arg->board[2][2] == -1  && arg->board[0][0] == 0 && arg->board[1][2] == 0 && arg->board[0][1] == 0)
    {
        arg->board[0][2] = 1;
        return;
    }
    // check current board and pick priority space for win possibility
    if (arg->board[0][0] == -1  && arg->board[2][1] == 0) { arg->board[2][1] = 1; return; }
    if (arg->board[0][1] == -1 && arg->board[1][0] == 0) { arg->board[1][0] = 1; return; }
    // if no other space has priority check for free space to take
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arg->board[i][j] == 0)
            {
                arg->board[i][j] = 1;
                return;
            }
        }
    }
}

void player2Move (struct mSeg *arg)
{
    int start;
    // player 2's first move is to pick a random corner
    if (arg->counter == 0)
    {
        start = rand() % 4;
        if (start == 0) { arg->board[0][0] = -1; }
        if (start == 1) { arg->board[0][2] = -1; }
        if (start == 2) { arg->board[2][0] = -1; }
        if (start == 3) { arg->board[2][2] = -1; }
        return;
    }

    // checking diagonals to block
    if (arg->board[0][0] == 1 && arg->board[2][2] == 0) { arg->board[2][2] = -1; return; }
    if (arg->board[0][2] == 1 && arg->board[2][0] == 0) { arg->board[2][0] = -1; return; }
    if (arg->board[2][2] == 1 && arg->board[0][0] == 0) { arg->board[0][0] = -1; return; }
    if (arg->board[2][0] == 1 && arg->board[0][2] == 0) { arg->board[0][2] = -1; return; }

    // row and column blocking loop to stop opponent win
    for (int i = 0; i < 3; i++)
    {
        if (arg->board[i][0] == 0 && arg->board[i][1] == 1 && arg->board[i][2] == 1) { arg->board[i][0] = -1; return; }
        if (arg->board[i][0] == 1 && arg->board[i][1] == 0 && arg->board[i][2] == 1) { arg->board[i][1] = -1; return; }
        if (arg->board[i][0] == 1 && arg->board[i][1] == 1 && arg->board[i][2] == 0) { arg->board[i][2] = -1; return; }
        if (arg->board[0][i] == 0 && arg->board[1][i] == 1 && arg->board[2][i] == 1) { arg->board[0][i] = -1; return; }
        if (arg->board[0][i] == 1 && arg->board[1][i] == 0 && arg->board[2][i] == 1) { arg->board[1][i] = -1; return; }
        if (arg->board[0][i] == 1 && arg->board[1][i] == 1 && arg->board[2][i] == 0) { arg->board[2][i] = -1; return; }
    }
    // if no other space has priority check for free space to take
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arg->board[i][j] == 0)
            {
                arg->board[i][j] = -1;
                return;
            }
        }
    }

}
// function for player 1
// player 1 will create a fifo if one does not exist
// randomly generated keys will be generated for the shared memory and semaphore
// the semaphores are created and attached
// player 1 will create shared memory using the struct mem and attaches it
// the fifo is opened by player 1 for write
// keys are written to the fifo and the fifo is closed
// the board is initialized as blank
// player 1 enters the gameplay loop
// once game is over player 1 checks that fifo is clear
// detaches shared memory
// deletes shared memory and semaphores
void player1()
{

    int shmID, semID;
    key_t shmK, semK;
    int rand1, rand2;

    struct mSeg *mem;

    rand1 = rand() % 10000;
    rand2 = rand() % 10000;

    fifo = mkfifo(filename, perms);
    if (fifo == -1)
    {
        if (errno != EEXIST)
        {
            perror("fifo failure");
            exit(EXIT_FAILURE);
        }
    }

    shmK = ftok(filename, rand1);
    semK = ftok(filename, rand2);

    checkCall(shmID = shmget(shmK, sizeof(struct mSeg), perms | IPC_CREAT), "shmget");
    checkCall(semID = semget(semK, 2, perms | IPC_CREAT), "semget");

    initSemInUse(semID, PLAYER2);
    initSemAvailable(semID, PLAYER1);

    mem = (struct mSeg *) shmat(shmID, NULL, 0);
    if (mem == (void*) -1) { checkCall(-1, "shmat"); }

    checkCall(fd = open(filename, O_WRONLY), "opening");
    checkCall(write(fd, &rand1, sizeof(int)), "write fifo");
    checkCall(write(fd, &rand2, sizeof(int)), "write fifo");
    close(fd);

    EmptyBoard(mem);
    // gameplay loop
    // if a player won the loop ends
    // otherwise reserves semaphore for player 1, displays player 2's move except on first turn
    // player 1 moves, displays the board, increments counter, and checks for player 1 win,
    // releases player 2 semaphore
    while (mem->counter > -1)
    {

        reserveSem(semID, PLAYER1);
        if (mem->counter >= 1)
        {
            printf("Player 2 Move:\n");
        }
        DisplayBoard(mem);
        player1Move(mem);
        printf("Player 1 Move:\n");
        DisplayBoard(mem);
        CheckWin(mem, 1, 3);
        releaseSem(semID, PLAYER2);
    }

    checkCall(fd = open(filename, O_WRONLY), "opening");
    close(fd);
    shmdt(mem);
    checkCall(shmctl(shmID, IPC_RMID, NULL), "shmctl");
    checkCall(semctl(semID, IPC_RMID, 0), "semctl");
}

// function for player 2
// player 2 will create a fifo if one does not exist
// randomly generated keys will be retrieved for the shared memory and semaphore
// the semaphore set is retrieved
// player 2 will retrieve shared memory and attaches it
// the fifo is opened by player 2 for read
// keys are read from the fifo and the fifo is closed
// player 2 enters the gameplay loop
// once game is over player 2 checks that fifo is clear
// detaches shared memory
void player2()
{
    int shmID, semID;
    key_t shmK, semK;
    int rand1, rand2;

    struct mSeg *mem;

    fifo = mkfifo(filename, perms);
    if (fifo == -1)
    {
        if (errno != EEXIST)
        {
            perror("fifo failure");
            exit(EXIT_FAILURE);
        }
    }

    checkCall(fd = open(filename, O_RDONLY), "opening");
    checkCall(read(fd, &rand1, sizeof(int)), "write fifo");
    checkCall(read(fd, &rand2, sizeof(int)), "write fifo");
    close(fd);

    shmK = ftok(filename, rand1);
    semK = ftok(filename, rand2);

    checkCall(shmID = shmget(shmK, 0, 0), "shmget");
    checkCall(semID = semget(semK, 0, 0), "semget");

    mem = (struct mSeg *) shmat(shmID, NULL, 0);
    if (mem == (void *) - 1) checkCall(-1, "shmat");

    // gameplay loop
    // reserves semaphore for player 2, displays player 1's move, if player 1 won the loop breaks
    // otherwise player 2 moves, displays the board, increments counter, and checks for player 2 win,
    // releases player 1 semaphore
    while (1)
    {
        reserveSem(semID, PLAYER2);
        printf("Player 1 Move:\n");
        DisplayBoard(mem);
        if (mem->counter == -1)
        {
            break;
        }
        player2Move(mem);
        printf("Player 2 Move:\n");
        DisplayBoard(mem);
        mem->counter++;
        CheckWin(mem, 2, -3);
        releaseSem(semID, PLAYER1);
    }

    checkCall(fd = open(filename, O_RDONLY), "opening");
    close(fd);
    shmdt(mem);
}

// main
int main(int argc, char *argv[])
{
    // seed rand
    srand(time(NULL));
    // if command line argument is -1 then player 1 is called
    if (!strcmp(argv[1], "-1"))
    {
        printf("Starting game...\n");
        player1();
        return 0;
    }
    // if command line argument is -2 then player 2 is called
    if (!strcmp(argv[1], "-2"))
    {
        printf("Starting game...\n");
        player2();
        return 0;
    }
    exit(EXIT_SUCCESS);
}
