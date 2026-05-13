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

#include "Commands.h"

//main driver function for program to execute commands
int main()
{
    std::cout <<
              "COMMAND LIST\n"
              "---------------------------------------------------------------------------------\n"
              "constructTree <depth>: constructs binary search tree based on given integer depth\n"
              "convert <string>: converts given string to morse code\n"
              "inOrderTraversal: displays inOrderTraversal of tree\n"
              "preOrderTraversal: displays preOrderTraversal of tree\n"
              "postOrderTraversal: displays postOrderTraversal of tree\n"
              "clear: clears tree of all contents\n"
              "load: loads a text file and executes commands in given file if formatted like the command list\n"
              "exit: exits the program\n"
              "---------------------------------------------------------------------------------\n";
    processText(std::cin);
    return 0;
}
