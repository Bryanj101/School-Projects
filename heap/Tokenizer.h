/*
Student Name: Bryan Johnson
Student NetID: btj117
Date: 11/14/2020
Compiler Used: Clion using mingw
Program Description:
This program will execute commands or load a text file and will tokenize it in order to find commands. If the program
finds a command it attempts to execute the given command. The given commands associated with this program will be used
to create and implement a preemptive scheduling queue. This program will schedule tasks, add scheduled tasks to a
priority queue, and increment through both the priority queue and schedule via time steps.
*/

#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <istream>
#include <vector>
#include <algorithm>
#include <iomanip>

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



#endif //HEAP_TOKENIZER_H
