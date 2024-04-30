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

	// tell glad to load needed configs for opengl
	gladLoadGL();
	// tell opengl to open viewport = area that we want opengl to render in
	// go from bottom left corner (0,0) to top right (800, 800)
	glViewport(0, 0, 800, 800);

	// tell opengl to prepare to clear color of a buffer and give another color
	// (r, g, b, alpha), alpha = transparency (1=opaque,  0=transparent)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// tell opengl to actually execute the command we told it to prepare for
	glClear(GL_COLOR_BUFFER_BIT);

	// right now have buffer w/ colors (from glClearColor) and front buffer w/ default color
	// want to swap the front and back buffers so we can see our colors
	glfwSwapBuffers(window);

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
