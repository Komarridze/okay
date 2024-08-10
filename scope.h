#pragma once
#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT {
	AST_T** fdefs;
	size_t fdefs_size;
} scope_T;

scope_T* init_scope();

AST_T* scope_addfdef(scope_T* scope, AST_T* fdef);

AST_T* scope_getfdef(scope_T* scope, const char* fname);
#endif // !SCOPE_H
