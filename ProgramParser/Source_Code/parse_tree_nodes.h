/****************************************************************************************************************
  Name: Bryan Johnson             NetID: btj117
  Course: CSE 4714              Assignment: Part 4 
  Programming Environment: Visual Studio Code
  Purpose of File: Contains node class for parse tree such as IdNode, IntLitNode, compoundNode, etc. 
  				   Also contains the interpreter functions for each node.
****************************************************************************************************************/

#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "lexer.h"

using namespace std;

// Forward declaration of <expr> node
class ExprNode;
class compoundNode;
class statementNode;
class PrgmNode;
map<string, int> symbolTable;
// Forward declaration of operator<< for ExprNode
ostream& operator<<(ostream& os, ExprNode& en);
ostream& operator<<(ostream& os, PrgmNode& pn);
ostream& operator<<(ostream& os, compoundNode& cn);
ostream& operator<<(ostream& os, statementNode& sn);

//*****************************************************************************
// Abstract class. Base class for IdNode, IntLitNode, NestedExprNode.
class FactorNode {
public:
	virtual int interpret() = 0;
    virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
    virtual ~FactorNode(); // labeling the destructor as virtual allows 
	                       // the subclass destructors to be called
						    // TOK_MULT_OP or TOK_DIV_OP
  
};

FactorNode::~FactorNode() {}

// Uses double dispatch to call the overloaded method printTo in the 
// FactorNodes: IdNode, IntLitNode, and NestedExprNode
ostream& operator<<(ostream& os, FactorNode& fn) {
	fn.printTo(os);
	os << " )";
	return os;
}

//*****************************************************************************
// class IdNode (Identifier Node)
class IdNode : public FactorNode {
public:
    string* id = nullptr;
	int value = 0;
	int interpret();
    IdNode(string name);
    ~IdNode();
    void printTo(ostream & os);
};

IdNode::IdNode(string name) {
	id = new string(name);
}

IdNode::~IdNode() {
	cout << "Deleting a factorNode" << endl;
	delete id;
	id = nullptr;
}

void IdNode::printTo(ostream& os) {
	os << " factor( " << *id;
}

int IdNode::interpret(){
	int result = 0;
	if (symbolTable.find(*id) != symbolTable.end()) {
		result = symbolTable[*id];
	}
	return result;
}

//*****************************************************************************
// class IntLitNode (Integer Literal Node)
class IntLitNode : public FactorNode {
public:
    int int_literal = 0;

    IntLitNode(int value);
    ~IntLitNode();
    void printTo(ostream & os);
	int interpret();
};

IntLitNode::IntLitNode(int value) {
	int_literal = value;
}

IntLitNode::~IntLitNode() {
	cout << "Deleting a factorNode" << endl;
	// Nothing to do since the only member variable is not a pointer
}

void IntLitNode::printTo(ostream& os) {
	os << " factor( " << int_literal;
}

int IntLitNode::interpret(){
    return int_literal;   
}

//*****************************************************************************
// class FloatLitNode (Float Literal Node)
class FloatLitNode : public FactorNode {
public:
    float float_literal = 0;

    FloatLitNode(float value);
	int interpret();
    ~FloatLitNode();
    void printTo(ostream & os);
};

FloatLitNode::FloatLitNode(float value) {
	float_literal = value;
}

FloatLitNode::~FloatLitNode() {
	cout << "Deleting a factorNode" << endl;
	// Nothing to do since the only member variable is not a pointer
}

void FloatLitNode::printTo(ostream& os) {
	os << " factor( " << float_literal;
}

int FloatLitNode::interpret(){
	return float_literal;   
}

//*****************************************************************************
// class NotFactorNode (Not Node)
class NotFactorNode : public FactorNode {
public:
    FactorNode* factorPtr = nullptr;
    NotFactorNode(FactorNode* fn);
    void printTo(ostream & os);
	int interpret();
    ~NotFactorNode();
};

NotFactorNode::NotFactorNode(FactorNode* fn) {
	factorPtr = fn;
}

void NotFactorNode::printTo(ostream& os) {
	os << " factor(" << (" NOT") << *factorPtr;
}

int NotFactorNode::interpret(){
	return 1;   
}

//*****************************************************************************
// class MinusFactorNode (Minus Node)
class MinusFactorNode : public FactorNode {
public:
    FactorNode* factorPtr = nullptr;
    MinusFactorNode(FactorNode* fn);
	int interpret();
    void printTo(ostream & os);
    ~MinusFactorNode();
};

MinusFactorNode::MinusFactorNode(FactorNode* fn) {
	factorPtr = fn;
}

void MinusFactorNode::printTo(ostream& os) {
	os << " factor(" << (" -") << *factorPtr;
}

int MinusFactorNode::interpret(){
	return 1;   
}

//*****************************************************************************
// class NestedExprNode (Nested Expression Node)
class NestedFactorExprNode : public FactorNode {
public:
    ExprNode* exprPtr = nullptr;
	int interpret();
    NestedFactorExprNode(ExprNode* en);
    void printTo(ostream & os);
    ~NestedFactorExprNode();
};

NestedFactorExprNode::NestedFactorExprNode(ExprNode* en) {
	exprPtr = en;
}

void NestedFactorExprNode::printTo(ostream& os) {
	os.clear();
	os << " nested_expression(" << *exprPtr;
}

//*****************************************************************************
// class TermNode (Terminal Node)
class TermNode {
public:
    FactorNode* firstFactor = nullptr;
    vector<int> restFactorOps; // TOK_MULT_OP or TOK_DIV_OP
    vector<FactorNode*> restFactors;
	int interpret();
    ~TermNode();
};

ostream& operator<<(ostream& os, TermNode& tn) {
	os << " term(";
	os << *(tn.firstFactor);

	int length = tn.restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		int op = tn.restFactorOps[i];
		if (op == TOK_MULTIPLY)
			os << " *";
		else if (op == TOK_DIVIDE)
			os << " /";
		else
			os << " and";
		os << *(tn.restFactors[i]);
	}
	os << " )";
	return os;
}

TermNode::~TermNode() {
	cout << "Deleting a termNode" << endl;
	delete firstFactor;
	firstFactor = nullptr;

	int length = restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		delete restFactors[i];
		restFactors[i] = nullptr;
	}
}

int TermNode::interpret(){
	int result = firstFactor->interpret();
	int length = restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		int op = restFactorOps[i];
		if (op == TOK_MULTIPLY)
			result *= restFactors[i]->interpret();
		else if (op == TOK_DIVIDE)
			result /= restFactors[i]->interpret();
	}
	return result;
}

//*****************************************************************************
// class SimpExprNode (Simple Expression Node)
class SimpExprNode {
public:
    TermNode* firstTerm = nullptr;
    vector<int> restTermOps; // TOK_ADD_OP or TOK_SUB_OP
    vector<TermNode*> restTerms;
	int interpret();
    ~SimpExprNode();
};

ostream& operator<<(ostream& os, SimpExprNode& en) {
	os << " simple_expression(";
	os << *(en.firstTerm);

	int length = en.restTermOps.size();
	for (int i = 0; i < length; ++i) {
		int op = en.restTermOps[i];
		if (op == TOK_PLUS)
			os << " +";
		else if (op == TOK_MINUS)
			os << " -";
		else
			os << " or";
		os << *(en.restTerms[i]);
	}
	os << " )";
	return os;
}

SimpExprNode::~SimpExprNode() {
	cout << "Deleting a simpleExpressionNode" << endl;
	delete firstTerm;
	firstTerm = nullptr;

	int length = restTermOps.size();
	for (int i = 0; i < length; ++i) {
		delete restTerms[i];
		restTerms[i] = nullptr;
	}
}

int SimpExprNode::interpret(){
	int result = firstTerm->interpret();
	int length = restTermOps.size();
	for (int i = 0; i < length; ++i) {
		int op = restTermOps[i];
		if (op == TOK_PLUS)
			result += restTerms[i]->interpret();
		else
			result -= restTerms[i]->interpret();
	}
	return result;
}

//*****************************************************************************
// class ExprNode (Expression Node)
class ExprNode {
public:
    SimpExprNode* firstExp = nullptr;
    vector<int> restExpOps;
    vector<SimpExprNode*> restExps;
	int interpret();
    ~ExprNode();
};

ostream& operator<<(ostream& os, ExprNode& en) {
	os << " expression(";
	os << *(en.firstExp);

	int length = en.restExpOps.size();
	for (int i = 0; i < length; ++i) {
		int op = en.restExpOps[i];
		if (op == TOK_LESSTHAN)
			os << " <";
		else if (op == TOK_GREATERTHAN)
			os << " >";
		else if (op == TOK_EQUALTO)
			os << " =";
		else
			os << " <>";
		os << *(en.restExps[i]);
	}
	os << " )";
	return os;
}

ExprNode::~ExprNode() {
	cout << "Deleting an expressionNode" << endl;
	delete firstExp;
	firstExp = nullptr;

	int length = restExpOps.size();
	for (int i = 0; i < length; ++i) {
		delete restExps[i];
		restExps[i] = nullptr;
	}
}

int ExprNode::interpret(){
	int result = firstExp->interpret();
	int length = restExpOps.size();
	for (int i = 0; i < length; ++i) {
		int op = restExpOps[i];
		if (op == TOK_LESSTHAN)
			result = result < restExps[i]->interpret();
		else if (op == TOK_GREATERTHAN)
			result = result > restExps[i]->interpret();
		else if (op == TOK_EQUALTO)
			result = result == restExps[i]->interpret();
		else
			result = result != restExps[i]->interpret();
	}

	return result;
}

//*****************************************************************************
// class ifNode (If Node)
class ifNode {
	public:
		ExprNode* exprPtr = nullptr;
		statementNode* statement = nullptr;
		statementNode* elseStatement = nullptr;
		vector<int> restIfOps;
		int interpret();
		~ifNode();
};

ostream& operator<<(ostream& os, ifNode& in) {
	os << "If";
	os << *(in.exprPtr);
	int length = in.restIfOps.size();
	for (int i = 0; i < length; ++i) {
		int op = in.restIfOps[i];
		if (op == TOK_THEN)
		{
			os << endl;
			os << "%%%%%%%% True Statement %%%%%%%%" << endl;
			os << *(in.statement);
			os << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		}
		else if (op == TOK_ELSE)
		{
			os << "%%%%%%%% False Statement %%%%%%%%" << endl;
			os << *(in.elseStatement);
			os << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		}
	}
	return os;
}

//*****************************************************************************
// class whileNode (While Node)
class whileNode {
	public:
		ExprNode* exprPtr = nullptr;
		statementNode* statement = nullptr;
		vector<int> restIfOps;
		int interpret();
		~whileNode();
};

ostream& operator<<(ostream& os, whileNode& in) {
	os << "While";
	os << *(in.exprPtr) << endl;
	os << "%%%%%%%% Loop Body %%%%%%%%" << endl;
	os << *(in.statement);
	os << "%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	return os;
}


//*****************************************************************************
// class readNode (Read Node)
class readNode{
	public:
		string* value = nullptr;
		int interpret();
		readNode(string name);
		~readNode();
};

readNode::readNode(string name) {
	value = new string(name);
}

readNode::~readNode() {
	cout << "Deleting a readNode" << endl;
}

ostream& operator<<(ostream& os, readNode& rn) {
	os << "Read Value ";
	os << *(rn.value) << endl;
	return os;
}
int readNode::interpret(){
	int input;
	cin >> input;
	symbolTable[*(value)] = input;
	return input;
}

//*****************************************************************************
// class assignmentNode (Statement Node)
class assignmentNode {
	public:
		ExprNode* expr = nullptr;
		string* value = nullptr;
		vector<int> AssignOps;
		int interpret();
		assignmentNode(string name);
		~assignmentNode();
};

assignmentNode::assignmentNode(string name) {
	value = new string(name);
}

assignmentNode::~assignmentNode() {
	cout << "Deleting an assignmentNode" << endl;
	delete value;
	value = nullptr;
	delete expr;
	expr = nullptr;
}

ostream& operator<<(ostream& os, assignmentNode& an) {
	os << "Assignment ";
	os << *(an.value);
	if (an.AssignOps[0] == TOK_ASSIGN)
		os << " :=";
	os << *(an.expr) << endl;
	return os;
}

int assignmentNode::interpret(){
	int result = expr->interpret();
	return result;
}


//*****************************************************************************
// class writeNode (Read Node)
class writeNode{
	public:
		string* value = nullptr;
		vector<int> WriteOps;
		int interpret();
		writeNode(string name);
		~writeNode();
};

writeNode::writeNode(string name) {
	value = new string(name);
}

writeNode::~writeNode() {
	cout << "Deleting a writeNode" << endl;
	delete value;
	value = nullptr;
}

ostream& operator<<(ostream& os, writeNode& wn) {
	if (wn.WriteOps[0] == TOK_IDENT)
	{
		os << "Write Value ";
		os << *(wn.value) << endl;	
	}
	else if (wn.WriteOps[0] == TOK_STRINGLIT)
	{
		os << "Write String ";
		os << *(wn.value) << endl;
	}
	return os;
}

int writeNode::interpret(){
	int result = symbolTable[*(value)];
	return result;
}

//*****************************************************************************
// class statementNode (Statement Node)
class statementNode {
	public:
		readNode* read = nullptr;
		ifNode* ifn = nullptr;
		compoundNode* compound = nullptr;
		assignmentNode* assign = nullptr;
		writeNode* writestat = nullptr;
		whileNode* whilestat = nullptr;
		int interpret();
		~statementNode();
};

ostream& operator<<(ostream& os, statementNode& sn) {
	if (sn.read)
	{
		os << *(sn.read);
	}
	else if (sn.ifn)
	{
		os << *(sn.ifn);
	}
	else if (sn.writestat)
	{
		os << *(sn.writestat);
	}
	else if (sn.compound)
	{
		os << *(sn.compound);
	}
	else if (sn.assign)
	{
		os << *(sn.assign);
	}
	else if (sn.whilestat)
	{
		os << *(sn.whilestat);
	}
	return os;
	
}



//*****************************************************************************
// class compoundNode (Compound Statement Node)
class compoundNode {
	public:
		statementNode* firstStatement = nullptr;
		vector<statementNode*> restStates;
		vector<int> restStatesOps;
		int interpret();
		~compoundNode();
};

ostream& operator<<(ostream& os, compoundNode& cn) {
	os << "Begin Compound Statement" << endl;
	os << *(cn.firstStatement);
	int length = cn.restStatesOps.size();
	for (int i = 0; i < length; ++i) {
		int op = cn.restStatesOps[i];
		os << *(cn.restStates[i]);
	}
	os << "End Compound Statement" << endl;
	return os;
}

compoundNode::~compoundNode() {
	cout << "Deleting a compoundNode" << endl;
	delete firstStatement;
	firstStatement = nullptr;

	int length = restStatesOps.size();
	for (int i = 0; i < length; ++i) {
		delete restStates[i];
		restStates[i] = nullptr;
	}
}

int compoundNode::interpret() {
	int length = restStatesOps.size();
	int result = firstStatement->interpret();
	for (int i = 0; i < length; ++i) {
		int op = restStatesOps[i];
		result = restStates[i]->interpret();
	}
	
	return result;
}

//*****************************************************************************
// class blockNode (Block Node)
class blockNode {
	public:
		compoundNode* compoundState = nullptr;
		int interpret();
		~blockNode();
};

blockNode::~blockNode() {
	cout << "Deleting a blockNode" << endl;
	delete compoundState;
	compoundState = nullptr;
}

ostream& operator<<(ostream& os, blockNode& bn) {
	os << *(bn.compoundState);
	return os;
}

int blockNode::interpret() {
	return compoundState->interpret();
}

//*****************************************************************************
// class PrgmNode (Program Node)
class PrgmNode{
public:
    string* id = nullptr;
    PrgmNode(string name);
	blockNode* block = nullptr;
	int interpret();
    ~PrgmNode();
};

PrgmNode::PrgmNode(string name) {
	id = new string(name);
}

ostream& operator<<(ostream& os, PrgmNode& pn) {
	os << "Program Name ";
	os << *(pn.id) << endl;
	os << *(pn.block);
	return os;
}

PrgmNode::~PrgmNode() {
	cout << "Deleting a programNode" <<endl;
	delete id;
	id = nullptr;
	delete block;
	block = nullptr;
}

int PrgmNode::interpret() {
	return block->interpret();
}

//*****************************************************************************
// interpreter functions
//*****************************************************************************
int statementNode::interpret()
{
	static int result = 0;
	if (assign)
	{
		result = assign->interpret();
		symbolTable[*(assign->value)] = result;
		return result;
	}
	else if (read)
	{
		result = read->interpret();
		return result;
	}
	else if (writestat)
	{

		if (symbolTable.find(*(writestat->value)) != symbolTable.end() && result != 0)
		{
			cout << result << endl;
		}
		else if (result != 0)
		{
			string temp = *(writestat->value);
			symbolTable[*(writestat->value)] = result;
			temp.erase(remove(temp.begin(), temp.end(), '\''), temp.end());
			cout << temp << endl;
		}
		else if (result == 0)
		{
			string temp = *(writestat->value);
			symbolTable[*(writestat->value)] = result;
			temp.erase(remove(temp.begin(), temp.end(), '\''), temp.end());
			cout << temp << endl;
		}
		
		return result;
	}
	else if (ifn)
	{
		result = ifn->interpret();
		return result;	
	}
	else if (compound)
	{
		result = compound->interpret();
	}
	else if (whilestat)
	{
		result = whilestat->interpret();
	}
	return result;
}

int ifNode::interpret(){
	int result = exprPtr->interpret();
	if (result != 0)
	{
		string temp = *(statement->writestat->value);
		temp.erase(remove(temp.begin(), temp.end(), '\''), temp.end());
		cout << temp << endl;
		return 0;
	}
		
	else if (result == 0)
	{
		string temp = *(elseStatement->writestat->value);
		temp.erase(remove(temp.begin(), temp.end(), '\''), temp.end());
		cout << temp << endl;
		return 0;
	}
	return 0;
}

int whileNode::interpret(){
	int result = exprPtr->interpret();
	while (result != 0)
	{
		statement->interpret();
		result = exprPtr->interpret();
	}
	return 0;
}

int NestedFactorExprNode::interpret(){
    return exprPtr->interpret();
}

//*****************************************************************************
// destructors
//*****************************************************************************

NestedFactorExprNode::~NestedFactorExprNode() {
	cout << "Deleting a factorNode" << endl;
	delete exprPtr;
	exprPtr = nullptr;
}

NotFactorNode::~NotFactorNode() {
	cout << "Deleting a factorNode" << endl;
	delete factorPtr;
	factorPtr = nullptr;
}
MinusFactorNode::~MinusFactorNode() {
	cout << "Deleting a factorNode" << endl;
	delete factorPtr;
	factorPtr = nullptr;
}
// 
statementNode::~statementNode() {
	delete read;
	read = nullptr;
	delete compound;
	compound = nullptr;
	delete writestat;
	writestat = nullptr;
	delete whilestat;
	whilestat = nullptr;
	delete ifn;
	ifn = nullptr;
	delete assign;
	assign = nullptr;
} 
ifNode::~ifNode() {
	cout << "Deleting an ifNode" << endl;
	delete exprPtr;
	exprPtr = nullptr;
	delete statement;
	statement = nullptr;
	delete elseStatement;
	elseStatement = nullptr;
}

whileNode::~whileNode() {
	cout << "Deleting a whileNode" << endl;
	delete exprPtr;
	exprPtr = nullptr;
	delete statement;
	statement = nullptr;
}
//*****************************************************************************
#endif /* PARSE_TREE_NODES_H */
