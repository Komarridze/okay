#ifndef K_DECL_H
#define K_DECL_H
#include "../utools/definitions.h"

typedef struct Decl // okay.generic.decl
{
	int Decltype;

	char* declname; // save & alias

	struct Node* value; // save
	struct Node* algo; // alias



	struct Scope* scope;

} Decl;

// Creates a new scope.
// [okay.decl.crdecl]
_unhandled Decl* crdecl();

#endif