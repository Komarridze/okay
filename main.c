#include <stdio.h>
#include "k_lexer.h"
#include "k_parser.h"
#include "k_visitor.h"
#include "io.h"

void print_help() {
	printf("Run by argv[1] <filename>");
}

int main(int argc, char* argv[]) {
	if (argc < 2)
		print_help();

	lexer_T* lexer = init_lexer(getfilecontents(argv[1]));

	parser_T* parser = init_parser(lexer);

	AST_T* root = ps_parse(parser, parser->scope);
	visitor_T* visitor = init_visitor();
	vt_visit(visitor, root);

	//printf("%d\n", root->type);
	//printf("%d\n", (int)root->compound_size);

	return 0;
}

