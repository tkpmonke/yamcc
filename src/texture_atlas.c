#include "texture_atlas.h"
#include "renderer.h"
#include "files.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string.h>

texture_atlas main_texture_atlas;

texture_atlas create_texture_atlas(const char *path) {
	char* p = strcat(strcat(exe_path(), "/"), path);
	texture_atlas a = {
		.path = p,
		.program = 0
	};
	
	glGenTextures(1, &a.program);
	glBindTexture(GL_TEXTURE_2D, a.program);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrchannels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(p, &width, &height, &nrchannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	stbi_image_free(data);
	return a;
}
