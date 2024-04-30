#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
using namespace std;

// create fragment and vertex shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";


int main() {
	
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "pointsssss", NULL, NULL);

	if(window == NULL) {
		cout << "no window ;-(" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	// area to render in
	glViewport(0, 0, 800, 800);

	// create reference to store vertex shader object into (gl unsigned int + specify vertex shader)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// pass in vertexShader source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile shader source code
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// wrap shaders into shader program b4 can use
	GLuint shaderProgram = glCreateProgram();
	// plug in reference to shader program + shaders u want to be attached to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// wrap up shader program after attached
	glLinkProgram(shaderProgram);

	// delete shaders after we link them to program, keeps things clean
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// create array of vertices
	GLfloat vertices[] = 
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
		0.5f, -05.f * float(sqrt(3)) / 3.0f, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2/3, 0.0f
	};
	
	// create VAO and VBO
	GLuint VAO, VBO;

	// create VAO object, only 1 object and pointed to reference var
	glGenVertexArrays(1, &VAO);
	// create buffer object (1)
	glGenBuffers(1, &VBO);

	// bind VAO to vertex array, same for buffer to VBO
	// binding = make object the "current" object
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// store vertices in VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// now have object packed with vertex data (VBO), but opengl doesn't know where to find stuff unless the VAO is there to help
	// define VAOs, pass in index of vertex attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//need to activate VAO b4 can use, starting at position 0
	glEnableVertexAttribArray(0);

	// for security, not necessary
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window)) {
		// background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// clean back buffer + assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		// activate shader program
		glUseProgram(shaderProgram);
		// bind VAO so opengl knows to use specific VAO
		glBindVertexArray(VAO);
		// draw triangle
		glDrawArrays(GL_POINTS, 0, 3);

		//swap buffers so image updated each frame!
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	// clean up time, delete everything
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// end
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


