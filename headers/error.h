#ifndef K_ERROR_H
#define K_ERROR_H
#include <stdio.h>
#include <stdlib.h>
#include "../utools/definitions.h"

// Displays a warning.
// [okay.error.warn]
_errorhandling void warn(short code, int line, char* details);

// Emits an error.
// [okay.error.error]
_errorhandling void error(short code, int line, char* details);

#endif