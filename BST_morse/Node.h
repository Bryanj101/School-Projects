/*
Student Name: Bryan Johnson
Student NetID: btj117
Date: 10/20/2020
Compiler Used: Clion using mingw
Program Description:
This program will execute commands or load a text file and will tokenize it in order to find commands. If the program
finds a command it attempts to execute the given command. The given commands associated with this program will be used
to create and implement a binary search tree. This program will be able to traverse the tree in inorder, preorder, and
postorder. The binary search tree will hold characters and element positions for the purpose of converting a string to
morse code. When the user commands the program to convert a string it will convert the string to morse code based on the
traversal of the string.
*/

#ifndef NODE_H
#define NODE_H

#include "Morse.h"
#include "Tokenizer.h"


//implements Node class for binary search tree nodes
class Node {
public:
    int data;
    char morse;
    Node *left;
    Node *right;

    Node() : morse('\0'), data(0), left(nullptr), right(nullptr) {}
    explicit Node(char _morse, int _data) : morse(_morse), data(_data), left(nullptr), right(nullptr) {}

    //function for determining the degree of current tree
    int degree() const {
        int deg = 0;
        if (left != nullptr)    //if parent has left child +1 degree
            deg++;
        if (right != nullptr)
            deg++;             //if parent has right child +1 degree
        return deg;
    }
};

#endif
