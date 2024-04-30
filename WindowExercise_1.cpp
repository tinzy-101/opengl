#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

int main() {
	
	// startup glfw
	glfwInit();

	//tell glfw that we want to use a version 4.6 of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// tell glfw to only pull functions from the opengl core profile (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window object that we can refer back to
	// specifics width 400, height 225, and name of window w/ no fullscreen
	GLFWwindow* window = glfwCreateWindow(400, 225, "I made this!", NULL, NULL);

	// error checking in case window can't be opened
	if(window == NULL) {
		cout << "Failed to open window" << endl;
		return -1;
	}

	// create window part of current context
	glfwMakeContextCurrent(window);

	// load opengl dependencies to create viewport where things are rendered
	gladLoadGL();
	glViewport(0,0, 400, 225);
	
	// set up opengl to create back buffer that has all orange pixels, then swap buffers to display back as front
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// keep window up unless manually closed
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	// close glfw
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
