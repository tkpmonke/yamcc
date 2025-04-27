#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv_coords;
layout (location = 2) in vec2 offset_coords;
out vec2 uv;
out vec2 offset;

uniform mat4 mvp;

void main() {
	gl_Position = mvp*vec4(pos, 1);
	uv = uv_coords;
	offset = offset_coords;
}
