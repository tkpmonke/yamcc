#include "renderer.h"
#include "files.h"

#include <assert.h>
#include <stdio.h>

/// text for shaders, gets loaded in first time create_drawable_object gets called
char* default_vertex_shader = NULL;
char* default_fragment_shader = NULL;

void create_drawable_object(drawable_object* object) {
	/// load in shaders
	
	if (default_vertex_shader == NULL
			|| default_fragment_shader == NULL) {
		default_vertex_shader = dump_file("shaders/default.vs.glsl", 1);
		default_fragment_shader = dump_file("shaders/default.fg.glsl", 1);

		assert((default_vertex_shader != NULL) && "Failed to load 'shaders/default.vs.glsl' (does it exist?)");
		assert((default_fragment_shader != NULL) && "Failed to load 'shaders/default.fg.glsl' (does it exist?)");
	}

	char info_log[512];
	int success;

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, (const char**)&default_vertex_shader, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		printf("Vertex Shader Failed To Compile > %s", info_log);
	}

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, (const char**)&default_fragment_shader, NULL);
	glCompileShader(fragment);
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		printf("Vertex Shader Failed To Compile > %s", info_log);
	}

	
	object->program = glCreateProgram();
	glAttachShader(object->program, vertex);
	glAttachShader(object->program, fragment);
	glLinkProgram(object->program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	glGenVertexArrays(1, &object->vao);
	glBindVertexArray(object->vao);
	glGenBuffers(1, &object->vbo);
	glGenBuffers(1, &object->ebo);

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(12+8), object->vertices, GL_STATIC_DRAW); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->indice_count*sizeof(int), object->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
}

void draw_object(drawable_object* object) {
	glUseProgram(object->program);
	glBindVertexArray(object->vao);
	glDrawElements(GL_TRIANGLES, object->indice_count, GL_UNSIGNED_INT, 0);
}

void destroy_drawable_object(drawable_object* object) {
	glDeleteVertexArrays(1, &object->vao);
	glDeleteBuffers(1, &object->vbo);
	glDeleteBuffers(1, &object->ebo);
	glDeleteProgram(object->program);
}
