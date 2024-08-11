#include "scope.h"
#include <String.h>
#define notnullptr != '\0'

scope_T* init_scope() {
	scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));
	if (scope notnullptr) {
		scope->fdefs = (void*)0;
		scope->fdefs_size = 0;

		scope->srcdefs = (void*)0;
		scope->srcdefs_size = 0;
	}

	return scope;
};

AST_T* scope_addfdef(scope_T* scope, AST_T* fdef) {
	scope->fdefs_size += 1;

	if (scope->fdefs == (void*)0) {
		scope->fdefs = calloc(1, sizeof(struct AST_STRUCT*));
	}
	else {
		struct AST_STRUCT** f = realloc(scope->fdefs, scope->fdefs_size * sizeof(struct AST_STRUCT));
		if (f != NULL) scope->fdefs = f;

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

AST_T* scope_addsrcdef(scope_T* scope, AST_T* srcdef) {
	if (scope->srcdefs == (void*)0) {
		scope->srcdefs = calloc(1, sizeof(struct AST_STRUCT*));
		if (scope->srcdefs notnullptr) {
			scope->srcdefs[0] = srcdef;
			scope->srcdefs_size += 1;
		}
	}
	else {
		scope->srcdefs_size += 1;
		struct AST_STRUCT** g = realloc(
			scope->srcdefs,
			scope->srcdefs_size * sizeof(struct AST_STRUCT*));
		if (g != NULL) scope->srcdefs = g;
		if (scope->srcdefs notnullptr) {
			scope->srcdefs[scope->srcdefs_size - 1] = srcdef;
		}
	}

	return srcdef;
};

AST_T* scope_getsrcdef(scope_T* scope, const char* srcname) {
	for (int i = 0; i < scope->srcdefs_size; i++) {
		AST_T* srcdef = scope->srcdefs[i];
		if (strcmp(srcdef->srcdef_name, srcname) == 0)
			return srcdef;
	}

	return (void*)0;
};
