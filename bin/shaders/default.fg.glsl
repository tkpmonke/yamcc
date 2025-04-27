#version 330 core

out vec4 color;
in vec2 uv;
in vec2 offset;

uniform sampler2D atlas;

void main() {
	color = texture(atlas, (uv+vec2(offset.x, 15-offset.y))/16);
}
