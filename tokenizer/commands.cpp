/*Student Name: Bryan Johnson
Student NetID: btj117
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
manipulate a doubly linked list.
*/

// includes commands header and inherits from List and Tokenizer headers
#include "commands.h"


bool commands::processText(istream& is, bool interactive)
{
    // implement commands and support for
    // exit ... exit the program
    // append ... adds new node at end of list
    // prepend ... adds new node at start of list
    // load file ... loads a file containing supported commands
    // insert before ... inserts new node before a given node
    // insert after ... inserts new node after a given node
    // display ... displays the entirety of the current list
    // display until ... displays active nodes until a given time
    // remove ... removes a specified node
    // length ... displays the total sum of time of the current list
    // search ... finds the specified node
    string line;
    string command;
    string arg;
    string arg1;
    string var;
    int int_arg;
    Tokenizer tkn;
    List lst;


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
            cout << ">>";
        }

        //gets line from input stream
        getline(is, line);
        tkn.setString(line);

        //first word in stream should always be a command
        tkn.readWord(command);

        //Below we start checking if the command is recognized

        if (command == "exit")
        {
            cout << "Exiting ...." << endl;
            return false;
        }

        if (command == "load")
        {
            // load expects a filename ... so read one more word
            if (!tkn.readWord(arg))
            {
                cout << "Missing file name" << endl;
                continue; // skip back to the top of the read loop
            }

            //Attempts to read input file
            ifstream fin;
            bool status = true;
            fin.open(arg);
            if (fin.is_open())
            {
                status = processText(fin, false);
            }
            else
            {
                cout << "Failed to open the file" << endl;
            }
            fin.close();
            if (!status)
                return false;
        }

        if (command == "append")
        {
            if (tkn.readWord(arg))
            {
                if (!tkn.readInteger(int_arg))
                {
                    cout << "Error! Expected word and integer." << endl;
                }
                else
                {
                    lst.append_list(arg, int_arg);
                    cout << "Appending list with " << arg << " " << int_arg << "." << endl;
                }
            }
            else
            {
                cout << "Error! Expected word and integer." << endl;
            }

        }

        if (command == "prepend")
        {
            if (tkn.readWord(arg))
            {
                if (!tkn.readInteger(int_arg))
                {
                    cout << "Error! Expected word and integer." << endl;
                }
                else
                {
                    lst.prepend_list(arg, int_arg);
                    cout << "Prepending list with " << arg << " " << int_arg << "." << endl;
                }
            }
            else
            {
                cout << "Error! Expected word and integer." << endl;
            }


        }

        if (command == "insert_before")
        {
            if (tkn.readWord(arg))
            {
                if (!tkn.readInteger(int_arg))
                {
                    cout << "Error! Expected word to be inserted, an integer, word to insert before."
                            << endl;
                }
                else if (!tkn.readWord(arg1))
                {
                    cout << "Error! Expected word to be inserted, an integer, word to insert before."
                            << endl;
                }
                else
                {
                    lst.insert_before(arg, int_arg, arg1);
                    cout << "Inserting " << arg << " before " << arg1 << "." << endl;
                }
            }
            else
            {
                cout << "Error! Expected word to be inserted, an integer, word to insert before."
                        << endl;
            }

        }

        if (command == "insert_after")
        {
            if (tkn.readWord(arg))
            {
                if (!tkn.readInteger(int_arg))
                {
                    cout << "Error! Expected word to be inserted, an integer, word to insert after."
                            << endl;
                }
                else if (!tkn.readWord(arg1))
                {
                    cout << "Error! Expected word to be inserted, an integer, word to insert after."
                            << endl;

                }
                else
                {
                    lst.insert_after(arg, int_arg, arg1);
                    cout << "Inserting " << arg << " after " << arg1 << "." << endl;
                }
            }
            else
            {
                cout << "Error! Expected word to be inserted, an integer, word to insert after."
                        << endl;

            }

        }

        if (command == "display")
        {
            if (!tkn.readWord(arg))
            {
                cout << "Displaying list of events:" << endl;
                lst.display(std::cout);
            }
            else
            {
                cout << "Error! Display function does not require any other input." << endl;
            }

        }

        if (command == "display_until")
        {
            if (tkn.readInteger(int_arg))
            {
                lst.display_until(cout, int_arg);
            }
            else
            {
                cout << "Error! Expected an integer." << endl;
            }


        }

        if (command == "remove")
        {
            if (tkn.readWord(arg))
            {
                cout << "Removing x from list." << endl;
                lst.remove(arg);
            }
            else
            {
                cout << "Error! Expected a single word." << endl;
            }

        }

        if (command == "search")
        {
            if (tkn.readWord(arg))
            {
                lst.search(arg);
            }
            else
            {
                cout << "Error! Expected a word." << endl;

            }

        }

        if (command == "clear")
        {
            if (!tkn.readWord(arg))
            {
                lst.clear();
            }
            else
            {
                cout << "Error! Clear does not require any other input." << endl;
            }

        }

        if (command == "length")
        {
            if (!tkn.readWord(arg))
            {
                lst.length(std::cout);
            }
            else
            {
                cout << "Error! Length does not require any other input." << endl;
            }

        }
        if (command.empty())
        {
            cout << "Waiting to load file..." << endl;
            continue;
        }

    }

}
