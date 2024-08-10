#include "k_visitor.h"
#include <stdio.h>
#include <string.h>
#define notnullptr != '\0'
/////// BUILT-IN
static AST_T* builtin_printc(visitor_T* visitor, AST_T** args, int args_size) {
	for (int i = 0; i < args_size; i++) {
		AST_T* visited_ast = vt_visit(visitor, args[i]);
		//printf("%d\n", visited_ast->type);
		switch (visited_ast->type) {
			case AST_STRINGEXPR: printf("%s\n", visited_ast->strvalue); break;
			default:("%p\n", visited_ast);
		}
		
	}

	return init_ast(AST_NOOP);

}
///////


visitor_T* init_visitor() {
	visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
	if (visitor notnullptr) {
		visitor->srcdefs = (void*)0;
		visitor->srcdefs_size = 0;
	}
}

AST_T* vt_visit(visitor_T* visitor, AST_T* node) {
	//printf("type: %d\n", node->type);
	switch (node->type) {
	case AST_SRC_DEF: return vt_VSrcDef(visitor, node); break;
	case AST_SRC: return vt_VSrc(visitor, node); break;
	case AST_FUNCTION_CALL: return vt_VFCall(visitor, node); break;
	case AST_STRINGEXPR: return vt_VStr(visitor, node); break;
	case AST_COMPOUND: return vt_VCompound(visitor, node); break;
	case AST_NOOP: return node; break;
	}

	printf("K0002: Uncaught statement of type '%d'\n", node->type);
	return init_ast(AST_NOOP);
};

AST_T* vt_VSrcDef(visitor_T* visitor, AST_T* node) {
	
	
	if (visitor->srcdefs == (void*)0) {
		visitor->srcdefs = calloc(1, sizeof(struct AST_STRUCT*));
		if (visitor->srcdefs notnullptr) {
			visitor->srcdefs[0] = node;
			visitor->srcdefs_size += 1;
		}
	}
	else {
		visitor->srcdefs_size += 1;
		visitor->srcdefs = realloc(
		visitor->srcdefs,
		visitor->srcdefs_size * sizeof(struct AST_STRUCT*));
		if (visitor->srcdefs notnullptr) {
			visitor->srcdefs[visitor->srcdefs_size - 1] = node;
		}
	}

	return node;
};

AST_T* vt_VSrc(visitor_T* visitor, AST_T* node) {
	for (int i = 0; i < visitor->srcdefs_size; i++) {
		AST_T* vardef = visitor->srcdefs[i];
		//printf("%s: %s", vardef->srcdef_name, node->srcname);

		if (strcmp(vardef->srcdef_name, node->srcname) == 0) {
			return vt_visit(visitor, vardef->srcdef_value);
		}
	}

	printf("K0004: Undefined variable '%s\n", node->srcname);
	return node;
};

AST_T* vt_VFCall(visitor_T* visitor, AST_T* node) {
	if (strcmp(node->fcallname, "printc") == 0) {
		return builtin_printc(visitor, node->fcall_args, node->fcall_argsize);
	}

	printf("K0003: Undefined method '%s'\n", node->fcallname);
	return init_ast(AST_NOOP);
};

AST_T* vt_VStr(visitor_T* visitor, AST_T* node) {
	//printf("str");
	return node;
};

AST_T* vt_VCompound(visitor_T* visitor, AST_T* node) {
	for (int i = 0; i < node->compound_size; i++) {
		vt_visit(visitor, node->compound_value[i]);
	}

	return init_ast(AST_NOOP);
};