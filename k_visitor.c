#include "k_visitor.h"
#include "scope.h"
#include "AST.h"
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
			case AST_INT: printf("%d\n", visited_ast->intvalue); break;
			case AST_FLOAT: printf("%f\n", visited_ast->floatvalue); break;
			default:("%p\n", visited_ast);
		}
		
	}

	return init_ast(AST_NOOP);

}
///////


visitor_T* init_visitor() {
	visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
	if (visitor notnullptr) {
		visitor->status = 1;
	}
	return visitor;
}

AST_T* vt_visit(visitor_T* visitor, AST_T* node) {
	//printf("type: %d\n", node->type);
	switch (node->type) {
	case AST_SRC_DEF: return vt_VSrcDef(visitor, node); break;
	case AST_SRC: return vt_VSrc(visitor, node); break;
	case AST_FUNCTION_DEF: return vt_VFDef(visitor, node); break;
	case AST_FUNCTION_CALL: return vt_VFCall(visitor, node); break;
	case AST_INT: return vt_Vreturn(visitor, node);break;
	case AST_FLOAT: return vt_Vreturn(visitor, node); break;;
	case AST_STRINGEXPR: return vt_VStr(visitor, node); break;
	case AST_COMPOUND: return vt_VCompound(visitor, node); break;
	case AST_NOOP: return node; break;
	}

	printf("K0002: Uncaught statement of type '%d'\n", node->type);
	return init_ast(AST_NOOP);
};

AST_T* vt_VSrcDef(visitor_T* visitor, AST_T* node) {
	
	
	scope_addsrcdef(node->scope, node);
	return node;
};

AST_T* vt_VSrc(visitor_T* visitor, AST_T* node) {
	AST_T* srcdef = scope_getsrcdef(node->scope, node->srcname);

	if (srcdef notnullptr) {
		return vt_visit(visitor, srcdef->srcdef_value);
	}
	

	printf("K0004: Undefined variable '%s'\n", node->srcname);
	return node;
};

AST_T* vt_VFDef(visitor_T* visitor, AST_T* node) {
	
	scope_addfdef(node->scope, node);
	return node;
};

AST_T* vt_VFCall(visitor_T* visitor, AST_T* node) {
	if (strcmp(node->fcallname, "printc") == 0) {
		return builtin_printc(visitor, node->fcall_args, node->fcall_argsize);
	}

	AST_T* fdef = scope_getfdef(node->scope, node->fcallname);

	if (fdef == (void*)0) {
		printf("K0003: Undefined method '%s'\n", node->fcallname);
		return init_ast(AST_NOOP);
	}

	for (int i = 0; i < fdef->fdefargs_size; i++) {
		AST_T* astsrc = fdef->fdefargs[i];
		AST_T* astvalue = node->fcall_args[i];

		AST_T* srcdef = init_ast(AST_SRC_DEF);
		srcdef->srcdef_value = astvalue;

		srcdef->srcdef_name = calloc(strlen(astsrc->srcname) + 1, sizeof(char));
		
		if (srcdef->srcdef_name != NULL) 
			strcpy_s(srcdef->srcdef_name, strlen(astsrc->srcname) + 1, astsrc->srcname);
		

		scope_addsrcdef(fdef->fdefbody->scope, srcdef);
			
	}


	return vt_visit(visitor, fdef->fdefbody);
	
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

///
AST_T* vt_Vreturn(visitor_T* visitor, AST_T* node) {
	return node;
};