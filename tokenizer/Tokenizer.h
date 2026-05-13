/*Student Name: Bryan Johnson
Student NetID: btj117
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
manipulate a doubly linked list.
*/

#ifndef TOKENIZER_H
#define TOKENIZER_H

// includes to be inherited by other headers in program
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
    bool readDouble(double& val); // read double function and its parameters
    bool readChar(char& val); // read character function and its parameters

    void rewind(); // rewind function
    void clear(); // clear function
};

#endif //TOKENIZER_H
