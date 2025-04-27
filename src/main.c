#include "renderer.h"
#include "texture_atlas.h"
#include "chunks.h"

#include <stdio.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1280, 720, "YAMCC", NULL, NULL);
	glfwMakeContextCurrent(window); 

	glewInit();
	glEnable(GL_DEPTH_BUFFER);
	//glEnable(GL_CULL_FACE);

	camera camera = {
		.fov = glm_rad(75),
		.position = {0,0,5},
		.rotation = {0,0,0}
	};

	chunk_mesh m = simplify_chunk_to_mesh(test_chunk);

	drawable_object obj = {
		.vertices = m.vertices,
		.indices = m.indices,
		.indice_count = m.indice_count,
		.vertex_count = m.vertex_count,
		.position = {0,0,0}
	};

	create_drawable_object(&obj);
	main_texture_atlas = create_texture_atlas("textures/atlas1.png");

	uint8_t wireframe = 0;
	uint8_t pstate = 0;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		int w,h;
		static int pw,ph;
		glfwGetWindowSize(window, &w, &h);

		if (w != pw || h != ph) {
			glViewport(0, 0, w, h);
			pw = w;
			ph = h;
		}

		camera.position[1] = sin(glfwGetTime())*2;
		get_camera_matrices(&camera, (h==0) ? 1.0f : (float)w/h);

		if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
			if (pstate == 0) {
				wireframe = !wireframe;
				pstate = 1;
				glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
			}
		} else {
			pstate = 0;
		}
		
		glClearColor(0.2f, 0.3f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_object(&obj, &camera);
		glfwSwapBuffers(window);
	}

	destroy_drawable_object(&obj);

	glfwDestroyWindow(window);
	glfwTerminate();
}
