#include "k_parser.h"
#include "scope.h"
#include <stdio.h>
#include <string.h>
#define notnullptr != '\0'

// just in case
/*static scope_T* getnodescope(parser_T* parser, AST_T* node) {
	return node->scope == (void*)0 ? parser->scope : node->scope;
}
 */

parser_T* init_parser(lexer_T* lexer) {
	parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
	if (parser notnullptr) {
		parser->lexer = lexer;
		parser->thistoken = lx_nexttoken(lexer);
		parser->prevtoken = parser->thistoken;
		parser->scope = init_scope();
	}

	return parser;
};

void ps_eat(parser_T* parser, int tokentype) {
	//printf("%s\n", parser->thistoken->value);
	if (parser->thistoken->type == tokentype) {
		parser->prevtoken = parser->thistoken;
		parser->thistoken = lx_nexttoken(parser->lexer);
	}
	else {
		printf("K0001: Unexpected token '%s' of type %d\n", parser->thistoken->value, parser->thistoken->type);
		parser->thistoken = init_token(TOKEN_STRINGEXPR, "undefined");
	}
		
};

AST_T* ps_parse(parser_T* parser, scope_T* scope) {
	return ps_parseMultSt(parser, scope);
};

AST_T* ps_parseStatement(parser_T* parser, scope_T* scope) {
	//printf("type: %d\n", parser->thistoken->type);
	switch (parser->thistoken->type) {
	case TOKEN_NEGATIVE: return ps_parseNumber(parser, scope);
	case TOKEN_ID: return ps_parseID(parser, scope);
	case TOKEN_NUMBER: return ps_parseNumber(parser, scope);
	}
	return init_ast(AST_NOOP);
};

AST_T* ps_parseMultSt(parser_T* parser, scope_T* scope) {
	AST_T* compound = init_ast(AST_COMPOUND);
	compound->scope = scope;
	compound->compound_value = calloc(1, sizeof(struct AST_STRUCT));
	AST_T* astStatement = ps_parseStatement(parser, scope);
	astStatement->scope = scope;
	if (compound->compound_value notnullptr) {
		compound->compound_value[0] = astStatement;
		compound->compound_size += 1;
	}
		

	while (parser->thistoken->type == TOKEN_SEMI) {
		ps_eat(parser, TOKEN_SEMI);
		
		AST_T* astStatement = ps_parseStatement(parser, scope);
		if (astStatement) {
		
		compound->compound_size += 1;

		if (compound->compound_value notnullptr) {
			struct AST_STRUCT** x = realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT));
			if (x != NULL) compound->compound_value = x;
			if (compound->compound_value notnullptr) {
				compound->compound_value[compound->compound_size - 1] = astStatement;
			}
		}
		}
	}
	
	return compound;
};

AST_T* ps_parseExpr(parser_T* parser, scope_T* scope) {
	//printf("%d\n", parser->thistoken->type);
	switch (parser->thistoken->type) {
	case TOKEN_STRINGEXPR: return ps_parseStr(parser, scope);
	case TOKEN_ID: return ps_parseID(parser, scope);
	case TOKEN_NUMBER: return ps_parseNumber(parser, scope);
	case TOKEN_NEGATIVE: return ps_parseNumber(parser, scope);
	}

	return init_ast(AST_NOOP);
};

AST_T* ps_parseFactor(parser_T* parser, scope_T* scope);

AST_T* ps_parseTerm(parser_T* parser, scope_T* scope);

AST_T* ps_parseFDef(parser_T* parser, scope_T* scope) {
	AST_T* fdef = init_ast(AST_FUNCTION_DEF);
	ps_eat(parser, TOKEN_ID); //alias

	char* fname = parser->thistoken->value;
	fdef->fdefname = calloc(strlen(fname) + 1, sizeof(char));

	if (fdef->fdefname notnullptr) {
		strcpy_s(fdef->fdefname, strlen(fname) + 1, fname);
	}
	

	ps_eat(parser, TOKEN_ID); //alias name
	ps_eat(parser, TOKEN_LEFTP);

	fdef->fdefargs = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* arg = ps_parseSrc(parser, scope);
	fdef->fdefargs_size += 1;
	
	if (fdef->fdefargs notnullptr) {
		fdef->fdefargs[fdef->fdefargs_size - 1] = arg;
	}

	while (parser->thistoken->type == TOKEN_COMMA) {
		ps_eat(parser, TOKEN_COMMA);

		fdef->fdefargs_size += 1;

		struct AST_STRUCT** t = realloc(fdef->fdefargs, fdef->fdefargs_size * sizeof(struct AST_STRUCT));
		if (t != NULL) fdef->fdefargs = t;

		AST_T* arg = ps_parseSrc(parser, scope);

		if (fdef->fdefargs notnullptr) {
			fdef->fdefargs[fdef->fdefargs_size - 1] = arg;
		}
		
		
	}

	ps_eat(parser, TOKEN_RIGHTP);
	ps_eat(parser, TOKEN_LEFTBR);

	
	fdef->fdefbody = ps_parseMultSt(parser, scope);

	ps_eat(parser, TOKEN_RIGHTBR);

	fdef->scope = scope;

	return fdef;

};

AST_T* ps_parseFCall(parser_T* parser, scope_T* scope) {
	AST_T* fcall = init_ast(AST_FUNCTION_CALL);
	
	fcall->fcallname = parser->prevtoken->value;
	ps_eat(parser, TOKEN_LEFTP);

	fcall->fcall_args = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* astExpr = ps_parseExpr(parser, scope);

	if (fcall->fcall_args notnullptr) {
		fcall->fcall_args[0] = astExpr;
		fcall->fcall_argsize += 1;
	}

	while (parser->thistoken->type == TOKEN_COMMA) {
		ps_eat(parser, TOKEN_COMMA);

		AST_T* astExpr = ps_parseExpr(parser, scope);
		fcall->fcall_argsize += 1;

		if (fcall->fcall_args notnullptr) {
			struct AST_STRUCT** c = realloc(fcall->fcall_args, fcall->fcall_argsize * sizeof(struct AST_STRUCT*));
			if (c != NULL) fcall->fcall_args = c;
			if (fcall->fcall_args notnullptr) {
				fcall->fcall_args[fcall->fcall_argsize - 1] = astExpr;
			}
		}
	}

	ps_eat(parser, TOKEN_RIGHTP);

	fcall->scope = scope;

	return fcall;

};

AST_T* ps_parseSrcDef(parser_T* parser, scope_T* scope) {
	ps_eat(parser, TOKEN_ID); //src
	char* srcdefname = parser->thistoken->value;
	//printf(srcdefname);
	ps_eat(parser, TOKEN_ID); //src name
	ps_eat(parser, TOKEN_EQUALS);
	AST_T* srcdefvalue = ps_parseExpr(parser, scope);

	AST_T* srcdef = init_ast(AST_SRC_DEF);
	srcdef->srcdef_name = srcdefname;
	srcdef->srcdef_value = srcdefvalue;

	srcdef->scope = scope;

	return srcdef;

};

AST_T* ps_parseSrc(parser_T* parser, scope_T* scope) {

	char* tokenvalue = parser->thistoken->value;
	ps_eat(parser, TOKEN_ID); // src name or alias name
	
	if (parser->thistoken->type == TOKEN_LEFTP) {
		return ps_parseFCall(parser, scope);
	}

	AST_T* astsrc = init_ast(AST_SRC);
	astsrc->srcname = tokenvalue;

	astsrc->scope = scope;

	return astsrc;
};

AST_T* ps_parseStr(parser_T* parser, scope_T* scope) {
	AST_T* aststring = init_ast(AST_STRINGEXPR);
	aststring->strvalue = parser->thistoken->value;
	
	ps_eat(parser, TOKEN_STRINGEXPR);

	aststring->scope = scope;

	return aststring;

};

AST_T* ps_parseID(parser_T* parser, scope_T* scope) {
	if (strcmp(parser->thistoken->value, "src") == 0) {
		return ps_parseSrcDef(parser, scope);
	}
	else if (strcmp(parser->thistoken->value, "alias") == 0) {
		return ps_parseFDef(parser, scope);
	}
	else {
		return ps_parseSrc(parser, scope);
	}
};

AST_T* ps_parseNumber(parser_T* parser, scope_T* scope) {
	int sign = 1;
	if (parser->thistoken->type == TOKEN_NEGATIVE) {
		if (parser->prevtoken->type != TOKEN_NUMBER) {
			sign = -1;
			ps_eat(parser, TOKEN_NEGATIVE);
		}
		else ps_eat(parser, TOKEN_NEGATIVE);
	}

	 
	for (int i = 0; i < strlen(parser->thistoken->value); i++) {
		if (parser->thistoken->value[i] == '.') {
			AST_T* tmp = init_ast(AST_FLOAT);
			tmp->floatvalue = (double) (atof(parser->thistoken->value) * sign);
			//printf("double: %f\n", atof(parser->thistoken->value));
			ps_eat(parser, TOKEN_NUMBER);
			tmp->scope = scope;
			return tmp;
		}
	}

	AST_T* tmp = init_ast(AST_INT);
	tmp->intvalue = (int)(atoi(parser->thistoken->value) * sign);
	tmp->scope = scope;
	ps_eat(parser, TOKEN_NUMBER);
	return tmp;
};