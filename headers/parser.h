#ifndef K_PARSER_H
#define K_PARSER_H

#include "../utools/definitions.h"
#include "../headers/node.h"
#include "../headers/error.h"
#include "../headers/syntax.h"

typedef struct Parser
{
	Lexer* lexer;
	Token* t;
	Scope* scope;

} Parser;



// Creates a new parser on the base of a lexer.
// [okay.parser.psnew]
_nooverflow Parser* psnew(Lexer* lexer);

// Eats a token.
// [okay.parser.peat]
_nooverflow void peat(Parser* parser, int token);

_unhandled Node* pparse(Parser* parser, Scope* scope);

_unhandled Node* pstatement(Parser* parser, Scope* scope);





#endif 