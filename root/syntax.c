#include "../headers/syntax.h"
#include "../headers/error.h"

_nooverflow Lexer* lnew(char* source_code) {

	Lexer* lexer = (Lexer*)calloc(1, sizeof(Lexer));

	if (lexer) {

		lexer->line = 0;
		lexer->symbol = 0;

		lexer->src = source_code;
		lexer->size = strlen(source_code);

		return lexer;

	}

	else {
		error(0, -1, "syntax.c");
	}



}

_nooverflow Token* tnew(int type, char* contents) {
	Token* t = (Token*)calloc(1, sizeof(Token));

	if (t) {

		t->type = type;
		t->contents = contents;

		return t;
	}

	else {
		error(0, -1, "syntax.c");
	}

}

_exceptoverflow Token* ltokenize(Lexer* lexer)
{

	while (lexer->src[lexer->symbol] != '\0') {

		if (lexer->src[lexer->symbol] == 0x20 || lexer->src[lexer->symbol] == 0x0d)
		{
			lnext(lexer); continue; // pass iter
		}
		
		if (lexer->src[lexer->symbol] == 0x0a)
		{
			lexer->line++;                                     // [POSSIBLE OVERFLOW, HIGHLY UNLIKELY, NOT CRITICAL, CAN BE IGNORED]
			lnext(lexer); continue; // pass iter
		}

		if (isalnum(lexer->src[lexer->symbol]) || lexer->src[lexer->symbol] == '_')
		{
			if (isdigit(lexer->src[lexer->symbol]))
			{
				return ltokenizeNumber(lexer);
			}
			else
			{
				return ltokenizeName(lexer);
			}


		}

		switch (lexer->src[lexer->symbol]) 
		{
		
//		ALWAYS ADD BREAK SAFEGUARDS

		case '+': return tnew(PLUS, "+"); break;
		case '-': return tnew(MINUS, "-"); break;
		case '*': return tnew(TIMES, "*"); break;
		case '/': return tnew(SLASH, "/"); break;

		case '%': return tnew(MOD, "%"); break;

		case '(': return tnew(LPAREN, "("); break;
		case ')': return tnew(RPAREN, ")"); break;

		case '[': return tnew(LBRACK, "["); break;
		case ']': return tnew(RBRACK, "]"); break;

		case '{': return tnew(LCBRA, "{"); break;
		case '}': return tnew(RCBRA, "}"); break;

		case ';': return tnew(SEMICOLON, ";"); break;
		case ',': return tnew(COMMA, ","); break;
		case '.': return tnew(PERIOD, "."); break;

		case '^': return tnew(LXOR, "^"); break;

		case '=': // ==
			if (lpeek(lexer) == '=') return tnew(CMP, "==");
			else return tnew(ASN, "=");
			break;

		case '!': // !=
			if (lpeek(lexer) == '=') return tnew(NEQ, "!=");
			else return tnew(NEG, "!");
			break;

		case '<': // <=
			if (lpeek(lexer) == '=') return tnew(LEQ, "<=");
			else return tnew(LSS, "<");
			break;

		case '>': // >=
			if (lpeek(lexer) == '=') return tnew(GEQ, ">=");
			else return tnew(GTR, ">");
			break;

		case '&': // &&
			if (lpeek(lexer) == '&') return tnew(LAND, "&&");
			else return tnew(CAST, "&");
			break;

		case '|': // ||
			if (lpeek(lexer) == '|') return tnew(LOR, "||");
			else return tnew(SEPARATE, "|");
			break;

			
			












		}

		lnext(lexer); // next char
	}


	


//	RETURN EOF
	return tnew(TEOF, "EOF");

}

_nooverflow void lnext(Lexer* lexer)
{
	if (lexer->symbol == lexer->size)
		lexer->symbol = 0;
	else lexer->symbol++;
}

_nooverflow char lpeek(Lexer* lexer)
{
	return (lexer->symbol == lexer->size) ? '\0' : lexer->src[lexer->symbol + 1];
}

_unified _nooverflow Token* ltokenizeName(Lexer* lexer)
{
//	COMPUTATION

	size_t namestart = lexer->symbol;
	size_t length = 1;

	while (isalnum(lexer->src[lexer->symbol]) || lexer->src[lexer->symbol] == '_')
	{
		length++;
		lnext(lexer);
	}

//	EXECUTION
	lexer->symbol = namestart;
	char* name = calloc(length, sizeof(char));

	if (name)
	{
		for (size_t i = 0; i < length - 1; i++)
		{
			name[i] = lexer->src[lexer->symbol];
			lnext(lexer);
		}
		name[length - 1] = '\0';
		return lkeywordTable(lexer, name);
	}

	else
	{
		error(0, -1, "syntax.c");
	}
	
}

_unified _nooverflow Token* ltokenizeNumber(Lexer* lexer)
{
	size_t numstart = lexer->symbol;
	size_t length = 1;
	short period = 0;
	short conversion = 0;

	while (isdigit(lexer->src[lexer->symbol]) || lexer->src[lexer->symbol] == '.'
		|| lexer->src[lexer->symbol] == 'f' || lexer->src[lexer->symbol] == 'b' || lexer->src[lexer->symbol] == 'h')
	{
		if (isdigit(lexer->src[lexer->symbol]))
		{
			length++;
			lnext(lexer);
		}
		else if (lexer->src[lexer->symbol] == '.')
		{
			if (period == 0) {
				length++;
				lnext(lexer);
				period = 1;
			}
			else
			{
				error(1000, lexer->line, "syntax.c");
				break;
			}
			
		}
		else {
			if (conversion == 0) {
				length++;
				lnext(lexer);
				conversion = 1;
			}
			else
			{
				error(1000, lexer->line, "syntax.c");
				break;
			}
		}


	}

	lexer->symbol = numstart;
	char* num = calloc(length, sizeof(char));

	if (num)
	{
		for (size_t i = 0; i < length - 1; i++)
		{
			num[i] = lexer->src[lexer->symbol];
			lnext(lexer);
		}
		num[length - 1] = '\0';
		return tnew(NUMBER, num);
	}

	else
	{
		error(0, -1, "syntax.c");
	}

}

// ADDITIONALS

_unhandled Token* lkeywordTable(Lexer* lexer, char* name) {

	if (strcmp(name, "alias") == 0)
	{
		return tnew(KALI, "alias");
	}
	else
	{
		return tnew(NAME, name);
	}

}
