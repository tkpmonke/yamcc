#pragma once

#include <GL/glew.h>

/// object that can be called...
/// pretty straight forward
typedef struct drawable_object {
	float* vertices;
	unsigned int* indices;
	int indice_count;
	unsigned int vao,vbo,ebo;
	unsigned int program;
} drawable_object;

/// expects vertices and indices to already be set, but
/// is required to be called to actually draw the object
void create_drawable_object(drawable_object*);

/// do i need to explain what this function does?
void draw_object(drawable_object*);

/// frees opengl buffers and such
void destroy_drawable_object(drawable_object*);
