#include "../headers/syntax.h"
#include "../headers/parser.h"

// This is the main entry for the Clutch Combiner.
// Any change could cause severe damage to program execution.
// Modify with caution.
//
// We are not held responsible for any damage this
// could cause or lead to.
//
// YOU HAVE BEEN WARNED.


int main() {
	
	Lexer* lexer = lnew("\"loh\nebaniy\"");
	
	//Parser* parser = psnew(lexer);
	//parser->scope = scnew();


	
	Token* t;
	while ((t = ltokenize(lexer))->type != TEOF) {
		printf("%d %s \n", t->type, t->contents);
	}
	
	


	return 0;


}