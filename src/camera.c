#include "camera.h"

void get_camera_matrices(camera* camera, float as) {
	mat4 projection = GLM_MAT4_IDENTITY_INIT;
	mat4 view = GLM_MAT4_IDENTITY_INIT;
	glm_perspective(camera->fov, as, 0.1f, 100.f, projection);
	float pitch = camera->rotation[1];
   float yaw = camera->rotation[0];
	camera->forward[0] = -sin(yaw)*cos(pitch);
   camera->forward[1] = sin(pitch);
   camera->forward[2] = -cos(yaw)*cos(pitch);
   glm_vec3_cross(camera->forward, (vec3){0,1,0}, camera->right);
   glm_normalize(camera->right);
   glm_vec3_cross(camera->right, camera->forward, camera->up);
   glm_normalize(camera->up);

   vec3 center;
   glm_vec3_add(camera->position, camera->forward, center);
   glm_lookat(camera->position, center, camera->up, view);

	glm_mat4_mul(projection, view, camera->vp);
}
