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

//includes and inheriting from Commands header file
#include <iostream>
#include "Commands.h"

//main function to execute program
int main()
{
    commands cmd;
    cmd.processText(std::cin);
}
