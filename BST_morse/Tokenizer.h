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

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <sstream>
#include <string>

using std::istream;
using std::stringstream;
using std::string;


class Tokenizer
{
private:
    stringstream ss;
public:
    Tokenizer() { ss.exceptions(std::ios::failbit); }
    Tokenizer(const string& source) { ss.str(source); ss.exceptions(std::ios::failbit); }

    void setString(const string& str);
    bool isEmpty() const;
    bool readLine(string& line);
    bool readInteger(int& val);
    bool readWord(string& val);
    bool readDouble(double& val);
    bool readChar(char& val);

    void rewind();
    void clear();
};


#endif
