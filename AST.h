#pragma once
#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT {
	enum {
		AST_FUNCTION_CALL,
		AST_SRC,
		AST_SRC_DEF,
		AST_STRINGEXPR,
		AST_COMPOUND,
		AST_NOOP
	} type;

	/* AST_SRC_DEF */
	char* srcdef_name;
	struct AST_STRUCT* srcdef_value;

	/* AST_SRC */
	char* srcname;
	

	/* AST_FUNCTION_CALL */
	char* fcallname;
	struct AST_STRUCT** fcall_args;
	size_t fcall_argsize;

	/* AST_STRINGEXPR */
	char* strvalue;

	/* AST_COMPOUND */
	struct AST_STRUCT** compound_value;
	size_t compound_size;
} AST_T;

AST_T* init_ast(int type);
#endif // !AST_H
