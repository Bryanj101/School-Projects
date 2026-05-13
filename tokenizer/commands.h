/*Student Name: Bryan Johnson
Student NetID: btj117
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
manipulate a doubly linked list.
*/

#ifndef COMMANDS_H
#define COMMANDS_H

// includes List header and inherits its functionality
#include "List.h"

using namespace std;

// class for command processing
class commands
{
public:
    bool processText(istream&, bool interactive = true); // processing text function and its values
};


#endif //COMMANDS_H
