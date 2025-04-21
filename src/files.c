#include "files.h"

#include <stdio.h>
#include <stdlib.h>

char* dump_file(char* path) {
	char* content = NULL;
	int size = 0;

	FILE* fp = fopen(path, "r");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		rewind(fp);

		content = (char*)malloc(size+1);
		fread(content, 1, size, fp);
		fclose(fp);
	} else {
		return NULL;
	}
}
