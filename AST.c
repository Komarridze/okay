#include "AST.h"
#define notnullptr != '\0'

AST_T* init_ast(int type) {
	AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
	if (ast notnullptr) {
		ast->type = type;

		ast->scope = (void*)0;

		/* AST_SRC_DEF */
		ast->srcdef_name = (void*)0;
		ast->srcdef_value = (void*)0;

		/* AST_SRC */
		ast->srcname = (void*)0;

		/* AST_FUNCTION_DEF */
		ast->fdefname = (void*)0;
		ast->fdefbody = (void*)0;

		/* AST_FUNCTION_CALL */
		ast->fcallname = (void*)0;
		ast->fcall_args = (void*)0;
		ast->fcall_argsize = 0;

		/* AST_STRINGEXPR */
		ast->strvalue = (void*)0;

		/* AST_COMPOUND */
		ast->compound_value = (void*)0;
		ast->compound_size = 0;
	}

	return ast;
	
}