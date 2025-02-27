#include "../headers/parser.h"
#include "../utools/definitions.h"



_nooverflow Parser* psnew(Lexer* lexer)
{
	Parser* parser = (Parser*)calloc(1, sizeof(struct Parser));

	if (parser)
	{
		parser->lexer = lexer;
		parser->t = NULL;

		return parser;
	}
	else
	{
		error(0, -1, "parser.c");
		return NULL;
	}

}

_nooverflow void peat(Parser* parser, int token)
{
	if (parser->t->type == token)
	{
		parser->t = ltokenize(parser->lexer);
	}
	else
	{
		error(1001, parser->lexer->line, "*.k");
	}
}

_unhandled Node* pparse(Parser* parser, Scope* scope)
{
	parser->t = ltokenize(parser->lexer);

	Node* generic = crnode();
	generic->object = crobj();
	generic->object->Objtype = SEQUENCE;

	size_t statements = 0;

	// COUNT STATEMENTS

	while (parser->t->type != TEOF)
	{
		if (parser->t->type == SEMICOLON)
		{
			statements++;
		}
	}

	parser->lexer->symbol = 0; // return back to start;

	// EXECUTE
	

	while (parser->t->type != TEOF)
	{
		if (parser->t->type != NOTHING)
		{
			Node* action = pstatement(parser, scope);
		}
	}
	
	return NULL;
}

_unhandled Node* pstatement(Parser* parser, Scope* scope)
{
	while (parser->t->type != SEMICOLON)
	{
		switch (parser->t->type)
		{

		}
	}

	return NULL;
}



// STRICT STATEMENT PARSING
