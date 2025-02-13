#include "../headers/error.h"
_errorhandling void warn(short code, int line, char* details)
{
};
_errorhandling void error(short code, int line, char* details)
{
	switch(code) {
	case 0:
		printf("K0000: Insufficient memory for program execution, at [%s, line %d].", details, line); exit(2); break;
	case 1000:
		printf("K1000: Incorrect declaration of a number literal, at [%s, line %d]", details, line); exit(2); break;
	}
	
};