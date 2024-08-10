#include "io.h"
#include <stdlib.h>
#include <stdio.h>

char* getfilecontents(const char* filepath) {
	char* buffer = 0;
	long length;

	FILE* f = fopen(filepath, "rb");

	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);

		buffer = calloc(length, length);

		if (buffer && length != -1L) 
			fread(buffer, 1, (size_t)length, f);

		fclose(f);
		return buffer;
	}

	printf("K0000: Error reading file %s\n", filepath);
	exit(2);
}
