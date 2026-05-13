//
// Created by D-1 on 11/12/2021.
//
#include "Commands.h"
#include "Heap.h"
// function for processing text to parse and execute commands
bool SchedulingMode(istream& is, bool interactive) {
    // implement support for
    // exit ... exit the program
    // load file ... loads a file containing supported commands
    // constructTree ... constructs a binary search tree based on depth
    // convert ... converts given string into morse code
    // preOrderTraversal ... displays pre-order traversal of the tree
    // postOrderTraversal ... displays post-order traversal of the tree
    // inOrderTraversal ... displays in-order traversal of the tree
    // clear ... clears content of the tree

    string line;
    string command;
    string arg1, arg2;
    int iarg1, iarg2, iarg3, iarg4;
    double darg1, darg2;
    Tokenizer tkn;



    //Enters control loop...
    while (true) {
        if (!interactive) {
            if (is.eof())
                return true;
        } else {
            std::cout << "Scheduling>>";
        }

        //gets line from input stream
        getline(is, line);
        tkn.setString(line);

        //first word in stream should always be a command
        tkn.readWord(command);

        //Below we start checking if the command is recognized

        // exits program and does some clean up
        if (command == "exit") {
            std::cout << "Exiting ...." << std::endl;
            return false;
        }

        if (command == "load") {
            // load expects a filename ... so read one more word
            if (!tkn.readWord(arg1)) {
                std::cout << "Missing file name" << std::endl;
                continue; // skip back to the top of the read loop
            }

            // checks for spaces in file path and appends for full path
            if (tkn.readLine(arg2)) {
                arg1 = arg1.append(arg2);
            }

            //Attempts to read input file
            std::ifstream fin;
            bool status = true;
            fin.open(arg1);
            if (fin.is_open()) {
                status = SchedulingMode(fin, false);
            } else {
                std::cout << "Failed to open the file" << std::endl;
            }
            fin.close();
            if (!status)
                return false;
        }
        if (command == "register")
        {
            std::vector<Process> tmp;
            if (!tkn.readInteger(iarg1) && tkn.readWord(arg1)) {
                Process task_label;
                task_label.name = arg1;
                tmp.push_back(task_label);
                for (auto & i : sched)
                {
                    if (i.name != tmp.at(0).name)
                        continue;
                    else
                        std::cout << "Task " << tmp.at(0).name << " already scheduled." << '\n';
                }
                if (tkn.readInteger(iarg2) && 0 < iarg2  && iarg2 < 100)
                {
                    if (tkn.readInteger(iarg3) && iarg3 > 0)
                    {

                        if (tkn.readInteger(iarg4) && iarg4 >= 0)
                        {
                            schedule(arg1, iarg2, iarg3, iarg4);
                        }
                        else
                        {
                            std::cout << "Arrival time must be a positive integer." << '\n';
                            continue;
                        }
                    }
                    else
                    {
                        std::cout << "Error! Length must be a positive integer." << '\n';
                        continue;
                    }
                }
                else
                {
                    std::cout << "Error! Priority must be between 1-100." << '\n';
                    continue;
                }
            }
            else
            {
                std::cout << "Error naming task..." << '\n';
                continue;
            }
        }
        if (command == "display")
        {
            display_schedule(std::cout);
        }
        if (command == "simulate")
        {
            std::cout << "Entering simulation mode..." << '\n';
            SimulationMode(std::cin);
            return false;
        }
        if (command == "clear")
        {
            clear();
        }
    }
}

// function for processing text to parse and execute commands
bool SimulationMode(istream& is, bool interactive) {
    // implement support for
    // exit ... exit the program
    // load file ... loads a file containing supported commands
    // constructTree ... constructs a binary search tree based on depth
    // convert ... converts given string into morse code
    // preOrderTraversal ... displays pre-order traversal of the tree
    // postOrderTraversal ... displays post-order traversal of the tree
    // inOrderTraversal ... displays in-order traversal of the tree
    // clear ... clears content of the tree

    string line;
    string command;
    string arg1, arg2;
    int iarg1, iarg2, iarg3, iarg4;
    double darg1, darg2;
    Tokenizer tkn;



    //Enters control loop...
    while (true) {
        if (!interactive) {
            if (is.eof())
                return true;
        } else {
            std::cout << "Simulating>>";
        }

        //gets line from input stream
        getline(is, line);
        tkn.setString(line);

        //first word in stream should always be a command
        tkn.readWord(command);

        //Below we start checking if the command is recognized

        // exits program and does some clean up
        if (command == "exit") {
            std::cout << "Exiting ...." << std::endl;
            return false;
        }

        if (command == "load") {
            // load expects a filename ... so read one more word
            if (!tkn.readWord(arg1)) {
                std::cout << "Missing file name" << std::endl;
                continue; // skip back to the top of the read loop
            }

            // checks for spaces in file path and appends for full path
            if (tkn.readLine(arg2)) {
                arg1 = arg1.append(arg2);
            }

            //Attempts to read input file
            std::ifstream fin;
            bool status = true;
            fin.open(arg1);
            if (fin.is_open()) {
                status = SimulationMode(fin, false);
            } else {
                std::cout << "Failed to open the file" << std::endl;
            }
            fin.close();
            if (!status)
                return false;
        }
        if (command == "schedule")
        {
            std::cout << "Entering scheduling mode..." << '\n';
            SchedulingMode(std::cin);
            return false;
        }

    }

}