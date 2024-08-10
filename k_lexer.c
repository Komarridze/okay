#include "k_lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define notnullptr != '\0'
 

lexer_T* init_lexer(char* contents) {
	lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
	if (lexer notnullptr) {
		lexer->contents = contents;
		lexer->i = 0;
		lexer->c = contents[lexer->i];
	}
	
	return lexer;
};

void lx_advance(lexer_T* lexer) {
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];

	}
	
};

void lx_skipspace(lexer_T* lexer) {
	while (lexer->c == ' ' || lexer->c == 10 || lexer->c == 13) {
		lx_advance(lexer);
	}
};

token_T* lx_nexttoken(lexer_T* lexer) {
	
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
		//printf("%d\n", lexer->c);
		if (lexer->c == ' ' || lexer->c == 10 || lexer->c == 13)
			lx_skipspace(lexer);
		
		if (isalnum(lexer->c))
			return lx_collectid(lexer);
		
		if (lexer->c == '"')
			return lx_collectstr(lexer);
		
		switch (lexer->c) {
		
		
		case '@': return lx_advanceWtoken(lexer, init_token(TOKEN_CAST, lx_ccharToString(lexer))); break;
		case ',': return lx_advanceWtoken(lexer, init_token(TOKEN_COMMA, lx_ccharToString(lexer))); break;
		case '=': return lx_advanceWtoken(lexer, init_token(TOKEN_EQUALS, lx_ccharToString(lexer))); break;
		case ';': return lx_advanceWtoken(lexer, init_token(TOKEN_SEMI, lx_ccharToString(lexer))); break;
		case '(': return lx_advanceWtoken(lexer, init_token(TOKEN_LEFTP, lx_ccharToString(lexer))); break;
		case ')': return lx_advanceWtoken(lexer, init_token(TOKEN_RIGHTP, lx_ccharToString(lexer))); break;
		}
		
	}

	return init_token(TOKEN_EOF, "\0");
};

token_T* lx_collectstr(lexer_T* lexer) {

	lx_advance(lexer);
	char* value = calloc(1, sizeof(char));
	if (value notnullptr)
	{
		
	value[0] = '\0';

		while (lexer->c != '"') { //skip '\', special symbol determinaed in parser
			if (lexer->c == ';') {

				return init_token(TOKEN_STRINGEXPR, value);
			}
			char* s = lx_ccharToString(lexer);
			char* x = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
			if (x != '\0') {
				value = x;
				strcat_s(value, (strlen(value) + strlen(s) + 1) * sizeof(char), s);
			} 
				
			
			lx_advance(lexer);
			

		}

		lx_advance(lexer);
		return init_token(TOKEN_STRINGEXPR, value);

	}
};

token_T* lx_collectid(lexer_T* lexer) {

	char* value = calloc(1, sizeof(char));
	if (value notnullptr)
	{

		value[0] = '\0';

		while (isalnum(lexer->c)) {
			char* s = lx_ccharToString(lexer);
			char* x = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
			if (x != '\0') {
				value = x;
				strcat_s(value, (strlen(value) + strlen(s) + 1) * sizeof(char), s);
			}

			lx_advance(lexer);

		}

		return init_token(TOKEN_ID, value);

	}
};


token_T* lx_advanceWtoken(lexer_T* lexer, token_T* token) {
	lx_advance(lexer);
	return token;
};

char* lx_ccharToString(lexer_T* lexer) {
	char* str = calloc(2, sizeof(char));
	if (str notnullptr) {
		str[0] = lexer->c;
		str[1] = '\0';
	}

	return str;
};