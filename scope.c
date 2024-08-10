#include "scope.h"
#include <String.h>
#define notnullptr != '\0'

scope_T* init_scope() {
	scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));
	if (scope notnullptr) {
		scope->fdefs = (void*)0;
		scope->fdefs_size = 0;
	}

	return scope;
};

AST_T* scope_addfdef(scope_T* scope, AST_T* fdef) {
	scope->fdefs_size += 1;

	if (scope->fdefs == (void*)0) {
		scope->fdefs = calloc(1, sizeof(struct AST_STRUCT*));
	}
	else {
		scope->fdefs = realloc(scope->fdefs, scope->fdefs_size * sizeof(struct AST_STRUCT));

	}

	if (scope->fdefs notnullptr) {
		scope->fdefs[scope->fdefs_size - 1] = fdef;
	}

	return fdef;
};

AST_T* scope_getfdef(scope_T* scope, const char* fname) {
	for (int i = 0; i < scope->fdefs_size; i++) {
		AST_T* fdef = scope->fdefs[i];
		if (strcmp(fdef->fdefname, fname) == 0)
			return fdef;
	}

	return (void*)0;
};