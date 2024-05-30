#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
using namespace std;

/*********************************************************************************************************
 * Index Buffers:
 *		- if for example want to create a triangle that is segmented into 4 triangles, then will get 3 *4 
 *			- want to have middle triangle upside down and cut out
 *		points = 9 vertices
 *		- however, 6  of those points are overlapping
 *		- in reality, only need to program 5 vertices, if you count the overlapping vertices toether (0 - 5, so 6 vertices total) 
 *		- however, giving those 5 vertices to opengl, it will draw small upside down triangle ontop of big triangle, which is not what we want
 *			- need index buffer! tells opengl what order to go over vertices
 *			- for duplicates, can go over same vertices twice using indices!
 *
 *
 ************************************************************************************************************/

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
"	FragColor = vec4(0.0f, 1.0f, 0.6f, 1.0f);\n"
"}\n\0";

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "index buffers!", NULL, NULL);
	if(window == NULL) {
		cout << "window broke :(" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader, glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vertices[] {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower right 
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
	};

	// index buffer
	// we labelled each vertices w/ 1 number in a diagram earlier, and these indices say which order to draw stuff
	GLuint indices[] = {
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right tri
		5, 4, 1 // upper tri
	}

	// create reference value for index buffer (very similar to code for VBO)
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	  	glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
