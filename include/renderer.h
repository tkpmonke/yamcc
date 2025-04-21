#pragma once

typedef struct drawable_object {
	float* vertices;
	int* indices;
	unsigned int vao;
	unsigned int program;
} drawable_object;

void create_drawable_object(drawable_object*);
void draw_object(drawable_object*);
