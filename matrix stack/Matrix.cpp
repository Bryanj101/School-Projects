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

//includes and inherits from Matrix header file
#include "Matrix.h"

/* function definitions for the Matrix class */
// function definition for setValue
    bool Matrix::setValue(int index_x, int index_y , float value)
    {
        if (index_x <= 3 && index_x >= 0 && index_y <= 3 && index_y >= 0)  // checks if input range falls within matrix size
        {
            data[index_x][index_y] = value;  //sets given element position to a specified value
            return true;
        }
        else
        {
            std::cout << "out of range" << std::endl;  //if element position is outside of matrix range
            return false;
        }
    }

    // function definition for creating an Identity Matrix
    Matrix Matrix::Identity()
    {
        Matrix tmp;
        tmp.setValue(0,0,1);
        tmp.setValue(1,1,1);
        tmp.setValue(2,2,1);
        tmp.setValue(3,3,1);
        return *this = tmp;
    }
    // function definition for rotateX
    Matrix Matrix::RotX(float angle)
    {
        Matrix tmp;
        angle = (angle * M_PI) / 180.0;
        tmp.setValue(0, 0, 1);
        tmp.setValue(1, 1, cosf(angle));
        tmp.setValue(1, 2, -sinf(angle));
        tmp.setValue(2, 1, sinf(angle));
        tmp.setValue(2, 2, cosf(angle));
        tmp.setValue( 3,3,1);
        return *this = tmp;
    }

    // function definition for rotateY
    Matrix Matrix::RotY(float angle)
    {
        Matrix tmp;
        angle = (angle * M_PI) / 180.0;
        tmp.setValue(0,0, cosf(angle));
        tmp.setValue(0,2, sinf(angle));
        tmp.setValue(2,0, -sinf(angle));
        tmp.setValue(2,2, cosf(angle));
        tmp.setValue(1,1,1);
        tmp.setValue(3,3,1);
        return *this = tmp;
    }

    // function definition for rotateZ
    Matrix Matrix::RotZ(float angle)
    {
        Matrix tmp;
        angle = (angle * M_PI) / 180.0;
        tmp.setValue(0,0, cosf(angle));
        tmp.setValue(0,1, -sinf(angle));
        tmp.setValue(1,0, sinf(angle));
        tmp.setValue(1,1, cosf(angle));
        tmp.setValue(2,2,1);
        tmp.setValue(3,3,1);
        return *this = tmp;
    }

    // function definition for translate
    Matrix Matrix::Translate(float x, float y, float z)
    {
        Matrix tmp;
        tmp.Identity();
        tmp.setValue(3, 0, x);
        tmp.setValue(3, 1, y);
        tmp.setValue(3, 2, z);
        return *this = tmp;
    }

    // function definition for multiplying matrices
    Matrix Matrix::multiply(Matrix input)
    {
        Matrix prod;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    prod.data[i][j] += data[i][k] * input.data[k][j];
                }
            }
        }
        return prod;
    }