/****************************************************************************************************************
  Name: Bryan Johnson             NetID: btj117
  Course: CSE 4714              Assignment: Part 4 
  Programming Environment: Visual Studio Code
  Purpose of File: Contains functions for program parsing such as block, statement, compound statement parsing, etc.
****************************************************************************************************************/

#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H

#include <iostream>
#include "parse_tree_nodes.h"

extern map<string, int> symbolTable;
int nextToken = 0;  // token returned from yylex
int level = 0;  // used to indent output to approximate parse tree


extern "C"
{
	// Instantiate global variables used by flex
	extern char* yytext;       // text of current lexeme
	extern int   yylex();      // the generated lexical analyzer
}
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }
  return nextToken;
}

// Forward declarations of production parsing functions
PrgmNode* program();


// Forward declarations of functions that check whether the current token is
// in the first set of a production rule
bool first_of_program();
bool ident();
bool semicolon();
bool var();
bool begin();
bool colon();
bool integer();
bool real();
bool end();
bool tok_if();
bool tok_read();
bool tok_while();
bool tok_write();
bool tok_then();
bool tok_else();
bool lessthan();
bool greaterthan();
bool equalto();
bool notequalto();
bool tok_plus();
bool tok_minus();
bool tok_or();
bool tok_multi();
bool tok_divide();
bool tok_and();
bool tok_int_lit();
bool tok_float_lit();
bool tok_string_lit();
bool tok_not();
readNode* read_statement();
blockNode* block();
statementNode* statement();
compoundNode* compound_statement();
ifNode* if_statement();
whileNode* while_statement();
writeNode* write_statement();
ExprNode* expression();
SimpExprNode* simple_expression();
TermNode* term();
FactorNode* factor();
assignmentNode* assignment_statement();


inline void indent(){
    for (int i = 0; i<level; i++)
        cout << ("    ");
}

void output(){
    indent();
    cout << "-->found " << yytext << endl;
}


PrgmNode* program() {

    if (!first_of_program()) // Check for PROGRAM
        throw "3: 'PROGRAM' expected";
    
    indent();
    cout << "enter <program>" << endl;
    ++level;
    output();
    lex();
    PrgmNode* newPrgmNode = new PrgmNode(string(yytext));
    if (!ident())
        throw "2: identifier expected";
    output();
    lex();
    if (!semicolon())
        throw "14: ';' expected";
    output();
    lex();

    newPrgmNode->block = block();

    --level;
    indent();
    cout << "exit <program>" << endl;
    return newPrgmNode;  
}


//*****************************************************************************


// boolean functions for checking nextToken value
//************************************************
bool first_of_program(void) {
    return nextToken == TOK_PROGRAM;
}

bool ident(void)
{
  return nextToken == TOK_IDENT;
}

bool semicolon(void)
{
    return nextToken == TOK_SEMICOLON;
}
bool var(void)
{
    return nextToken == TOK_VAR;
}

bool begin(void)
{
    return nextToken == TOK_BEGIN;
}

bool colon(void)
{
    return nextToken == TOK_COLON;
}

bool integer(void)
{
    return nextToken == TOK_INTEGER;
}

bool real(void)
{
    return nextToken == TOK_REAL;
}

bool tok_if(void)
{
    return nextToken == TOK_IF;
}

bool tok_while(void)
{
    return nextToken == TOK_WHILE;
}

bool tok_read(void)
{
    return nextToken == TOK_READ;
}

bool tok_write(void)
{
    return nextToken == TOK_WRITE;
}

bool tok_then(void)
{
    return nextToken == TOK_THEN;
}

bool tok_else(void)
{
    return nextToken == TOK_ELSE;
}

bool open_paren(void)
{
    return nextToken == TOK_OPENPAREN;
}

bool close_paren(void)
{
    return nextToken == TOK_CLOSEPAREN;
}

bool equalto(void)
{
    return nextToken == TOK_EQUALTO;
}

bool notequalto(void)
{
    return nextToken == TOK_NOTEQUALTO;
}

bool lessthan(void)
{
    return nextToken == TOK_LESSTHAN;
}

bool greaterthan(void)
{
    return nextToken == TOK_GREATERTHAN;
}

bool tok_plus(void)
{
    return nextToken == TOK_PLUS;
}

bool tok_minus(void)
{
    return nextToken == TOK_MINUS;
}

bool tok_or(void)
{
    return nextToken == TOK_OR;
}

bool tok_multi(void)
{
    return nextToken == TOK_MULTIPLY;
}

bool tok_divide(void)
{
    return nextToken == TOK_DIVIDE;
}

bool tok_and(void)
{
    return nextToken == TOK_AND;
}

bool tok_int_lit(void)
{
    return nextToken == TOK_INTLIT;
}

bool tok_float_lit(void)
{
    return nextToken == TOK_FLOATLIT;
}

bool tok_string_lit(void)
{
    return nextToken == TOK_STRINGLIT;
}

bool tok_not(void)
{
    return nextToken == TOK_NOT;
}

bool tok_assign(void)
{
    return nextToken == TOK_ASSIGN;
}

bool tok_end(void)
{
    return nextToken == TOK_END;
}

//************************************************

// block parsing function
blockNode* block()
{
    blockNode* newBlockNode = new blockNode;
    if (begin())
    {
        indent();
        cout << "enter <block>" << endl;
        ++level;
        newBlockNode->compoundState = compound_statement();
    }
        
        
    if (!begin())
        if (!var())
            throw "18: error in declaratin part or 17: 'BEGIN' expected";
        indent();
        cout << "enter <block>" << endl;
        ++level;
        output();
        lex();
        
    
    while(!begin())
    {   
        if (symbolTable.find(yytext) != symbolTable.end())
            throw "101: identifier declared twice";
        symbolTable.insert(std::make_pair(yytext, 0));
    
        if (!ident())
        throw "2: identifier expected";
        output();
        lex();
        if (!colon())
            throw "5: ':' expected";
        output();
        lex();
        if (!integer() && !real())
            throw "10: error in type";
        output();
        lex();
        if (!semicolon())
        throw "14: ';' expected";
        output();
        lex();
        cout << endl;
    }
    // begin found enter compound statement

    newBlockNode->compoundState = compound_statement();
    --level;
    indent();
    cout << "exit <block>" << endl;
    return newBlockNode;  
}

// statement parsing function
statementNode* statement()
{
    indent();
    cout << "enter <statement>" << endl;
    ++level;
    statementNode* newStatementNode = new statementNode;
    // check for identifier and that identifier has been declared
    if (ident())
    {
        newStatementNode->assign = assignment_statement();
    }
    // if begin token found enter compound statement
    if (begin())
    {
        newStatementNode->compound = compound_statement();
        
    }
    // if read token found enter read statement    
    if (tok_read())
    {
       newStatementNode->read = read_statement();
    }
    // if IF token found enter IF statement    
    if (tok_if())
    {
        newStatementNode->ifn = if_statement();
    }
    // if write token found enter write statement
    if (tok_write())
    {
        newStatementNode->writestat = write_statement();
    }
    // if while token found enter while statement    
    if (tok_while())
    {
        newStatementNode->whilestat = while_statement();
    }
    --level;
    indent();
    cout << "exit <statement>" << endl;
    return newStatementNode;
}
// compound statement parsing function
compoundNode* compound_statement()
{
    // check that compound statement starts with begin token
    if (!begin())
        throw "17: 'BEGIN' expected";
    indent();
    cout << "enter <compound_statement>" << endl;
    compoundNode* newCompoundNode = new compoundNode;
    ++level;
    output();
    lex();
    // enter statement
    newCompoundNode->firstStatement = statement();
    // if there is a semicolon keep parsing statements
    while(semicolon())
        {
            output();
            newCompoundNode->restStatesOps.push_back(nextToken);
            lex();
            newCompoundNode->restStates.push_back(statement());
        }
    if (tok_end())
    {
        output();
        lex();
        --level;
        indent();
        cout << "exit <compound_statement>" << endl;
    }
    return newCompoundNode;
}
// if statement function
ifNode* if_statement()
{
    // check for if token at start of statement
    if (!tok_if())
        throw "900: illegal type of statement";
    indent();
    cout << "enter <if statement>" << endl;
    ++level;
    ifNode* newIfNode = new ifNode;
    output();
    lex();
    newIfNode->exprPtr = (expression());
    if (tok_then())
    {
        output();
        newIfNode->restIfOps.push_back(nextToken);
        lex();
        newIfNode->statement = statement();
    }
    if (tok_else())
    {
        output();
        newIfNode->restIfOps.push_back(nextToken);
        lex();
        newIfNode->elseStatement = statement();
    }
    --level;
    indent();
    cout << "exit <if statement>" << endl;
    return newIfNode;
}
// read statement function
readNode* read_statement()
{
    // check for read token at start of statement
    if (!tok_read())
        throw "900: illegal type of statement";
    indent();
    cout << "enter <read>" << endl;
    readNode* newReadNode = nullptr;
    ++level;
    output();
    lex();
    // check for parenthesis enclosing identifier
    if (!open_paren())
        throw "9: '(' expected";
    output();
    lex();
    newReadNode = new readNode(string(yytext));
    if (!ident())
        throw "2: identifier expected";
    output();
    lex();
    if (!close_paren())
        throw "4: ')' expected";
    output();
    lex();

    --level;
    indent();
    cout << "exit <read>" << endl;
    //cout << newReadNode;
    return newReadNode;
}

// assignment statement parsing function
assignmentNode* assignment_statement()
{
    assignmentNode* newAssignmentNode = new assignmentNode(string(yytext));
    // check for identifier and that identifier has been declared
  
    indent();
    cout << "enter <assignment>" << endl;
    if (symbolTable.find(yytext) == symbolTable.end())
        throw "104: identifier not declared";
    ++level;
    output();
    lex();
    newAssignmentNode->AssignOps.push_back(nextToken);
    if (!tok_assign())
        throw "assign error";
    output();
    lex();
    newAssignmentNode->expr = expression();
    --level;
    indent();
    cout << "exit <assignment>" << endl;

    return newAssignmentNode;
}

// write statement parsing function
writeNode* write_statement()
{
    writeNode* newWriteNode = nullptr;
    // check for write token at start of statement
    if (!tok_write())
        throw "900: illegal type of statement";
    indent();
    cout << "enter <write>" << endl;
    ++level;
    output();
    lex();
    // check for identifier or string literal enclosed by parentheses
    if (!open_paren())
        throw "9: '(' expected";
    
    output();
    lex();

    if (!ident() && !tok_string_lit())
        throw "134: illegal type of opreand(s)";
    
    output();
    newWriteNode = new writeNode(string(yytext));
    newWriteNode->WriteOps.push_back(nextToken);
    lex();
    
    if (!close_paren())
        throw "4: ')' expected";
    
    output();
    lex();
    
    --level;
    indent();
    cout << "exit <write>" << endl;
    return newWriteNode;
}
// while statement parsing function
whileNode* while_statement()
{
    whileNode* newWhileNode = new whileNode;
    // check for while token at start of statement
    if (!tok_while())
        throw "900: illegal type of statement";
    indent();
    cout << "enter <while statement>" << endl;
    ++level;
    output();
    lex();
    // enter expression followed by statement
    newWhileNode->exprPtr = expression();
    newWhileNode->statement = statement();
    --level;
    indent();
    cout << "exit <while statement>" << endl;
    return newWhileNode;
}

// expression parsing function
ExprNode* expression()
{
    // check for literals, paranthesis, not, minus at start of expression
    if (!tok_int_lit() && !tok_float_lit() && !ident() && !open_paren() && !tok_not()
        && !tok_minus())
        throw "144: illegal type of expression";
    indent();
    cout << "enter <expression>" << endl;
    ++level;
    ExprNode* newExprNode = new ExprNode;
    newExprNode->firstExp = simple_expression();
    // check for comparison operators and enter simple expression
    while(equalto() || notequalto() || greaterthan() || lessthan())
    {
        output();
        newExprNode->restExpOps.push_back(nextToken);
        lex();
        newExprNode->restExps.push_back(simple_expression());
    }
    --level;
    indent();
    cout << "exit <expression>" << endl;
    return newExprNode;
}

// simple expression parsing statement
SimpExprNode* simple_expression()
{
    indent();
    cout << "enter <simple expression>" << endl;
    ++level;
    SimpExprNode* newSimpExprNode = new SimpExprNode;
    newSimpExprNode->firstTerm = term();

    while(tok_plus() || tok_minus() || tok_or())
    {
        output();
        newSimpExprNode->restTermOps.push_back(nextToken);
        lex();
        newSimpExprNode->restTerms.push_back(term());
    }
       

    --level;
    indent();
    cout << "exit <simple expression>" << endl;
    return newSimpExprNode;
}

// term parsing statement
TermNode* term()
{
    indent();
    cout << "enter <term>" << endl;
    ++level;
    TermNode* newTermNode = new TermNode;
    newTermNode->firstFactor = factor();
    // after first factor parse check for successive operations and parse factors
    while((tok_multi() || tok_divide() || tok_and()))
    {
        output();
        newTermNode->restFactorOps.push_back(nextToken);
        lex();
        newTermNode->restFactors.push_back(factor());
    }   

    
    --level;
    indent();
    cout << "exit <term>" << endl;
    return newTermNode;
}

// factor parsing function
FactorNode* factor()
{
    indent();
    cout << "enter <factor>" << endl;
    ++level;
    FactorNode* newFactorNode = nullptr;
    // check for literals or identifier
    if (!tok_int_lit() && !tok_float_lit() && !ident())
    {
        // check for expressions enclosed by parenthesis
        if (open_paren())
        {
            output();
            lex();
            newFactorNode = new NestedFactorExprNode(expression());
        }
        if (close_paren())
        {
            output();
            lex();
        }
        // check for not or minus operation and begin parsing for factor
        if (tok_not())
        {
            output();
            lex();
            newFactorNode = new NotFactorNode(factor());
            
        }    
        if (tok_minus())
        {
            output();
            lex();
            newFactorNode = new MinusFactorNode(factor());
            
        }    
    }
    else
    {
        if (ident())
        {
            int result = 0;
            if (symbolTable.find(yytext) == symbolTable.end())
                throw "104: identifier not declared";
            newFactorNode = new IdNode(string(yytext));
        }
        if (tok_int_lit())
        {   
            for (auto rit = symbolTable.rbegin(); rit != symbolTable.rend(); ++rit) 
            {
                // If the value is 0, update it with a new integer value
                if (rit->second == 0) {
                    rit->second = stoi(yytext); // Assign the new integer value to the current element
                    break; // Exit the loop after updating the first key-value pair with value 0
                }
            }           
            newFactorNode = new IntLitNode(stoi(yytext));
        }
            
        if (tok_float_lit())
        {
            newFactorNode = new FloatLitNode(stof(yytext));
        }
        output();
        lex();
    }
    
    
    --level;
    indent();
    cout << "exit <factor>" << endl;
    return newFactorNode;
}           


#endif
