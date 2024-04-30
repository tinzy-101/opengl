#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
using namespace std;

// setting up fragment and vertex shaders (source code)
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
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "more triangle", NULL, NULL);
	if(window == NULL) {
		cout << "cant open window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	// tell glad to load needed configs for opengl
	gladLoadGL();

	// tell opengl where to render in
	glViewport(0, 0, 800, 800);

	// after creating the viewport, need to start setting up the vertex and fragment shaders
	// source code for the shaders are above, but have no actual shaders that we can use
	// create reference value to store vertex shader object in
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// pass in reference value we created above and point it to the source code above main 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// need to compile the shader source code so gpu understands it
	glCompileShader(vertexShader);

	// create reference variable to store fragment shader in
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// poin the reference variable to the frag shader source code above + specify only want 1 string for whole shader, with a last part that doesn't matter
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile the fragment shader so gpu understands
	glCompileShader(fragmentShader);


	// now that we've created our shaders, need to wrap them in a shader program so tey can actually be used
	// create reference variable for shader program 
	GLuint shaderProgram = glCreateProgram();
	// attach shader to shader program: need to pass in reference to shader program + reference to shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// now shaders attached to shader program, need to wrap up and link all shader together into shader program
	glLinkProgram(shaderProgram);
	
	// to keep program clean, delete the shaders now that we've created them
	// they are already linked into the program, so we can use them (thanks to the shader program), even if the o.g. shaders are deleted
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// create GLfloat array of vertices (safer than reg floats)
	// choose any floats [-1, 1]
	// create a right triangle!
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.3f, 0.0f
	};

	// now that we have vertices and shaders, want to create VAO and VBO to store vertice and buffer data
	// tells opengl what to do with vertices we defined 
	GLuint VAO, VBO;
	// generate VAO object (1 object + reference intereger VAO)
	glGenVertexArrays(1, &VAO);
	// generate VBO buffer object (point back to reference int
	glGenBuffers(1, &VBO);

	// bind VAO so we can use it later on, after we define the VBO
	glBindVertexArray(VAO);

	// binding in opengl = make an object the current object 
	// want to bind VBO as the buffer (following the opengl type GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// store vertices in the VBO
	// specify buffer type, size of data, actual data, use of data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// now that the VBO is packed with the vertex data, opengl still needs to know where to find the object and data 
	// tell vertex array object to store pointers to VBO(s) + tell opengl how to interpret them
	// specify position of vertex attrib, how many values per vertex, type of values making up vertices, GL_FALSE (only matters if we have coords as ints), stride of vertices = num data b/w vertices, offset = pointer to where vertices begin in array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// now that VAO is loaded and configured, need to activate it
	glEnableVertexAttribArray(0);

	// make extra sure that the VAO and VBO are binding to 0, start of vertex attrib
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// now shaders, VAO/VBO fully configured!
	
	while(!glfwWindowShouldClose(window)) {
		// color background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean back buffer + assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		// tell opengl to use shaderProgram
		glUseProgram(shaderProgram);

		//bind VAO so opengl knows to use specific VAO
		glBindVertexArray(VAO);

		// to actually draw the vertices and connect them as a shape
		// specify primitive, starting indice, and amount of vertices to draw
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
