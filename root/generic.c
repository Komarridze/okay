#include "../utools/definitions.h"
#include "../headers/node.h"
#include "../headers/error.h"

_unhandled Scope* scnew() {
	Scope* scope = (Scope*)calloc(1, sizeof(Scope));

	if (scope)
	{
		scope->size = 0;
		scope->structure = NULL;

		return scope;
	}
	else
	{
		error(-1, 0, "generic.c");
		return NULL;
	}

}

_unhandled Node* crnode() {
	Node* node = (Node*)calloc(1, sizeof(Node));

	if (node)
	{
		node->Ntype = 0;
		node->Operation = 0;

		node->object = NULL;
		node->decl = NULL;

		node->lhs = NULL;
		node->rhs = NULL;

		node->scope = NULL;

		return node;
	}
	else
	{
		error(-1, 0, "generic.c");
		return NULL;
	}

}

_unhandled Object* crobj() {
	Object* object = (Object*)calloc(1, sizeof(Object));

	if (object)
	{
		object->Objtype = 0;

		object->sequence = NULL;
		object->name = "";

		object->number = 0;
		object->conversion = '\0';

		object->scope = NULL;
		return object;
	}
	else
	{
		error(-1, 0, "generic.c");
		return NULL;
	}
}

_unhandled Decl* crdecl() {
	Decl* decl = (Decl*)calloc(1, sizeof(Decl));

	if (decl)
	{
		decl->Decltype = 0;

		decl->declname = "";

		decl->value = NULL;
		decl->algo = NULL;



		decl->scope = NULL;

		return decl;
	}
	else
	{
		error(-1, 0, "generic.c");
		return NULL;
	}
}