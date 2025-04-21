#include "renderer.h"
#include "files.h"

#include <stdio.h>
#include <GLFW/glfw3.h>

  

int main() {

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1280, 720, "YAMCC", NULL, NULL);
	glfwMakeContextCurrent(window); 

	glewInit();
	glEnable(GL_DEPTH_BUFFER);

	printf("exe path > %s\n", exe_path());
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	drawable_object obj = {
		.vertices = vertices,
		.indices = indices,
		.indice_count = 6
	};

	create_drawable_object(&obj);

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
		
		glClearColor(0.2f, 0.3f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_object(&obj);
		glfwSwapBuffers(window);
	}

	destroy_drawable_object(&obj);

	glfwDestroyWindow(window);
	glfwTerminate();
}
