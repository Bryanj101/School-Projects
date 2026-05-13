/*
Student Name: Bryan Johnson
Student NetID: btj117
Date: 10/20/2020
Compiler Used: Clion using mingw
Program Description:
This program will execute commands or load a text file and will tokenize it in order to find commands. If the program
finds a command it attempts to execute the given command. The given commands associated with this program will be used
to create and implement a binary search tree. This program will be able to traverse the tree in inorder, preorder, and
postorder. The binary search tree will hold characters and element positions for the purpose of converting a string to
morse code. When the user commands the program to convert a string it will convert the string to morse code based on the
traversal of the string.
*/

# include "BST.h"

//implementation of private binary search tree functions
bool BST::insert(Node* &node, char _morse, int _data)  //inserts a new node into the binary search tree
{
    if (node == nullptr)
    {
        node = new Node(_morse, _data);
        return true;
    }
    if (_data < node->data)
    {
        return (insert(node->left, _morse, _data));
    }
    if (_data > node->data)
    {
        return (insert(node->right, _morse, _data));
    }
    return false;
}

bool BST::remove(Node* &node, int _data)    //removes a node from the binary search tree
{
    if (node == nullptr)
    {
        return false;
    }
    if (_data < node->data)
    {
        return (remove(node->left, _data));
    }
    if (_data > node->data)
    {
        return (remove(node->right, _data));
    }
    // if node has children then a new parent will be determined before node removal
    int deg = node->degree();
    if (deg == 0)
    {
        delete node;
        node = nullptr;
    }
    else if (deg == 1)
    {
        Node* tmp = node;
        if (node->left != nullptr)
            node = node->left;
        else
        {
            node = node->right;
        }
        delete tmp;
    }
    else
    {
        Node *tmp = node->left;
        while (tmp->right != nullptr)
        {
            tmp = tmp->right;
        }
        node->data = tmp->data;
        remove(node->left, tmp->data);
    }

    return true;
}

void BST::postorder(Node* &node, std::ostream& os)   //displays tree in post-order
{
    if (node == nullptr)
    {
        return;
    }
    postorder(node->left, os);
    postorder(node->right, os);
    os << "<" << node->morse << "," << node->data << ">" << "\t";
}

void BST::preorder(Node* &node, std::ostream& os)  //displays tree in pre-order
{
    if (node == nullptr)
        return;
    os << "<" << node->morse << "," << node->data << ">" << "\t";
    preorder(node->left, os);
    preorder(node->right, os);
}

void BST::inorder(Node* &node, std::ostream& os)   //displays tree in in-order
{
    if (node == nullptr)
        return;
    inorder(node->left, os);
    os << "<" << node->morse << "," << node->data << ">" << '\t';
    inorder(node->right, os);
}

void BST::destroy(Node* &node)   //deletes all nodes in tree
{
    if (node == nullptr)
        return;
    destroy(node->left);
    destroy(node->right);
    remove(node, node->data);
}

bool BST::find(Node* node, int &_data, std::ostream& os) {   //finds a specific node in tree
    {
        // as it traverses tree it adds a dot or dash based on left or right traversal
        if (_data > sizeof(morseObject.morseTree)) {
            return false;
        }
        if (_data < node->data) {
            os << ".";
            find(node->left, _data, os);
        }
        if (_data > node->data) {
            os << "-";
            find(node->right, _data, os);
        }
        return true;
    }
}

bool BST::findChar(Node* node, char _morse)   //finds a specific character in a node in tree
{
    if (node == nullptr)
        return false;
    if (_morse != node->morse) {            // traverses tree to find character
        findChar(node->left, _morse);
        findChar(node->right, _morse);
    }
    else {
        find(node->data, std::cout);    // once character is found uses that node's data to call find function
        std::cout << "\n";
    }
    return true;
}

void BST::construct(int depth)   //constructs the binary search tree based on given depth
{
    int arrCount = 0;
    for (int rowCount = 0; rowCount <= depth; rowCount++)
    {
        int rowElementCount = pow(2, rowCount);
        int rowElement = pow(2, (depth - rowCount));
        int rowElementCounter = pow(2, (depth - rowCount + 1));

        // insert morse tree array elements based on depth
        for (int j = 0; j < rowElementCount; j++, rowElement += rowElementCounter)
        {
            insert(morseObject.morseTree[arrCount], rowElement);
            arrCount ++;
        }
    }
}

//implementation of functions that call private functions
bool BST::insert(char morse, int data)   //calls private insert function
{
    return insert(root, morse, data);
}
bool BST::remove(int data)              //calls private remove function
{
    return remove(root, data);
}

bool BST::find(int &data, std::ostream& os)     //calls private find function
{
    return find(root, data, os);
}
bool BST::findChar(char morse)          //calls private findChar function
{
    return findChar(root, morse);
}

void BST::inorder(std::ostream& os)     //calls private inorder function
{
    inorder(root, os);
}

void BST::postorder(std::ostream& os)       //calls private postorder function
{
    postorder(root, os);
}

void BST::preorder(std::ostream& os)      //calls private preorder function
{
    preorder(root, os);
}

void BST::destroy()                 //calls private destroy function
{
    destroy(root);
}

void BST::constructTree(int depth)       //calls private construct function
{
    construct(depth);
}

BST::~BST()     //destructor
{
    BST::destroy();
}
