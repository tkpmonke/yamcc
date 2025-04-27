#include "chunks.h"
#include "blocks.h"

#include <string.h>

/*
chunk test_chunk = {
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }
};*/

chunk test_chunk = {{2,2},{3,3}};

float cube_vertices[24*7] = {
	 -0.5f, -0.5f, -0.5f,	0,0,	1,1,
     0.5f, -0.5f, -0.5f,	1,0,	1,1,
     0.5f,  0.5f, -0.5f, 	1,1,	1,1,
    -0.5f,  0.5f, -0.5f,	0,1,	1,1,
    -0.5f, -0.5f,  0.5f,	0,0,	1,1,
     0.5f, -0.5f,  0.5f,	1,0,	1,1,
     0.5f,  0.5f,  0.5f, 	1,1,	1,1,
    -0.5f,  0.5f,  0.5f,	0,1,	1,1,

    -0.5f,  0.5f, -0.5f,	0,0,	1,1,
    -0.5f, -0.5f, -0.5f,	1,0,	1,1,
    -0.5f, -0.5f,  0.5f, 	1,1,	1,1,
    -0.5f,  0.5f,  0.5f,	0,1,	1,1,
     0.5f, -0.5f, -0.5f,	0,0,	1,1,
     0.5f,  0.5f, -0.5f,	1,0,	1,1,
     0.5f,  0.5f,  0.5f, 	1,1,	1,1,
     0.5f, -0.5f,  0.5f,	0,1,	1,1,

    -0.5f, -0.5f, -0.5f,	0,0,	0,0,
     0.5f, -0.5f, -0.5f,	1,0,	0,0,
     0.5f, -0.5f,  0.5f,  	1,1,	0,0,
    -0.5f, -0.5f,  0.5f,	0,1,	0,0,
     0.5f,  0.5f, -0.5f,	0,0,	1,0,
    -0.5f,  0.5f, -0.5f,	1,0,	1,0,
    -0.5f,  0.5f,  0.5f, 	1,1,	1,0,
     0.5f,  0.5f,  0.5f,	0,1,	1,0,
};

unsigned int cube_indices[36] = {
	0,  3,  2,
	2,  1,  0,
	4,  5,  6,
	6,  7,  4,
	11, 8,  9,
	9,  10, 11,
	12, 13, 14,
	14, 15, 12,
	16, 17, 18,
	18, 19, 16,
	20, 21, 22,
	22, 23, 20
};


chunk_mesh simplify_chunk_to_mesh(chunk chunk) {
	float* vertices = (float*)malloc(CHUNK_SIZE * CHUNK_SIZE * 24 * 7 * sizeof(float));
	unsigned int* indices = (unsigned int*)malloc(CHUNK_SIZE * CHUNK_SIZE * 36 * sizeof(unsigned int));
	
	unsigned int vertex_count = 0;
	unsigned int index_count = 0;

	// Define face data: vertex offset, index offset, and neighbor check direction
	struct {
		int v_start;	// Starting index in cube_vertices (per face)
		int i_start;	// Starting index in cube_indices (per face)
		int dx, dy;	 // Neighbor direction to check
	} faces[] = {
		{0,  0,  0, -1},   // Front face (Z-)
		{4,  6,  0,  1},   // Back face (Z+)
		{8,  12, -1, 0},   // Left face (X-)
		{12, 18, 1,  0},   // Right face (X+)
		{16, 24, 0,  0},   // Bottom face (Y-)
		{20, 30, 0,  0}	// Top face (Y+)
	};

	for (int x = 0; x < CHUNK_SIZE; ++x) {
		for (int y = 0; y < CHUNK_SIZE; ++y) {
			if (chunk[x][y] == 0) continue;

			// Check all 6 faces
			for (int f = 0; f < 6; f++) {
				int nx = x + faces[f].dx;
				int ny = y + faces[f].dy;

				switch (f) {
					case(0):
						if (ny > 0)
							continue;
						break;
					case(1):
						if (ny >= CHUNK_SIZE)
							continue;
						break;
					case(2):
						if (nx > 0)
							continue;
						break;
					case(3):
						if (nx >= CHUNK_SIZE)
							continue;
						break;
				}

				// Copy vertices for this face (4 vertices)
				for (int v = 0; v < 4; v++) {
					int src_idx = (faces[f].v_start + v) * 7;
					vertices[vertex_count++] = cube_vertices[src_idx + 0] + x;
					vertices[vertex_count++] = cube_vertices[src_idx + 1];
					vertices[vertex_count++] = cube_vertices[src_idx + 2] + y;
					vertices[vertex_count++] = cube_vertices[src_idx + 3];
					vertices[vertex_count++] = cube_vertices[src_idx + 4];
					
				  	const float* offset;
					switch (f) {
						case (0):
							offset = cs_blocks[chunk[x][y]].forward_offset;
							break;
						case (1):
							offset = cs_blocks[chunk[x][y]].back_offset;
							break;
						case (2):
							offset = cs_blocks[chunk[x][y]].left_offset;
							break;
						case (3):
							offset = cs_blocks[chunk[x][y]].right_offset;
							break;
						case (4):
							offset = cs_blocks[chunk[x][y]].bottom_offset;
							break;
						case (5):
							offset = cs_blocks[chunk[x][y]].top_offset;
							break;
					}

					vertices[vertex_count++] = offset[0];
					vertices[vertex_count++] = offset[1];
				}

				// Copy indices for this face (6 indices)
				for (int i = 0; i < 6; i++) {
					indices[index_count++] = cube_indices[faces[f].i_start + i] + 
											(vertex_count / 7 - 4); // Adjust offset
				}
			}
		}
	}

	// Trim arrays to actual used size
	vertices = realloc(vertices, vertex_count * sizeof(float));
	indices = realloc(indices, index_count * sizeof(unsigned int));

	return (chunk_mesh) {
		.vertices = vertices,
		.indices = indices,
		.vertex_count = vertex_count / 7,  // 7 elements per vertex
		.indice_count = index_count
	};
}
