/*Student Name: Bryan Johnson
Student NetID: btj117
Compiler Used: Clion using mingw
Program Description:
This program will load a text file and will tokenize it in order to find commands. If the program finds a command it
attempts to execute the given command. The given commands associated with this program will be used to create and
manipulate a doubly linked list.
*/

// including list header
#include "List.h"

//constructing nodes for linked list
Node::Node()
{
    event = ""; //sets default event to 0
    time = 0; //sets default time to 0
    next = nullptr; //sets next node to a NULL pointer
    prev = nullptr; //sets next node to a NULL pointer
}

Node::Node(std::string _event, int _time)
{
    event = std::move(_event); //sets event to input parameter _event
    time = _time; //sets time to input parameter _time
    next = nullptr; //sets next node to NULL pointer
    prev = nullptr; //sets next node to NULL pointer
}

// constructing head and tail for list functions
List::List()
{
    head = nullptr; // sets default head to NULL ptr
    tail = nullptr; // sets default tail to NULL ptr
}

// prepend list function for inserting node at start of list
void List::prepend_list(std::string _event, int _time)
{
    Node* tmp = new Node(std::move(_event), _time);
    tmp->next = head;

    if (head == nullptr)
        tail = tmp;
    else
        head->prev = tmp;

    head = tmp;
}

// append list function for inserting node at end of list
void List::append_list(std::string _event, int _time)
{
    Node *tmp = new Node(std::move(_event), _time);
    tmp->prev = tail;

    if (head == nullptr)
        head = tmp;
    else
        tail->next = tmp;

    tail = tmp;
}
void List::display(std::ostream &os)
{
    Node *tmp = head;
    while (tmp != nullptr)
    {
        os << tmp->event << " " << tmp->time << "s" << std::endl;
        tmp = tmp->next;
    }
}

// display until function displays nodes up to a specified time
void List::display_until(std::ostream &os, int _time)
{
    Node *tmp = head;
    int sum_time = 0;
    while (tmp != nullptr)
    {
        os << tmp->event << " " << tmp->time << "s"  << std::endl;
        sum_time += tmp->time;
        tmp = tmp->next;
        if (sum_time >= _time)
        {
            break;
        }
    }
    os << "Events played for "<< _time << "s."<< std::endl;
}

// length function gives the total sum of time in current list
void List::length(std::ostream &os)
{
    Node *tmp = head;
    int sum_time = 0;
    while (tmp != nullptr)
    {
        sum_time += tmp->time;
        tmp = tmp->next;
    }
    os << "Total time of events in list "<< sum_time << "s."<< std::endl;
}

// remove function to remove a specified node from the list
bool List::remove(const std::string& _event)
{
    Node *tmp = head;
    while(tmp != nullptr)
    {
        if (tmp->event == _event)
        {
            if (tmp->prev != nullptr)
                tmp->prev->next = tmp->next;
            if (tmp->next != nullptr)
                tmp->next->prev = tmp->prev;
            if (tmp == head)
                head = tmp->next;
            if (tmp == tail)
                tail = tmp->prev;
            delete tmp;
            return true;
        }

        tmp = tmp->next;

    }
    std::cout << "Error! Event does not exist in list." << std::endl;
    return false;
}

// clear function to clear the list of all its current contents
void List::clear()
{
    Node *tmp = head;
    while(tmp != nullptr)
    {
        if (tmp->prev != nullptr)
            tmp->prev->next = tmp->next;
        if (tmp->next != nullptr)
            tmp->next->prev = tmp->prev;
        if (tmp == head)
            head = tmp->next;
        if (tmp == tail)
            tail = tmp->prev;
        delete tmp;


        tmp = tmp->next;
    }
    std::cout << "Clearing list of events." << std::endl;
}

// search function to find a specified node in the list
bool List::search(const std::string& _event)
{
    Node *tmp = head;

    while (tmp != nullptr)
    {
        if (tmp->event == _event)
        {
            std::cout << "Found event: " << tmp->event <<  " " << tmp->time << "s"  << std::endl;
            return true;
        }

        tmp = tmp->next;
    }
    std::cout << "Error! Event does not exist in list." << std::endl;
    return false;
}

// insert before function to insert a node before a specified node
void List::insert_before(std::string new_event, int _time,  const std::string& _event)
{
    Node* next_event = head;
    Node *tmp = new Node(std::move(new_event), _time);

    while (next_event != nullptr)
    {
        if (next_event->event == _event)
        {
            if (next_event->prev != nullptr) {
                next_event->prev->next = tmp;
                tmp->prev = next_event->prev;
                tmp->next = next_event;
                next_event->prev = tmp;
                break;
            } else {
                tmp->next = head;
                head->prev = tmp;
                head = tmp;
                break;
            }
        }
        else if (next_event->next == nullptr)
        {
            std::cout << "Error! Event does not exist in list." << std::endl;
            break;
        }

        next_event = next_event->next;
    }

}
// insert after function to insert a node after a specified node
void List::insert_after(const std::string& new_event, int _time, const std::string& _event)
{
    Node* prev_event = head;

    while (prev_event != nullptr)
    {
        if (prev_event->event == _event)
        {
            Node *tmp = new Node(new_event, _time);
            tmp->next = prev_event->next;
            tmp->prev = prev_event;
            prev_event->next = tmp;
            break;
        }
        else if (prev_event->next == nullptr)
        {
            std::cout << "Error! Event does not exist in list." << std::endl;
            break;
        }

        prev_event = prev_event->next;
    }

}
