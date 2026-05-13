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

//includes and inherits from Commands header file
#include "Commands.h"


bool commands::processText(istream& is, bool interactive)
{
    // implement commands and support for
    // exit ... exit the program
    // rotateX ... adds a rotation matrix around the x-axis based on angle given
    // rotateY ... adds a rotation matrix around the y-axis based on angle given
    // rotateZ ... adds a rotation matrix around the z-axis based on angle given
    // translate ... adds a translation matrix along the x,y,z axes based on values given
    // transformVertex ... executes transformation stack based on given vector and returns a final vertex
    // undo ... removes the current matrix on the top of the transformation stack

    string line;
    string command;
    string arg;
    string arg1;
    string var;
    int int_arg;
    float float_arg;
    float float_arg1;
    float float_arg2;
    Tokenizer tkn;
    Matrix mtx;
    Stack stk;


    std::cout << "Input commands to perform transformation stack operations.\n"
                 "Command List\n"
                 "---------------------------------------------------------------------------------\n"
                 "rotateX <angle>: adds a rotation matrix around the z-axis based on angle inputted\n"
                 "rotateY <angle>: adds a rotation matrix around the z-axis based on angle inputted\n"
                 "rotateZ <angle>: adds a rotation matrix around the z-axis based on angle inputted\n"
                 "translate <x, y, z>: adds a translation matrix along x,y,z axes based on values inputted\n"
                 "transformVertex <x, y, z>: "
                 "transforms the matrix and gives a final vertex of x,y,z axes based on values inputted\n"
                 "undo: removes the most recent matrix in the stack\n"
                 "load: loads a text file and executes commands in given file if formatted like the command list\n"
                 "exit: exits the program\n"
                 "---------------------------------------------------------------------------------\n";


    //Enters control loop...
    while (true)
    {
        if (!interactive)
        {
            if (is.eof())
                return true;
        }
        else
        {
            std::cout << ">>";
        }

        //gets line from input stream
        getline(is, line);
        tkn.setString(line);

        //first word in stream should always be a command
        tkn.readWord(command);

        //Below we start checking if the command is recognized

        if (command == "exit")
        {
            std::cout << "Exiting ...." << std::endl;
            return false;
        }

        if (command == "load")
        {
            // load expects a filename ... so read one more word
            if (!tkn.readWord(arg))
            {
                std::cout << "Missing file name" << std::endl;
                continue; // skip back to the top of the read loop
            }

            //Attempts to read input file
            std::ifstream fin;
            bool status = true;
            fin.open(arg);
            if (fin.is_open())
            {
                status = processText(fin, false);
            }
            else
            {
                std::cout << "Failed to open the file" << std::endl;
            }
            fin.close();
            if (!status)
                return false;
        }

        if (command == "rotateX")
        {
            // if a float value is found adds a rotation matrix around the x-axis based on angle inputted
            if (tkn.readFloat(float_arg))
            {
                //rotated matrix pushed on stack
                mtx.RotX(float_arg);
                stk.push(mtx);
                std::cout << "rotateX: " << float_arg << std::endl;
            }
            else
            {
                // if no float value is found user is informed and loop continues
                std::cout << "Error! Expected angle value." << std::endl;
                continue;
            }

        }

        if (command == "rotateY")
        {
            // if a float value is found adds a rotation matrix around the y-axis based on angle inputted
            if (tkn.readFloat(float_arg))
            {
                //rotated matrix pushed on stack
                mtx.RotY(float_arg);
                stk.push(mtx);
                std::cout << "RotateY: " << float_arg << std::endl;

            }
            else
            {
                // if no float value is found user is informed and loop continues
                std::cout << "Error! Expected angle value." << std::endl;
                continue;
            }


        }

        if (command == "rotateZ")
        {
            // if a float value is found adds a rotation matrix around the z-axis based on angle inputted
            if (tkn.readFloat(float_arg))
            {
                //rotated matrix pushed on stack
                mtx.RotZ(float_arg);
                stk.push(mtx);
                std::cout << "rotateZ: " << float_arg << std::endl;

            }
            else
            {
                // if no float value is found user is informed and loop continues
                std::cout << "Error! Expected angle value." << std::endl;
                continue;
            }

        }

        if (command == "translate")
        {
            // if a float value is found it translates along the X-axis based on value found
            if (tkn.readFloat(float_arg))
            {
                // if a float value is found it translates along the Y-axis based on value found
                if (tkn.readFloat(float_arg1))
                {
                    // if a float value is found it translates along the Z-axis based on value found
                    if (tkn.readFloat(float_arg2))
                    {
                        mtx.Translate(float_arg, float_arg1, float_arg2); //translate is executed once all values found
                        stk.push(mtx);                                    //translated matrix pushed on stack
                        std::cout << "Translate: " << float_arg << "   " << float_arg1 << "   "
                        << float_arg2 << "   " << std::endl;
                    }
                    else
                    {
                        // if no float value is found user is informed and loop continues
                        std::cout << "Error! Expected a value for z in translation." << std::endl;
                        continue;
                    }
                }
                else
                {
                    // if no float value is found user is informed and loop continues
                    std::cout << "Error! Expected a value for y in translation." << std::endl;
                    continue;
                }
            }
            else
            {
                // if no float value is found user is informed and loop continues
                std::cout << "Error! Expected a value for x in translation." << std::endl;
                continue;
            }
        }

        if (command == "transformVertex")
        {
            // if a float value is found it transforms the X-axis based on value found
            if (tkn.readFloat(float_arg))
            {
                // if a float value is found it transforms the Y-axis based on value found
                if (tkn.readFloat(float_arg1))
                {
                    // if a float value is found it transforms along the Z-axis based on value found
                    if (tkn.readFloat(float_arg2))
                    {
                        stk.Transform(float_arg, float_arg1, float_arg2); //transform is executed once all values found
                    }
                    else
                    {
                        // if no float value is found user is informed and loop continues
                        std::cout << "Error! Expected a value for z in vertex." << std::endl;
                        continue;
                    }
                }
                else
                {
                    // if no float value is found user is informed and loop continues
                    std::cout << "Error! Expected a value for y in vertex." << std::endl;
                    continue;
                }
            }
            else
            {
                // if no float value is found user is informed and loop continues
                std::cout << "Error! Expected a value for x in vertex." << std::endl;
                continue;
            }
        }

        // removes the most recent matrix found on the stack by popping it, does nothing if stack is empty
        if (command == "undo")
        {
            stk.pop();
        }


        if (command.empty())
        {
            // if no command is found user is informed and loop continues
            std::cout << "Waiting to load file..." << std::endl;
            continue;
        }

    }

}
