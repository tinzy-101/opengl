#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
using namespace std;


// fragment and vertex shaders copy-pasted in (will learn later)
// first specify coordinates of vertices (ignore z axis bc only working in 2D)
// for x-y axis, origin is in middle of window (x right, y up)
// 	- coordinate is normalized (x: -1-->1, y: -1-->1)
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

	GLFWwindow* window = glfwCreateWindow(800, 800, "triangle time!!", NULL, NULL);

	if(window == NULL) {
		cout << "cannot open window \n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// rn we have source code for fragment/vertex shaders, but no actual shaders (Shaders are opengl objects)
	// shaders live in background in mem, and need to be accessed w/ a reference (applies to ALL objects in opengl)
	// need to create value/reference to store vertex shader object in
	// 	- use GLuint = opengl unsigned integer
	// 	- specify that u want the gl vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// pass in our reference value vertexSahder, specify only using 1 string for whole shader, and point to the source code (stuff above main function), and last part doesn't matter
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// gpu can't understand source code (vertexShader = reference to obj), so it needs to be compiled rn using gl compile function
	glCompileShader(vertexShader);

	// replicate vertexShader creation for fragment shader creation
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// now we have our shaders! BUT b4 we can actually use them, they need to be wrapped into shader program
	// create reference variable for shader program, then attach shader to the shader program
	GLuint shaderProgram = glCreateProgram();
	// need to plug in reference to shader program AND reference to the shader u want to be attached to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// now that we've attached both shaders to the shader program, need to wrap up shader program
	glLinkProgram(shaderProgram);

	// to keep things clean, delete shaders created b4
	// they are alrd in the program itself, so we're all good
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	// create array of vertices w/ datatype GLfloat (diff than reg floats, safer to use opengl version)
	// create coordinates: every 3 floats (ie every line) = 1 coordinate (zero out z-coord)
	// can choose ANY floats [-1,1] (exclusive or inclusive, not sure) 
	// 	- this is bc normalized window explained above w/ shaders
	// will get equilateral triangle
	GLfloat vertices[] = 
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // upper corner
	};



	// jumping back to create VAOs, after VBOs were created...
	// VERY IMPORTANT: VAO created BEFORE create VBO
	GLuint VAO;

	// we've created our shaders, but running code won't do anything bc we havent told shader to do anything with vertices we specified
	// since sending info from cpu to gpu to render stuff is slow, want to send data is big batches thru BUFFERS (NOT same buffers as front and back buffers for the screen)
	// need to create buffers!
	// 	-want to use reference integer for the buffer
	GLuint VBO;


	// generate a VAO object by saying we only have 1 object + point to reference integer VAO
	glGenVertexArrays(1, &VAO);

	// create buffer object
	// 	- 1 = only have 1 buffer for object
	// 	- point the buffer object back to reference int, VBO
	glGenBuffers(1, &VBO);


	// bind VAO so we can work with it
	glBindVertexArray(VAO);
	// now that we've configured the VAO, jump back down past where VBO was created to configure VAO so we can use it with pointers to VBOs!

	// binding in opengl = make an object the "current" object
	// 	- whenever a function does stuff that only affects a certain type of object that is the same type as the current object, then the current object (binded object) is the one that is acted on my the function
	// GL_ARRAY_BUFFER = type needed for vertex buffer
	// 	- can find other types in opengl docs
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// store our vertices in VBO
	// 1. specify buffer type
	// 2. size of data
	// 3. give actual data (the vertices)
	// 4. specify use of that data (GL_ + STREAM, STATIC, or DYNAMIC + DRAW, READ, or COPY)
	// 	- STREAM: vertices modded once, used a few times
	// 	- STATIC: vertices modded once, used many times
	// 	- DYNAMIC: vertices modded many times, used many times
	// 	
	// 	- DRAW: vertices are modded and used to draw image on screen
	// 	- READ: no explanation
	// 	- COPY: no explanation
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// now have an object packed with our vertex data! (VBO)
	// BUT opengl still doesnt know where to find the object/data
	// use vertex array object (VAO) to store pointers to 1+ VBOs + tells opengl how to interpret them
	// VAO = make it easier to quickly switch b/w VBOs w/ all our vertex data
	// want to go back to def of VBO, and define VAO before VBO

	//...
	
	// we've just created the VAO above the VBO
	// now we want to create VAOs to help opengl understand what to do with VBOs
	// pass index of vertex attribute we want to use 
	// 	- vertex attrib = way of communicating w/ vertex shader from outside (talk more later)
	// 	- first input = position of vertex attrib = 0
	// 	- 2nd input = how many values per vertex (3 b/c 3 floats)
	// 	- 3rd input = what type of values we have making up vertices = GL_FLOAT
	// 	- 4th input = only matters if we have coords as ints, so just = GL_FALSE
	// 	- 5th input = stride of vertices = amount of data b/w each vertex = 3 * sizeof(float) b/c we have 3 floats defining each vertex
	// 	- 6th input = offset = pointer to where vertices begin in array = beginning of array = weird pointer = (void*)0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 

	// before we can actually use the vertex attribute we just configred, need to activate
	// 0 = position of vertex attribute
	glEnableVertexAttribArray(0);

	// not super necessary next step, but good to do to be sure VAO and VBO are binded to 0 = start og vertex attribute
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// now everything is fully configured!
	// to keep things clean, go to end of program (b4 destroying window) to delte VAO & VBOs

cout << "I made it!\n";

	while(!glfwWindowShouldClose(window)) {
		// after creating and configuring VAO, VBO, and objects + deleted them, copy the color change + clearing into while loop
		// specify color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// then, activate shader program
		glUseProgram(shaderProgram);
		// bind VAO so opengl knows we want to use a specific VAO 
		// 	- not strictly necessary rn, bc only have 1 object and 1 VAO, but is good practice for when things get more complicated later on
		glBindVertexArray(VAO);

		// for drawing function, specify type of primitive we wantt o use (triangle), startng indices of vertices (0), and amount of vertices we want to draw (3)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//make sure we swap buffers so image is updated each frame
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	// delete VAO and VBO + all objects created so far
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	
	// now that we've configures VAO, VBO, and all necessary objects, and deleted them at end, just need to go back to while loop and add in color / switching buffers part

	cout << "I made it to the end" << endl;

	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}
