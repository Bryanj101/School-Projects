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

//includes and inherits from Stack header file
#include "Stack.h"

/* function definitions for the Stack class */

    //function definition for push
    void Stack::push(Matrix data)
    {
        Node *tmp = new Node(data);
        tmp->next = top;
        top = tmp;
    }

    //function definition for peek
    bool Stack::peek(Matrix &data)
    {
        if (top == nullptr)
            return false;
        data = top->data;

        return true;
    }

    //function definition for pop
    bool Stack::pop()
    {
        Node *tmp = top;
        if (top == nullptr)
            return false;
        top = top->next;
        delete tmp;
        return true;
    }

    //function definition for transformation
    bool Stack::Transform(float x, float y, float z, float w)
    {
        float vec[4] = {x, y, z, w};
        Matrix transform;
        Matrix prod;
        peek(prod);
        pop();

        while(peek(transform))    //loops until stack is empty and pops on each loop
        {
            prod = prod.multiply(transform); //product of all matrices in stack
            pop();
        }

        std::cout << "Final vertex: ";

        for (int i = 0; i < 3; i++)
        {
            float final = 0;

            for (int j = 0; j < 4; j++)
            {
                // final vertex = vector multiplied by product of all matrices in stack
                final += vec[j] * prod.data[j][i];
            }
            std::cout << std::setprecision(3) << final << "   ";   // value output precision is first 3

        }
        std::cout << std::endl;
        return true;
    }
