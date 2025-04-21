#define _POSIX_C_SOURCE 200112L // needed for readlink

#include "files.h"

#include <stdio.h> // needed for file io stuff
#include <stdlib.h> // needed for malloc
#include <string.h> // needed for strlen and memcpy
#include <libgen.h> // needed for dirname


char* dump_file(char* path, uint8_t is_local) {
	char* content = NULL;
	int size = 0;

	char* p;

	if (is_local) {
		p = strcat(strcat(exe_path(), "/"), path);
	} else {
		p = path;
	}

	FILE* fp = fopen(p, "r");
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

	content[size] = '\0';
	return content;
}

char buf[512];
#if defined(__unix__)

#include <unistd.h>
#include <limits.h>

char* exe_path() {
	ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf)-1);
	
	if (len == -1) return NULL;
	buf[len] = '\0';
	
	char* d = duplicate_string(buf);
	strcpy(buf, dirname(d));
	free(d);

	return buf;
}

#elif defined(_WIN32)
#include <windows.h>
#include <shlwapi.h>
char* exe_path() {
	GetModuleFileName(NULL, buf, 512);
	PathRemoveFileSpec(buf);
}
#endif

char* duplicate_string(char* str) {
	size_t len = strlen(str);
	char* out = malloc(len+1);
	memcpy(str, out, len+1);
	return out;
}
