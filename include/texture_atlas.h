#pragma once

typedef struct texture_atlas {
	unsigned int program;
	const char* path;
} texture_atlas;

extern texture_atlas main_texture_atlas;
texture_atlas create_texture_atlas(const char* path);
