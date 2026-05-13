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

#ifndef BST_H
#define BST_H

#include "Node.h"

class BST
{
private:
    Morse morseObject;
    Node* root;
    bool insert(Node* &node, char _morse, int _data);   //inserts a new node into the binary search tree
    bool remove(Node* &node, int _data);                //removes a node from the binary search tree
    void postorder(Node* &node, std::ostream& os);      //displays tree in post-order
    void preorder(Node* &node, std::ostream& os);       //displays tree in pre-order
    void inorder(Node* &node, std::ostream& os);        //displays tree in in-order
    void destroy(Node* &node);                          //deletes all nodes in tree
    bool find(Node* node, int &_data, std::ostream& os);    //finds a specific node in tree
    bool findChar(Node* node, char _morse);                 //finds a specific character in a node in tree
    void construct(int depth);                          //constructs the binary search tree based on given depth

    //public functions for binary search tree class
    //these functions will call the private ones of the same name
public:
    BST(): root(nullptr){}
    ~BST();
    bool insert(char morse, int data);
    bool remove(int data);
    bool find(int &data, std::ostream& os);
    bool findChar(char morse);
    void inorder(std::ostream& os);
    void postorder(std::ostream& os);
    void preorder(std::ostream& os);
    void destroy();
    void constructTree(int depth);

};
#endif
