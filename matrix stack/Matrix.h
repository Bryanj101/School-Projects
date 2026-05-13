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

#ifndef MATRIX_H
#define MATRIX_H

//includes for program functionality
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


// class and constructors for the Matrix
class Matrix
{
public:
    float data[4][4];
    Matrix(): data{{0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}}{}

    // functions for the Matrix class
    bool setValue(int index_x, int index_y , float value); //setValue function and its parameters

    Matrix Identity();

    Matrix RotX(float angle); //rotateX function and its parameters

    Matrix RotY(float angle); //rotateY function and its parameters

    Matrix RotZ(float angle); //rotateZ function and its parameters

    Matrix Translate(float x, float y, float z); //translate function and its parameters

    Matrix multiply(Matrix input); //multiply function and its parameters

};

#endif
