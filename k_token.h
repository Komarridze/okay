#pragma once
typedef struct TOKEN_STRUCT
{
	enum 
	{
		TOKEN_ID,
		TOKEN_EOF,
		TOKEN_NEWL,
		TOKEN_CAST,
		TOKEN_NUMBER,
		TOKEN_NEGATIVE,

		TOKEN_ADD,
		TOKEN_SUBSTRACT,
		TOKEN_MULTIPLY,
		TOKEN_DIVIDE,

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


