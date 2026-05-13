//*****************************************************************************
// purpose: driver for Project Part 4 (parser for TIPS)
// version: Spring 2023
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;
#include "productions.h"


extern "C" {
    // Instantiate global variables
    extern FILE *yyin; // input stream
    extern FILE *yyout; // output stream
    extern int yyleng; // length of current lexeme
    extern char *yytext; // text of current lexeme
    extern int yylineno; // line number for current lexeme
    extern int yylex(); // the generated lexical analyzer
}

// Needed global variables
extern int nextToken; // token returned from yylex


// Feel free to use a different data structure for the symbol table (list of
// variables declared in the program) but you will have to adjust the code in
// main() to print out the symbol table after a successful parse



//*****************************************************************************
// The main processing loop
//
int main(int argc, char* argv[]) {

    // Set the input stream
    if (argc > 1) {
        printf("INFO: Using the %s file for input\n", argv[1]);
        yyin = fopen(argv[1], "r"); 
    }
    else {
        printf("INFO: Using the sample.pas file for input\n");
        yyin = fopen("sample.pas", "r");
    }
  
    if (!yyin) {
        printf("ERROR: input file not found\n");
        return EXIT_FAILURE;
    }

    // Set the output stream
    yyout = stdout;

    // Get the first token
    nextToken = yylex();
    // Create the root of the parse tree
    PrgmNode* root = nullptr;
    // Fire up the parser!
    try {
        
        do {
        root = program(); // start symbol is <prgm>
        } while (nextToken != TOK_EOF);

        if (nextToken != TOK_EOF)
            throw "end of file expected, but there is more here!";
        
    } catch (char const *errmsg) {
        cout << endl << "***ERROR:" << endl;
        cout << "On line number " << yylineno << ", near " << yytext << ", error type ";
        cout << errmsg << endl;
        return EXIT_FAILURE;
    }

    // Tell the world about our success!!
    cout << endl << "=== GO BULLDOGS! Your parse was successful! ===" << endl;
  

    // Print out the symbol table
    cout << endl << "User Defined Symbols:" << endl;
    map<string, int>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        cout << it->first << endl;
    }
    // Print out the parse tree
    cout << endl << "*** In order traversal of parse tree ***" << endl;
    cout << *root << endl << endl;
    cout << "*** Interpreting the TIPS program ***" << endl;
    // Interpret the parse tree
    root->interpret();
    cout << endl;
    cout << "*** Delete the parse tree ***" << endl;
    delete root; // delete the parse tree
    root = nullptr; // set the root to nullptr
    return EXIT_SUCCESS;
}

