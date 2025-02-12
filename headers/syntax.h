#ifndef K_SYNTAX_H
#define K_SYNTAX_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utools/definitions.h"

enum 
{

	TEOF, // end-of-file

	CAST, // &

	/* TYPE IDENTIFIERS */

	YINT, // i / int
	YFLT, // f / float
	YSTR, // str / string
	YBLN, // bb / bool / boolean
	YSEQ, // sq / seq / sequence
	YOBJ, // obj / object


	BTRUE, // true
	BFALSE, // false

	NOTHING, // nothing
	NAME, // Object

	NUMBER, // 0.4f
	POSTFIX, //   f

	STRING, // "lol"

	PLUS, // +
	MINUS, // -
	TIMES, // *
	SLASH, // /

	MOD, // %

	LPAREN, // (
	RPAREN, // )

	LBRACK, // [
	RBRACK, // ]

	LCBRA, // {
	RCBRA, // }

	SEMICOLON, // ;
	COMMA, // ,
	PERIOD, // .

	ASN, // = (assign)
	NEQ, // !=
	CMP, // ==
	LSS, // <
	GTR, // >
	LEQ, // <=
	REQ, // >=

	LAND, // &&
	LOR, // ||
	LXOR, // ^


	/* KEYWORDS */

		/* STRUCTS */

	KALI, // alias
	KSCH, // schematic
	KORI, // oriented

	/* SIMPLE */

// CONTROL

KIF,
KELSE,
KFOR,
KWHILE,
KBREAK,
KCONTINUE,
KRETURN,
KREST,


// LOGIC

KAND, // and
KOR, // or
KNOT,


// OTHER

KIN,
KGET,
KBURN,

// EXCEPTIONS

KTRY, // try / fuckaround
KCATCH, // catch / findout
KFIX // fix / coverup

} Ttype;

typedef struct // okay.syntax.token
{

	int type;
	char* contents;

} Token;

typedef struct // okay.syntax.lexer
{
	int line;
	size_t symbol;

	char* src;
	size_t size;

} Lexer;

// Creates a new Lexer Object.
// [okay.syntax.lnew]
_nooverflow Lexer* lnew(char* source_code);

// Tokenizes the input string.
// [okay.syntax.ltokenize]
_nooverflow void ltokenize(Lexer* lexer, char* code);

// Scrolls to the next character inside of a Lexer Object.
// [okay.syntax.lnext]
_nooverflow void lnext(Lexer* lexer);

// Returns the next character inside a Lexer Source String, 
// or nullchar if there are no more characters to read.
// [okay.syntax.lpeek]
_nooverflow char lpeek(Lexer* lexer);

#endif