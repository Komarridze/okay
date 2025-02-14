#ifndef K_SYNTAX_H
#define K_SYNTAX_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../utools/definitions.h"

enum 
{

	TEOF = -1, // end-of-file

	NOTHING = 0, // nothing

	CAST, // &
	SEPARATE, // |

	/* TYPE IDENTIFIERS */

	YINT, // i / int
	YFLT, // f / float
	YSTR, // str / string
	YBLN, // bb / bool / boolean
	YSEQ, // sq / seq / sequence
	YOBJ, // obj / object


	BTRUE, // true
	BFALSE, // false

	NAME = 11, // Object
	NUMBER = 12, // 0.4f
	STRING = 13, // "lol"

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

	SEMICOLON = 25, // ;
	COMMA, // ,
	PERIOD, // .

	ASN, // = (assign)
	NEG, // ! (not)
	NEQ, // !=
	CMP, // ==
	LSS, // <
	GTR, // >
	LEQ, // <=
	GEQ, // >=

	LAND, // &&
	LOR, // ||
	LXOR, // ^

	ARROW, // ->

	/* KEYWORDS */

		/* STRUCTS */

	KALI = 40, // alias
	KGLO = 41, // global
	KSVV = 42, // save
	KSCH = 43, // schematic
	KORI = 44, // oriented

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
	KNOT, // not


	// OTHER

	KIN,
	KGET,
	KBURN,

	// EXCEPTIONS

	KTRY, // try / fuckaround
	KCATCH, // catch / findout
	KFIX // fix / coverup

} Ttype;

typedef struct Token // okay.syntax.token
{

	int type;
	char* contents;

} Token;

typedef struct Lexer // okay.syntax.lexer
{
	int line;
	size_t symbol;

	char* src;
	size_t size;

} Lexer;

// Create a new Token.
// [okay.syntax.tnew]
_nooverflow Token* tnew(int type, char* contents);

// Creates a new Lexer Object.
// [okay.syntax.lnew]
_nooverflow Lexer* lnew(char* source_code);

// Tokenizes the input string.
// [okay.syntax.ltokenize]
_exceptoverflow Token* ltokenize(Lexer* lexer);

// Scrolls to the next character inside of a Lexer Object.
// [okay.syntax.lnext]
_nooverflow void lnext(Lexer* lexer);

// Returns the next character inside a Lexer Source String, 
// or nullchar if there are no more characters to read.
// [okay.syntax.lpeek]
_nooverflow char lpeek(Lexer* lexer);


// DETERMINE TOKENS

// Tokenizes a name — an alphanumeric (including underscores)
// char sequence that ends in a null terminator.
// [okay.syntax.ltokenizeName]
_unified _nooverflow Token* ltokenizeName(Lexer* lexer);

// Tokenizes a number — a numeric (with a possible postfix f, b, h)
// char sequence that ends in a null terminator.
// [okay.syntax.ltokenizeNumber]
_unified _nooverflow Token* ltokenizeNumber(Lexer* lexer);


// ADDITIONALS

// Checks whether a given name is a reserved keyword
// and creates a corresponding token.
// [okay.syntax.lkeywordTable]
_unhandled Token* lkeywordTable(Lexer* lexer, char* name);


#endif