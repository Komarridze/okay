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

	Lexer* lexer = lnew("blablabla");

	ltokenize(lexer, lexer->src);

	return 0;


}