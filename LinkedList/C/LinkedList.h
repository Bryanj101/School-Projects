/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will take individual words inputted by a user and store them in a linked list. When the user inputs
 * STOP as a word, the program prints the stored words in reverse order of how they were originally inputted.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node struct and function definitions
struct Node // struct for node creation
{
    char *string;
    struct Node* next;
};
struct Node* head;
void display(struct Node* head); // display function and parameters
void add(struct Node** head, char* new_string); // add function and parameters
void clear(struct Node** head);
#endif //LINKEDLIST_H
