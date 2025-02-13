#include "../headers/syntax.h"

// This is the main entry for the Clutch Combiner.
// Any change could cause severe damage to program execution.
// Modify with caution.
//
// We are not held responsible for any damage this
// could cause or lead to.
//
// YOU HAVE BEEN WARNED.


int main() {
	
	Lexer* lexer = lnew("blablabla 0.4f");
	Token* t;

	while ((t = ltokenize(lexer))->type != TEOF) {
		printf("%d %s", t->type, t->contents);
	}
	


	return 0;


}