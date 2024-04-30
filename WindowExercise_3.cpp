#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(500, 500, "Window :)", NULL, NULL);

	if(window == NULL) {
		cout << "Unable to create window :-(" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 500, 500);

	// create vars for r, g, b, and instead the if statement increment the glclearcolor rgb values, then swap buffers inside too
	// i stole the implementation of time - prevTime
	// also good idea to use trig values to change color!!
	float r, g, b;

	float prevTime = float(glfwGetTime());
	
	 while(!glfwWindowShouldClose(window)) {	
		float time = float(glfwGetTime());
		if((time - prevTime) >= 0.5f) {
			r = ((float)rand()/(float)RAND_MAX); 
			g = ((float)rand()/(float)RAND_MAX); 
			b = ((float)rand()/(float)RAND_MAX); 
			
			glClearColor(r, g, b, 1.0f);	
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);

			glfwPollEvents();

			prevTime = time; 
		}	
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
