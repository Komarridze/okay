#pragma once
#include "AST.h"

typedef struct SCOPE_STRUCT {
	AST_T** fdefs;
	size_t fdefs_size;

	AST_T** srcdefs;
	size_t srcdefs_size;

} scope_T;

scope_T* init_scope();

AST_T* scope_addfdef(scope_T* scope, AST_T* fdef);

AST_T* scope_getfdef(scope_T* scope, const char* fname);

AST_T* scope_addsrcdef(scope_T* scope, AST_T* fdef);

AST_T* scope_getsrcdef(scope_T* scope, const char* fname);

