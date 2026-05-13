/*Student Name: Bryan Johnson
Student NetID: btj117
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
manipulate a doubly linked list.
*/

#ifndef LIST_H
#define LIST_H

#include "Tokenizer.h"

// class for Node values and its functions
class Node
{
public:
    std::string event; //string event stored in Node
    int time; // integer time stored in Node
    Node *next; // Pointed to the NEXT Node
    Node *prev; // Pointed to the PREV Node

    Node(); //default constructors
    Node(std::string, int); //constructor with data as parameter
};

// class for List values and its functions
class List
{
private:
    Node *head; // Pointed to the HEAD Node
    Node *tail; // Pointed to the TAIL Node
public:
    List(); // default constructor
    void prepend_list(std::string, int); // prepend list function and its parameters

    void append_list(std::string, int); // append list function and its parameters

    void display(std::ostream &); // display function and its parameters

    void display_until(std::ostream &, int); // display until function and its parameters

    void length(std::ostream &); // length function and its parameters

    bool remove(const std::string&); // remove function and its parameters

    void clear(); // clear function and its parameters

    bool search(const std::string&); // search function and its parameters

    void insert_before(std::string, int, const std::string&); // insert before function and its parameters

    void insert_after(const std::string&, int, const std::string&); // insert after function and its parameters

};

#endif //LIST_H
