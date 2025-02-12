#include "../headers/error.h"

_errorhandling void warn(short code, char* details)
{
	
};
_errorhandling void error(short code, char* details)
{
	switch(code) {
	case 0:
		printf("K0000: Insufficient memory for program execution, at [%s].", details);
	}
};