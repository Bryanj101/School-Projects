/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will take individual words inputted by a user and store them in a linked list. When the user inputs
 * STOP as a word, the program prints the stored words in reverse order of how they were originally inputted.
 */

#include "LinkedList.h"

int main()
{

    char *input;  // sets char array
    input = (char*)malloc (sizeof (char)); // dynamic allocation
    printf("%s", "This program will read a string entered by the user until STOP is entered.\n");
    while(strcmp(input, "STOP") != 0)    // while user has not inputted STOP loop will run
    {
        printf("%s", "Enter a word:"); // user prompt to enter a word
        scanf("%s", input);  // sets input variable as user entered string
        if (strcmp(input, "STOP") != 0) { add(&head, input); } // if input is not STOP, word added to list
    }
    display(head);  // displays content of linked list starting at head, reverse order of original input
    clear(&head); // clears list and frees allocated memory
    free(input);  // frees allocated memory



    exit(EXIT_SUCCESS); // exit program

}
