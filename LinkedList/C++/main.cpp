/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will take individual words inputted by a user and store them in a linked list. When the user inputs
 * STOP as a word, the program prints the stored words in reverse order of how they were originally inputted.
 */
#include "LinkedList.hpp"
int main() {
    LinkedList lst{};  // initializes LinkedList obj
    std::string input;
    std::cout << "This program will read a string entered by the user until STOP is entered.\n";
    while (true) // prompts user for a word until STOP is entered
    {
        std::cout << "Enter a string:";
        std::cin >> input;
        if (input == "STOP")
        {
            break;
        }
        lst.add(input);
    }
    lst.display(std::cout); // displays list in reverse order of input
    lst.clear(); // clears list and frees memory
    return 0;
}
