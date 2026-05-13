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

#ifndef MORSE_H
#define MORSE_H

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

// class for Morse Tree array used during binary search tree construction
class Morse
{
public:
    char morseTree[63] =
            {
                    '\0',
                    'E',
                    'T',

                    'I', 'A',
                    'N', 'M',

                    'S', 'U', 'R', 'W',
                    'D', 'K', 'G', 'O',

                    'H', 'V', 'F', '\0', 'L', '\0', 'P', 'J',
                    'B', 'X', 'C', 'Y', 'Z', 'Q', '\0', '\0',

                    '5', '4', '\0', '3', '\0', '\0', '\0', '2', '\0', '\0', '+', '\0', '\0', '\0', '\0', '1',
                    '6', '=', '/', '\0', '\0', '\0', '\0', '\0', '7', '\0', '\0', '\0', '8', '\0', '9', '0'

            };
};


#endif
