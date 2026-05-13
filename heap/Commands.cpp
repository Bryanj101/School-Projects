/*
Student Name: Bryan Johnson
Student NetID: btj117
Date: 11/14/2020
Compiler Used: Clion using mingw
Program Description:
This program will execute commands or load a text file and will tokenize it in order to find commands. If the program
finds a command it attempts to execute the given command. The given commands associated with this program will be used
to create and implement a preemptive scheduling queue. This program will schedule tasks, add scheduled tasks to a
priority queue, and increment through both the priority queue and schedule via time steps.
*/
#include "Commands.h"
string command;
string arg1, arg2;
int iarg1, iarg2, iarg3, iarg4;
double darg1, darg2;
int step = -1;
int count;
string line;
Heap pq;
std::vector<Process> sched;
std::vector<Process> sched_store;
std::vector<Process> current_task;
// function for processing text to parse and execute commands

    bool processText(istream& is, bool interactive) {
        // implement support for
        // exit ... exit the program
        // load file ... loads a file containing supported commands
        // simulate ... enters simulation mode to allow for simulation commands
        // schedule ... enters scheduling mode to allow for scheduling commands
        // register ... registers tasks to the scheduling vector
        // display ... depending on mode displays either the schedule or both the schedule and priority queue
        // clear ... clear command for scheduling mode to clear schedule
        // remove ... removes scheduled task based on name of task
        // step ... increases the time elapsed by an increment of 1
        // reset ... clears priority queue and resets original scheduling
        // run ... increments time steps until the end of the priority queue
        // run til ... increments time steps until specified time



        Tokenizer tkn;
        bool sim_mode = false;
        bool schedule_mode = true;
        int total_time;
        //Enters control loop...
        while (true) {
            if (!interactive) {
                if (is.eof())
                    return true;
            } else {
                if (schedule_mode)
                    std::cout << "Scheduling>>";
                if (sim_mode)
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
                sim_mode = false;
                schedule_mode = false;
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
                    status = processText(fin, false);
                } else {
                    std::cout << "Failed to open the file" << std::endl;
                }
                fin.close();
                if (!status)
                    return false;
            }
            // command function to handling switching to simulation mode
            if (command == "simulate")
            {
                std::cout << "Entering simulation mode..." << '\n';
                schedule_mode = false;
                sim_mode = true;
                continue;
            }
            // command function set scheduling mode
            if (command == "schedule")
            {
                std::cout << "Entering scheduling mode...Removing scheduled tasks." << '\n';
                sched.clear();
                schedule_mode = true;
                sim_mode = false;
                continue;
            }
            // command function set scheduling mode
            if (command == "register")
            {
                if (!schedule_mode) {
                    std::cout << "This command can only be done in scheduling mode." << std::endl;
                    continue;
                }
                std::vector<Process> tmp;
                if (tkn.readWord(arg1))
                {
                    Process task_label;
                    task_label.name = arg1;
                    tmp.push_back(task_label);
                    for (auto & i : sched)
                    {
                        if (i.name == tmp.at(0).name)
                        {
                            std::cout << "Task " << tmp.at(0).name << " already scheduled. Remove it if you want to "
                                                                      "reschedule it."<< '\n';
                            sched.pop_back();
                            sched_store.pop_back();
                            continue;
                        }

                    }
                    if (tkn.readInteger(iarg2) && 0 < iarg2  && iarg2 < 100)
                    {
                        if (tkn.readInteger(iarg3) && iarg3 > 0)
                        {
                            total_time = total_time + iarg3;
                            if (tkn.readInteger(iarg4) && iarg4 >= 0)
                            {
                                Process::schedule(sched,arg1, iarg2, iarg3, iarg4);
                                Process::schedule(sched_store,arg1, iarg2, iarg3, iarg4);
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

                std::cout << "Registering: " << sched.back().name;
                std::cout << " @" << sched.back().priority;
                std::cout << " for " << sched.back().elapsed_time;
                std::cout << " out of " << sched.back().length;
                std::cout << " arriving at " << sched.back().arrives << '\n';
            }
            // command function set to display contents of schedule or both depending on mode
            if (command == "display")
            {
                if (schedule_mode)
                {
                    Process::display_schedule(std::cout, sched);
                    continue;
                }
                if (sim_mode)
                {
                    if (current_task.empty())
                    {
                        std::cout << "Next step = " << step + 1<< '\n';
                        std::cout << "Current task: None" << '\n';
                        Process::display_schedule(std::cout, sched);
                    }
                    else if (!current_task.empty())
                    {
                        std::cout << "Time step = " << step << '\n';
                        for (auto & i : current_task) {
                            std::cout << "Current task: " << i.name;
                            std::cout << " @" << i.priority;
                            std::cout << " for " << i.elapsed_time;
                            std::cout << " out of " << i.length;
                            std::cout << " arriving at " << i.arrives << '\n';
                        }
                        pq.display(std::cout);
                        Process::display_schedule(std::cout, sched);
                    }
                }
            }
            // command function to clear schedule of all tasks
            if (command == "clear")
            {
                if (!schedule_mode) {
                    std::cout << "This command can only be done in scheduling mode." << std::endl;
                    continue;
                }
                sched.clear();
                continue;
            }
            // command function to remove specific task by name from schedule
            if (command == "remove")
            {
                if (!schedule_mode) {
                    std::cout << "This command can only be done in scheduling mode." << std::endl;
                    continue;
                }
                if (tkn.readWord(arg1)) {
                    for (int i = 0; i < sched.size(); i++)
                        if (sched.at(i).name == arg1)
                            sched.erase(sched.begin() + i);
                }
                else
                    std::cout << "Invalid name." << '\n';
            }
            // command function to call on step function and increment through queue
            if (command == "step")
            {
                if (!sim_mode) {
                    std::cout << "This command can only be done in simulation mode." << std::endl;
                    continue;
                }
                if (tkn.readInteger(iarg1))
                {
                    count = iarg1;
                }
                else
                {
                    count = 1;
                }
                for (int i = 0; i < count; i++) { step_func(); }
            }
            // command function to reset priority queue and schedule
            if (command == "reset")
            {
                if (!sim_mode) {
                    std::cout << "This command can only be done in simulation mode." << std::endl;
                    continue;
                }
                std::vector<Process> tmp;
                current_task.clear();
                pq.buildHeap(tmp, 0);
                for (auto & i : sched_store)
                    sched.push_back(i);
                step = -1;
            }
            // command function to run until end of schedule or specific time step
            if (command == "run")
            {

                if (!sim_mode)
                {
                    std::cout << "This command can only be done in simulation mode." << std::endl;
                    continue;
                }
                if (tkn.readWord(arg1)) {
                    if (arg1 == "til" && tkn.readInteger(iarg1)) {
                        if (step < iarg1) {
                            for (int i = 0; i < (iarg1 + 1); i++)
                                step_func();
                        } else { std::cout << "At time: " << step << '\n'; }
                    }

                    else
                        std::cout << "Please enter a valid integer." << '\n';

                }
                else
                    for (int j = 0; j < total_time; j++)
                    {
                        if (j == total_time)
                            return false;
                        step_func();
                    }

            }
        }

    }

    //function for incrementing time steps and handling priority swapping
    void step_func()
{
    Process tmp;

        step++;
        std::cout << "Time step: " << step << '\n';
        while (sched[0].arrives <= step && !sched.empty() && sched[0].priority != 0) {
            std::cout << "Added: " << sched.at(0).name;
            std::cout << " @" << sched.at(0).priority;
            std::cout << " for " << sched.at(0).elapsed_time;
            std::cout << " out of " << sched.at(0).length;
            std::cout << " arriving at " << sched.at(0).arrives << '\n';
            pq.add(sched[0]);
            sched.erase(sched.begin());
        }


        if (!current_task.empty()) {
            current_task.at(0).elapsed_time++;
            if (current_task.at(0).elapsed_time >= current_task.at(0).length
                && current_task.at(0).length != 0) {
                current_task.erase(current_task.begin());
                if (pq.peek(tmp)) {
                    pq.remove(current_task);
                    current_task.at(0).elapsed_time++;
                }
            }
        }
        if (current_task.empty() && pq.peek(tmp)) {
            pq.remove(current_task);
            current_task.at(0).elapsed_time++;
        }

        if (!pq.peek(tmp) && sched.empty() && current_task.empty()) {
            std::cout << "End of queue..." << '\n';
        }
        std::cout << "Current task: " << current_task.at(0).name;
        std::cout << " @" << current_task.at(0).priority;
        std::cout << " for " << current_task.at(0).elapsed_time;
        std::cout << " out of " << current_task.at(0).length;
        std::cout << " arriving at " << current_task.at(0).arrives << '\n';

        if (tmp.priority < current_task.at(0).priority && tmp.priority != 0 ||
            tmp.priority == current_task.at(0).priority &&
            tmp.elapsed_time > current_task.at(0).elapsed_time && tmp.priority != 0) {

            tmp.name = current_task.at(0).name;
            tmp.priority = current_task.at(0).priority;
            tmp.length = current_task.at(0).length;
            tmp.arrives = current_task.at(0).arrives;
            tmp.elapsed_time = current_task.at(0).elapsed_time;
            current_task.clear();
            pq.remove(current_task);
            pq.add(tmp);
            current_task.at(0).elapsed_time++;
        }

}

