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

#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"

// function for processing text to parse and execute commands
bool processText(istream& is, bool interactive = true)
{
    // implement support for
    // exit ... exit the program
    // load file ... loads a file containing supported commands
    // constructTree ... constructs a binary search tree based on depth
    // convert ... converts given string into morse code
    // preOrderTraversal ... displays pre-order traversal of the tree
    // postOrderTraversal ... displays post-order traversal of the tree
    // inOrderTraversal ... displays in-order traversal of the tree
    // clear ... clears content of the tree

    string line;
    string command;
    string arg1, arg2;
    char carg1;
    char* carray = &arg1[0];
    int iarg1;
    double darg1, darg2;
    Tokenizer tkn;
    BST bst;



    //Enters control loop...
    while (true)
    {
        if (!interactive)
        {
            if (is.eof())
                return true;
        }
        else
        {
            std::cout << ">>";
        }

        //gets line from input stream
        getline(is, line);
        tkn.setString(line);

        //first word in stream should always be a command
        tkn.readWord(command);

        //Below we start checking if the command is recognized

        // exits program and does some clean up
        if (command == "exit")
        {
            std::cout << "Exiting ...." << std::endl;
            bst.destroy();
            return false;
        }

        if (command == "load")
        {
            // load expects a filename ... so read one more word
            if (!tkn.readWord(arg1))
            {
                std::cout << "Missing file name" << std::endl;
                continue; // skip back to the top of the read loop
            }

            // checks for spaces in file path and appends for full path
            if (tkn.readLine(arg2))
            {
                arg1 = arg1.append(arg2);
            }

            //Attempts to read input file
            std::ifstream fin;
            bool status = true;
            fin.open(arg1);
            if (fin.is_open())
            {
                status = processText(fin, false);
            }
            else
            {
                std::cout << "Failed to open the file" << std::endl;
            }
            fin.close();
            if (!status)
                return false;
        }

        // condition if constructTree is given as input
        if (command == "constructTree")
        {
            if (tkn.readInteger(iarg1))
            {
                bst.constructTree(iarg1);
            }
            else
            {
                std::cout << "Error! Expected an integer..." << "\n";
            }

        }

        // condition if convert is given as input
        if (command == "convert")
        {
            // attempts to convert string to uppercase and convert it into morse
            if (tkn.readWord(arg1))
            {
                if (tkn.readLine(arg2))
                {
                    arg1 = arg1.append(arg2);
                }
                for(char & i : arg1)
                {
                    i = toupper(i);
                }
                std::cout << arg1 << " converted" << '\n';
                for (int j = 0; j < arg1.length(); j++) {
                    bst.findChar(carray[j]);
                }

            }
            else
                std::cout << "Error! Expected a word..." << "\n";

        }

        // condition if preOrderTraversal is given as input
        if (command == "preOrderTraversal")
        {
            // attempts to display preOrderTraversal
            if (!tkn.readWord(arg1))
            {
                std::cout << "pre-order traversal:";
                bst.preorder(std::cout << '\n');
                std::cout << '\n';
            }
            else
            {
                std::cout << "Error! Expected only command..." << "\n";
            }

        }

        // condition if postOrderTraversal is given as input
        if (command == "postOrderTraversal")
        {
            // attempts to display postOrderTraversal
            if (!tkn.readWord(arg1))
            {
                std::cout << "post-order traversal:";
                bst.postorder(std::cout << '\n');
                std::cout << '\n';
            }
            else
            {
                std::cout << "Error! Expected only command..." << "\n";
            }

        }

        // condition if inOrderTraversal is given as input
        if (command == "inOrderTraversal")
        {
            // attempts to display inOrderTraversal
            if (!tkn.readWord(arg1))
            {
                std::cout << "in-order traversal:";
                bst.inorder(std::cout << '\n');
                std::cout << '\n';
            }
            else
            {
                std::cout << "Error! Expected only command..." << "\n";
            }

        }

        // condition if clear is given as input
        if (command == "clear")
        {
            // attempts to clear tree of contents
            if (!tkn.readWord(arg1))
            {
                std::cout << "Clearing tree.." << '\n';
                bst.destroy();
            }
            else
            {
                std::cout << "Error! Expected only command..." << "\n";
            }

        }
        if (command.empty())
        {
            std::cout << "Enter a command..." << std::endl;
        }
    }

}

#endif
