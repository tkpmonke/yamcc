#pragma once

#define CHUNK_SIZE 2

#include <stdint.h>
typedef uint8_t chunk[CHUNK_SIZE][CHUNK_SIZE];

typedef struct chunk_mesh {
	float* vertices;
	unsigned int* indices;
	unsigned int vertex_count;
	unsigned int indice_count;
} chunk_mesh;

extern chunk test_chunk;
chunk_mesh simplify_chunk_to_mesh(chunk chunk);

