#include "k_token.h"
#include <stdlib.h>
#define notnullptr != '\0'

token_T* init_token(int type, char* value) {
	token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
	if (token notnullptr) {
		token->type = type;
		token->value = value;
	}

	
	return token;

};