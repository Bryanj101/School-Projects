/*
Student Name: Bryan Johnson
Student NetID: btj117
Date: 9/27/2020
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
implement a transformation stack. The matrix in the transformation stack can cann add rotation matrices around the
x,y,z axes and translation matrices along the axes based on the given command. When the transformation command is
inputted the stack executes the transformation based on the given vector to provide a final vertex.
*/

#ifndef TOKENIZER_H
#define TOKENIZER_H

//includes program functionality and inherits from Stack header file
#include "Stack.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


using std::istream;
using std::stringstream;
using std::string;

// Tokenizer class and its functions
class Tokenizer
{
private:
    stringstream ss;
public:
    // default constructors
    Tokenizer() { ss.exceptions(std::ios::failbit); }
    Tokenizer(const string& source) { ss.str(source); ss.exceptions(std::ios::failbit); }

    void setString(const string& str); // set string function and its parameters
    bool isEmpty() const; // check empty function
    bool readLine(string& line); // read line function and its parameters
    bool readInteger(int& val); // read int function and its parameters
    bool readWord(string& val); // read word function and its parameters
    bool readFloat(float& val); // read float function and its parameters
    bool readFloats(float& val, float& val1, float& val2); // read double function and its parameters
    bool readChar(char& val); // read character function and its parameters

    void rewind(); // rewind function
    void clear(); // clear function
};

#endif
