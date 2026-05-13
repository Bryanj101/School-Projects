/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will take individual words inputted by a user and store them in a linked list. When the user inputs
 * STOP as a word, the program prints the stored words in reverse order of how they were originally inputted.
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <string>
#include <iostream>

class Node
{
public:
    std::string input; //string event stored in Node
    Node *next; // points to next node in the list
    Node(); // default constructors
    explicit Node(std::string); // constructor with string as parameter
};


class LinkedList
{
private:
    Node *head; // Pointed to the head Node

public:
    LinkedList();
    void add(const std::string& input); // function for adding node to list
    void display(std::ostream &os); // function for displaying contents of list
    void clear(); // function that clears list and frees memory
};




#endif

