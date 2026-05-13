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

//includes and inherits from Tokenizer header file
#include "Tokenizer.h"
#include <iostream>

void Tokenizer::setString(const string& str)
{
    //sets the source string for the stream
    ss.str(str);
    //clears any error flags
    ss.clear();
}

/*
 * bool isEmpty - returns true if the stringstream is empty
 */

bool Tokenizer::isEmpty() const
{
    bool status=false;
    //checks if at end of stream (therefore its empty)
    if (ss.eof())
        status=true;

    return status;
}

/*
 * bool readLine - reads the remainder of the stream as a single string
 */

bool Tokenizer::readLine(string& line)
{
    bool status=false;

    if (isEmpty()) //check if stream is empty...
    {
        status=false;
    }
    else if (getline(ss, line)) //if not, try to read a line
    {
        status=true;
    }
    return status;
}

/*
 * bool readInteger - reads an integer value from the stream, otherwise returns false
 */

bool Tokenizer::readInteger(int& val)
{
    bool status=false;
    if (isEmpty()) //check if stream is empty...
    {
        status=false;
    }
    else
    {
        try //try to read val...
        {
            ss >> val;
            status=true;
        }
        catch (std::ios_base::failure) //...otherwise fail and set status
        {
            ss.clear();
            status=false;
        }
    }
    return status;
}

/*
 * bool readWord - reads a single word (as a string) from the stream, otherwise returns false
 */

bool Tokenizer::readWord(string& val)
{
    bool status=false;

    if (isEmpty()) //check if stream is empty...
    {
        status=false;
    }
    else
    {
        try //try to read val...
        {
            ss >> val;
            status=true;
        }
        catch (std::ios_base::failure) //...otherwise fail and set status
        {
            ss.clear();
            status=false;
        }
    }
    return status;
}

/*
 * bool readFloat - reads a float from the stream, otherwise returns false
 */

bool Tokenizer::readFloat(float& val)
{
    bool status=false;
    if (isEmpty()) //check if stream is empty...
    {
        status=false;
    }
    else
    {
        try //try to read val...
        {
            ss >> val;
            status=true;
        }
        catch (std::ios_base::failure) //...otherwise fail and set status
        {
            ss.clear();
            status=false;
        }
    }
    return status;
}

bool Tokenizer::readFloats(float& val, float& val1, float& val2)
{
    bool status=false;
    if (isEmpty()) //check if stream is empty...
    {
        status=false;
    }
    else
    {
        try //try to read val...
        {
            ss >> val;
            status=true;
        }
        catch (std::ios_base::failure) //...otherwise fail and set status
        {
            ss.clear();
            status=false;
        }
    }
    return status;
}


/*
 * bool readChar - reads a single character from the stream, otherwise returns false
 */

bool Tokenizer::readChar(char& val)
{
    bool status=false;
    if (isEmpty()) //check if stream is empty...
    {
        status=false;
    }
    else
    {
        try //try to read val...
        {
            ss >> val;
            status=true;
        }
        catch (std::ios_base::failure) //...otherwise fail and set status
        {
            ss.clear();
            status=false;
        }
    }
    return status;
}

/*
 * void rewind - resets stream to beginning
 */

void Tokenizer::rewind()
{
    ss.seekg(0, ss.beg); //moves stream back to beginning
}

/*
 * void clear - empties the stream
 */

void Tokenizer::clear()
{
    setString(""); //sets stream to empty string
    ss.setstate(std::ios::eofbit); //sets "end of file" flag/state
}
