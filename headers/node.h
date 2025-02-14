#ifndef K_NODE_H
#define K_NODE_H
#include "../utools/definitions.h"
#include "../headers/object.h"
#include "../headers/decl.h"
#include "../headers/scope.h"

enum
{
	RET = -1,

	NOTHING = 0,
	OBJECT = 1,
	DECLARATION = 2,
	OPERATION = 3,
	GENERIC = 4,


	/*
	
	NOTHING IS VOID.
	
	OBJECT -> Object*;

	DECLARATION -> Decl*;

	OPERATION -> Node* (operation) Node*;

	GENERIC GOES TO FIRST NODE* SLOT;
	
	
	*/

	// GENERIC


	// UNARY
	CALL = 5, // CALL IS APPLIED TO Object* function
	NEG = 6,

	// BINARY
	ADD = 7,
	SUB = 8,
	MUL = 9,
	DIV = 10,

	SEQUENCE = 11,
	ALIAS,
	INT,
	FLOAT,
	STRING,
	BOOL,

	DSAVE = 17, // variable
	DALIAS // function

} Ntype;

typedef struct Node// okay.generic.node
{
	int Ntype;
	int Operation;

	struct Object* object; 
	struct Decl* decl;

	struct Node* lhs;
	struct Node* rhs;


	/*
		NODE CAN BE EITHER:
		0. NOTHING
		1. A SIMPLE OBJECT
		2. SOME DECLARATION
		3. AN OPERATION OF SORTS
		4. GENERIC NODE SPACE FOR WHICH
		IS RESERVED IN THE FIRST SLOT (lhs)
	*/


	Scope* scope;

} Node;

// Creates a new node.
// [okay.node.crnode]
_unhandled Node* crnode();





#endif
