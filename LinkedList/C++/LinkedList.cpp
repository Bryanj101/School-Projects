/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will take individual words inputted by a user and store them in a linked list. When the user inputs
 * STOP as a word, the program prints the stored words in reverse order of how they were originally inputted.
 */

#include "LinkedList.hpp"

void LinkedList::add(const std::string& input)
{
    Node* tmp = new Node(input);  // adds new Node with new string input to the list
    tmp->next = head;  // new node's next ptr points to head
    head = tmp;  // head is now the new node
}

void LinkedList::display(std::ostream &os)  // displays entire list
{
    Node *tmp = head;
    if (head == nullptr)  // if head is already NULL prints the list is empty
    {
        std::cout << "List is empty." << "\n";
    }
    else {std::cout << "Reversed order of strings:\n";}
    while (tmp != nullptr)  // print strings of list node's until list is exhausted
    {
        os << tmp->input << "\n";
        tmp = tmp->next;
    }
}

void LinkedList::clear()  // clears entire list
{
    Node *tmp = head;
    while(tmp != nullptr)  // deletes nodes until list is exhausted
    {
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

// constructors
LinkedList::LinkedList()
{
    head = nullptr; // initialize head to NULL pointer
}

Node::Node()
{
    input = ""; //sets default input to nothing
    next = nullptr; //sets next node to a NULL pointer
}

Node::Node(std::string _input)
{
    input = std::move(_input); //sets default input to new input
    next = nullptr; //sets next node to a NULL pointer
}