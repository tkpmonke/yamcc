#pragma once

#include <stdint.h>

/// load file from disk
/// is_local_file is for files that are in the same folder as the
/// executable
char* dump_file(char* path, uint8_t is_local_file);

/// gets executable path
/// uses non-cross platform api
char* exe_path();

/// uses malloc, ensure memory is free'd once usage is done
char* duplicate_string(char*);
