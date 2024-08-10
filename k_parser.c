#include "k_parser.h"
#include <stdio.h>
#include <string.h>
#define notnullptr != '\0'

parser_T* init_parser(lexer_T* lexer) {
	parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
	if (parser notnullptr) {
		parser->lexer = lexer;
		parser->thistoken = lx_nexttoken(lexer);
		parser->prevtoken = parser->thistoken;
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
		printf("K0001: Unexprected token '%s' of type %d", parser->thistoken->value, parser->thistoken->type);
		parser->thistoken = init_token(TOKEN_STRINGEXPR, "undefined");
	}
		
};

AST_T* ps_parse(parser_T* parser) {
	return ps_parseMultSt(parser);
};

AST_T* ps_parseStatement(parser_T* parser) {
	//printf("type: %d\n", parser->thistoken->type);
	switch (parser->thistoken->type) {
	case TOKEN_ID: return ps_parseID(parser);
	}
	return init_ast(AST_NOOP);
};

AST_T* ps_parseMultSt(parser_T* parser) {
	AST_T* compound = init_ast(AST_COMPOUND);
	compound->compound_value = calloc(1, sizeof(struct AST_STRUCT));
	AST_T* astStatement = ps_parseStatement(parser);

	if (compound->compound_value notnullptr) {
		compound->compound_value[0] = astStatement;
		compound->compound_size += 1;
	}
		

	while (parser->thistoken->type == TOKEN_SEMI) {
		ps_eat(parser, TOKEN_SEMI);
		
		AST_T* astStatement = ps_parseStatement(parser);
		if (astStatement) {
		
		compound->compound_size += 1;

		if (compound->compound_value notnullptr) {
			compound->compound_value = realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT));
			if (compound->compound_value notnullptr) {
				compound->compound_value[compound->compound_size - 1] = astStatement;
			}
		}
		}
	}
	
	return compound;
};

AST_T* ps_parseExpr(parser_T* parser) {
	//printf("%d\n", parser->thistoken->type);
	switch (parser->thistoken->type) {
	case TOKEN_STRINGEXPR: return ps_parseStr(parser);
	case TOKEN_ID: return ps_parseID(parser);
	}

	return init_ast(AST_NOOP);
};

AST_T* ps_parseFactor(parser_T* parser);

AST_T* ps_parseTerm(parser_T* parser);

AST_T* ps_parseFCall(parser_T* parser) {
	AST_T* fcall = init_ast(AST_FUNCTION_CALL);
	
	fcall->fcallname = parser->prevtoken->value;
	ps_eat(parser, TOKEN_LEFTP);

	fcall->fcall_args = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* astExpr = ps_parseExpr(parser);

	if (fcall->fcall_args notnullptr) {
		fcall->fcall_args[0] = astExpr;
		fcall->fcall_argsize += 1;
	}
		

	while (parser->thistoken->type == TOKEN_COMMA) {
		ps_eat(parser, TOKEN_COMMA);

		AST_T* astExpr = ps_parseExpr(parser);
		fcall->fcall_argsize += 1;

		if (fcall->fcall_args notnullptr) {
			fcall->fcall_args = realloc(fcall->fcall_args, fcall->fcall_argsize * sizeof(struct AST_STRUCT*));
			if (fcall->fcall_args notnullptr) {
				fcall->fcall_args[fcall->fcall_argsize - 1] = astExpr;
			}
		}
	}

	ps_eat(parser, TOKEN_RIGHTP);
	return fcall;

};

AST_T* ps_parseSrcDef(parser_T* parser) {
	ps_eat(parser, TOKEN_ID); //src
	char* srcdefname = parser->thistoken->value;
	//printf(srcdefname);
	ps_eat(parser, TOKEN_ID); //src name
	ps_eat(parser, TOKEN_EQUALS);
	AST_T* srcdefvalue = ps_parseExpr(parser);

	AST_T* srcdef = init_ast(AST_SRC_DEF);
	srcdef->srcdef_name = srcdefname;
	srcdef->srcdef_value = srcdefvalue;

	return srcdef;

};

AST_T* ps_parseSrc(parser_T* parser) {

	char* tokenvalue = parser->thistoken->value;
	ps_eat(parser, TOKEN_ID); // src name or alias name
	
	if (parser->thistoken->type == TOKEN_LEFTP) {
		return ps_parseFCall(parser);
	}

	AST_T* astsrc = init_ast(AST_SRC);
	astsrc->srcname = tokenvalue;

	return astsrc;
};

AST_T* ps_parseStr(parser_T* parser) {
	AST_T* aststring = init_ast(AST_STRINGEXPR);
	aststring->strvalue = parser->thistoken->value;
	
	ps_eat(parser, TOKEN_STRINGEXPR);

	return aststring;

};

AST_T* ps_parseID(parser_T* parser) {
	if (strcmp(parser->thistoken->value, "src") == 0) {
		return ps_parseSrcDef(parser);
	}
	else {
		return ps_parseSrc(parser);
	}
};