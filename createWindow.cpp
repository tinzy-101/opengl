#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

int main() {
	
	//start up glfw, helps to create window + process external input but not rendering stuff
	glfwInit();

	//tell glfw what version of opengl we're using (give it a hint!)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//opengl profile = package of functions = core (modern functions), compatibility (older functions)
	//we only care about modern functions, so specify core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// datatype of window object in glfw: width, height, name, fullscreen or not, N/A 
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// error checking in case window doesn't open
	if(window == NULL) {
			  std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// tell glfw to make created window part of current context (even tho window created, can't use)
	glfwMakeContextCurrent(window);

	// while the window should not close (ie not pressing the close button, or theres not another function telling it to close), keep the window open and poll events
	while(!glfwWindowShouldClose(window)) {
		// tell glfw to process all polled events, e.g. window appearing, resizing, etc
		// if don't process the events, the window won't respond
		glfwPollEvents();
	}

	// destory window when you're done with it
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
