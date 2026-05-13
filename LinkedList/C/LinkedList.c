/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will take individual words inputted by a user and store them in a linked list. When the user inputs
 * STOP as a word, the program prints the stored words in reverse order of how they were originally inputted.
 */

#include "LinkedList.h"

void display(struct Node* head)  // methods for display function of the linked list
{
    struct Node *tmp = head;
    if (head == NULL)  // if list is already empty
    {
        printf("%s", "List is empty.\n");
        return;
    }
    else { printf("%s", "Reversed order of strings:\n"); }
    while (tmp != NULL) // prints list until list is exhausted
    {
        printf("%s\n", tmp->string);
        tmp = tmp->next;
    }

}

void add(struct Node** head, char* new_string) // methods for add function of the linked list
{
    struct Node* tmp = (struct Node*) malloc(sizeof(struct Node)); // allocate space for new node
    tmp->string  = malloc(strlen(new_string) + 1);
    strcpy(tmp->string, new_string);   // stores new string as new node's stored string data
    tmp->next = *head;  // next node is made the current head pointer
    *head = tmp;  // current head point is made the new node
}

void clear(struct Node** head)  // methods for display function of the linked list
{
    struct Node *tmp = *head;
    while (tmp != NULL) // frees memory of each node in the list until list is exhausted
    {
        *head = tmp->next;
        free(tmp);
        tmp = *head;
    }
    *head = NULL;  // sets head pointer to null
}

struct Node* head = NULL; // initialize head as NULL