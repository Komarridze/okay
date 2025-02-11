#pragma once


enum {

	EOF, // end-of-file

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

typedef struct {

	int type;
	char* contents;

} Token;

typedef struct {
	int line;
	int symbol;
	char* src;
} Lexer;

Token* tokenize(char* code) {

}