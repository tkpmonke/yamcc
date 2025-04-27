#pragma once

#include <cglm/cglm.h>

typedef struct camera {
	vec3 position;
	vec3 rotation;

	vec3 forward,right,up;
	float fov;

	mat4 vp;
} camera;

void get_camera_matrices(camera*, float aspect_ratio);
