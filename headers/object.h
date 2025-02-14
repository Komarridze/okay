#ifndef K_OBJECT_H
#define K_OBJECT_H
#include "../utools/definitions.h"

typedef struct Object// okay.generic.object
{
	int Objtype;

	struct Node* sequence; // sequence
	char* name; // string & alias

	double number; // int & float & bool
	char conversion; // int & float

	/*
		TO OPTIMIZE MEMORY USAGE:

		[name] is both the string value and the function name.
		[number] is a value of int and float OR 0/1 for boolean.
		[conversion] is a single char.

	*/

	struct Scope* scope;

} Object;

// Creates a new Object.
// [okay.object.crobj]
_unhandled Object* crobj();

#endif

