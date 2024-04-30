#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

int main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(700, 700, "Flicker Flicker", NULL, NULL);

	if(window == NULL) {
		cout << "can't display window :-(" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 700, 700);

	glClearColor(0.8f, 0.2f, 0.8f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	/*
	glClearColor(0.0f, 0.9f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	*/
	// putting the glfwSwapBuffers inside the while loop makes it go back and forth b/w the back and the front buffer defined
	// can only define 1, (0.8, 0.2, 0.8, 1.0), and the screen will flicker b/w the o.g. front buffer=black screen, and the newly defined back buffer
	while(!glfwWindowShouldClose(window)) {	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
