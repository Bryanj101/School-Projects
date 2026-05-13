/*Student Name: Bryan Johnson
Student NetID: btj117
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
manipulate a doubly linked list.
*/

// including commands header, inheriting all necessary functionality for program
#include "commands.h"

//executes main body to initialize program
int main()
{
    commands cmd;
    cout << "Input load and the path of the file to load the file and execute the commands in it." << endl;
    cmd.processText(cin);
    return 0;
}