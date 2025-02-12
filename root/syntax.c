#include "../headers/syntax.h"
#include "../headers/error.h"

_nooverflow Lexer* lnew(char* source_code) {
	
	Lexer * lexer = (Lexer*)calloc(1, sizeof(Lexer));

	if (lexer) {

		lexer->line = 0;
		lexer->symbol = 0;

		lexer->src = source_code;
		lexer->size = strlen(source_code);

		return lexer;

	}

	else {
		error(0, "syntax.c");
		exit(2);
	}

	
	
}

_nooverflow void ltokenize(Lexer* lexer, char* code)
{
	while (lexer->src[lexer->symbol] != '\0') {
		lnext(lexer);
	}


	printf("%d %d", (int)lexer->symbol, (int)lexer->size);

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