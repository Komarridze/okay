#include "../headers/syntax.h"
#include "../headers/error.h"

_nooverflow Lexer* lnew(char* source_code) {

	Lexer* lexer = (Lexer*)calloc(1, sizeof(struct Lexer));

	if (lexer) {

		lexer->line = 0;
		lexer->symbol = 0;

		lexer->src = source_code;
		lexer->size = strlen(source_code);

		return lexer;

	}

	else {
		error(0, -1, "syntax.c");
		return NULL;
	}



}

_nooverflow Token* tnew(int type, char* contents) {
	Token* t = (Token*)calloc(1, sizeof(struct Token));

	if (t) {

		t->type = type;
		t->contents = contents;

		return t;
	}

	else {
		error(0, -1, "syntax.c");
		return NULL;
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

		if (lexer->src[lexer->symbol] == '"')
		{
			return ltokenizeString(lexer);
		}

		switch (lexer->src[lexer->symbol]) 
		{
		
//		ALWAYS ADD BREAK SAFEGUARDS

		case '+': lnext(lexer); return tnew(PLUS, "+"); break;
		case '-': lnext(lexer); return tnew(MINUS, "-"); break;
		case '*': lnext(lexer); return tnew(TIMES, "*"); break;
		case '/': lnext(lexer); return tnew(SLASH, "/"); break;

		case '%': lnext(lexer); return tnew(MOD, "%"); break;

		case '(': lnext(lexer); return tnew(LPAREN, "("); break;
		case ')': lnext(lexer); return tnew(RPAREN, ")"); break;

		case '[': lnext(lexer); return tnew(LBRACK, "["); break;
		case ']': lnext(lexer); return tnew(RBRACK, "]"); break;

		case '{': lnext(lexer); return tnew(LCBRA, "{"); break;
		case '}': lnext(lexer); return tnew(RCBRA, "}"); break;

		case ';': lnext(lexer); return tnew(SEMICOLON, ";"); break;
		case ',': lnext(lexer); return tnew(COMMA, ","); break;
		case '.': lnext(lexer); return tnew(PERIOD, "."); break;

		case '^': lnext(lexer); return tnew(LXOR, "^"); break;

		case '=': // ==
			if (lpeek(lexer) == '=')
			{
				lnext(lexer);
				return tnew(CMP, "==");
			}
			else return tnew(ASN, "=");
			lnext(lexer);
			break;

		case '!': // !=
			if (lpeek(lexer) == '=') 
			{
				lnext(lexer);
				return tnew(NEQ, "!=");
			}
			else return tnew(NEG, "!");
			lnext(lexer);
			break;

		case '<': // <=
			if (lpeek(lexer) == '=') 
			{
				lnext(lexer);
				return tnew(LEQ, "<=");
			}
			else return tnew(LSS, "<");
			lnext(lexer);
			break;

		case '>': // >=
			if (lpeek(lexer) == '=') 
			{
				lnext(lexer);
				return tnew(GEQ, ">=");
			}
			else return tnew(GTR, ">");
			lnext(lexer);
			break;

		case '&': // &&
			if (lpeek(lexer) == '&') 
			{
				lnext(lexer);
				return tnew(LAND, "&&");
			}
			else return tnew(CAST, "&");
			lnext(lexer);
			break;

		case '|': // ||
			if (lpeek(lexer) == '|') 
			{
				lnext(lexer);
				return tnew(LOR, "||");
			}
			else return tnew(SEPARATE, "|");
			lnext(lexer);
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
		return NULL;
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
		return NULL;
	}

}

_unified _nooverflow Token* ltokenizeString(Lexer* lexer)
{
	// CALCULATE
	size_t strlen = 1;

	lnext(lexer); // LEADING "
	size_t start = lexer->symbol;


	while (lexer->src[lexer->symbol] != '"' && lexer->src[lexer->symbol] != '\0')
	{
		if (lexer->src[lexer->symbol] == '\\')
		{
			strlen++;
			lnext(lexer);
		}

		strlen++;
		lnext(lexer);
	}

	lexer->symbol = start;

	char* str = calloc(strlen, sizeof(char));

	if (str)
	{
		for (size_t i = 0; i < strlen - 1; i++)
		{
			str[i] = lexer->src[lexer->symbol];
			lnext(lexer);
		}
		str[strlen - 1] = '\0';

		lnext(lexer); // TRAILING "

		return tnew(STRINGEXPR, str);
	}

	else
	{
		error(0, -1, "syntax.c");
		return NULL;
	}
	

}

// ADDITIONALS

_unhandled _nooverflow Token* lkeywordTable(Lexer* lexer, char* name) {

	if (strcmp(name, "alias") == 0)
	{
		return tnew(KALI, "alias");
	}
	else
	{
		return tnew(NAME, name);
	}

}