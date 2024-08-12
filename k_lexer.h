#pragma once
#ifndef K_LEXER_H
#define K_LEXER_H
#include "k_token.h"

typedef struct LEXER_STRUCT {
	char c;
	unsigned long int i;
	char* contents;
} lexer_T;

lexer_T* init_lexer(char* contents);

void lx_advance(lexer_T* lexer);

void lx_skipspace(lexer_T* lexer);

token_T* lx_nexttoken(lexer_T* lexer);

token_T* lx_collectstr(lexer_T* lexer);

token_T* lx_collectid(lexer_T* lexer);

token_T* lx_collectnum(lexer_T* lexer);

token_T* lx_advanceWtoken(lexer_T* lexer, token_T* token);

char* lx_ccharToString(lexer_T* lexer);

#endif // !LEXER_H


