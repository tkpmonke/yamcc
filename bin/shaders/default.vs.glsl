#version 330 core

layout (location = 0) in vec3 pos;
out vec3 position;

uniform mat4 mvp;

void main() {
	gl_Position = vec4(pos,1);
	position = pos;
}
