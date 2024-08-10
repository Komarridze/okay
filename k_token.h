#pragma once
#ifndef K_TOKEN_H
#define K_TOKEN_H
typedef struct TOKEN_STRUCT
{
	enum 
	{
		TOKEN_ID,
		TOKEN_EOF,
		TOKEN_NEWL,
		TOKEN_CAST,

		TOKEN_EQUALS,
		TOKEN_SEMI,
		TOKEN_LEFTP,
		TOKEN_RIGHTP,
		TOKEN_COMMA,

		TOKEN_LEFTBR,
		TOKEN_RIGHTBR,
		
		TOKEN_STRINGEXPR
	} type;

	char* value;

} token_T;

token_T* init_token(int type, char* value);

#endif // !K_TOKEN_H
