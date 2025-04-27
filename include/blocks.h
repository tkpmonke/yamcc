#pragma once

#include <cglm/cglm.h>

typedef struct block {
	const char* name;
	
	vec2 top_offset;
	vec2 bottom_offset;
	vec2 left_offset;
	vec2 right_offset;
	vec2 forward_offset;
	vec2 back_offset;
} block;

const static block cs_blocks[4] = {
	{
		.name = "Air"
	},
	{
		.name = "Dirt Block",
		.top_offset 		= {0,0},
		.bottom_offset 	= {0,0},
		.left_offset 		= {0,0},
		.right_offset 		= {0,0},
		.forward_offset 	= {0,0},
		.back_offset 		= {0,0}
	},

	{
		.name = "Grass Block",
		.top_offset 		= {1,0},
		.bottom_offset 	= {0,0},
		.left_offset 		= {1,1},
		.right_offset 		= {1,1},
		.forward_offset 	= {1,1},
		.back_offset 		= {1,1}
	},

	{
		.name = "Cobblestone",
		.top_offset 		= {0,1},
		.bottom_offset 	= {0,1},
		.left_offset 		= {0,1},
		.right_offset 		= {0,1},
		.forward_offset 	= {0,1},
		.back_offset 		= {0,1}
	}
};
