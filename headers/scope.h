#ifndef K_SCOPE_H
#define K_SCOPE_H
#include "../utools/definitions.h"

typedef struct Scope // okay.generic.scope
{
	size_t size;
	struct Node** structure;

} Scope;

// Creates a new scope.
// [okay.scope.scnew]
_unhandled Scope* scnew();

#endif