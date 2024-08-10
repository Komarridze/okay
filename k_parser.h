#pragma once
#ifndef K_PARSER_H
#define K_PARSER_H
#include "k_token.h"
#include "k_lexer.h"
#include "AST.h"
#include "scope.h"

typedef struct PARSER_STRUCT {
	lexer_T* lexer;
	token_T* thistoken;
	token_T* prevtoken;
	scope_T* scope;

} parser_T;

parser_T* init_parser(lexer_T* lexer);

void ps_eat(parser_T* parser, int tokentype);

AST_T* ps_parse(parser_T* parser, scope_T* scope);

AST_T* ps_parseStatement(parser_T* parser, scope_T* scope);

AST_T* ps_parseMultSt(parser_T* parser, scope_T* scope);

AST_T* ps_parseExpr(parser_T* parser, scope_T* scope);

AST_T* ps_parseFactor(parser_T* parser, scope_T* scope);

AST_T* ps_parseTerm(parser_T* parser, scope_T* scope);

AST_T* ps_parseFDef(parser_T* parser, scope_T* scope);

AST_T* ps_parseFCall(parser_T* parser, scope_T* scope);

AST_T* ps_parseSrcDef(parser_T* parser, scope_T* scope);

AST_T* ps_parseSrc(parser_T* parser, scope_T* scope);

AST_T* ps_parseStr(parser_T* parser, scope_T* scope);

AST_T* ps_parseID(parser_T* parser, scope_T* scope);
#endif // !K_PARSER_H