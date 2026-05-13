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

#ifndef STACK_H
#define STACK_H

//includes and inherits from Matrix header file
#include "Matrix.h"
#include <iostream>


// class and constructors for Nodes
class Node
{
public:
    Matrix data;
    Node* next;
    Node(): data(), next(nullptr){}
    explicit Node(Matrix data): data(data), next(nullptr){}
};


// class and constructors for the Stack
class Stack
{
private:
    Node* top;
public:
    Stack(): top(nullptr){}

    void push(Matrix data); //push function and its parameters

    bool peek(Matrix &data); //peek function and its parameters

    bool pop(); //pop function and its parameters

    bool Transform(float x, float y, float z, float w = 1); //transform function and its parameters
};

#endif
