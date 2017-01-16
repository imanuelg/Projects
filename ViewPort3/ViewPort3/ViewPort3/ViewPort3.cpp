// ViewPort3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

#include "Shader.h"

// GLEW
#define GLEW_STATIC



const GLuint WIDTH = 2000, HEIGHT = 1300;
int width, height;


// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
}


void drawTriangle()
{
	GLfloat vertices1[] = {
		0.5f, -0.5f, 0.0f,		// 1.0f, 0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,		//  0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f		//,   0.0f, 0.0f, 1.0f    // Top 
	};


	static float alpha = 0;
	//attempt to rotate cube
	glRotatef(alpha, 0, 1, 0);

	
	
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Draw our first triangle
	glEnableClientState(GL_VERTEX_ARRAY);
	


	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);


	glDisableClientState(GL_VERTEX_ARRAY);
	
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	
	alpha += 1;

}




void drawCube()
{
	GLfloat vertices1[] =
	{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,    //      0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,     //     1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,    //     0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,    //      0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,    //      0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1    //,       0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	static float alpha = 0;
	//attempt to rotate cube
	glRotatef(alpha, 0, 1, 0);



	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Draw our first triangle
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 24);
	glBindVertexArray(0);


	glDisableClientState(GL_VERTEX_ARRAY);
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	alpha += 1;

}




int main(int argc, char** argv)
{
	std::cout << "Ami ViewPort3" << std::endl;
	// Init GLFW
	glfwInit();
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	

	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	glfwGetFramebufferSize(window, &width, &height);
	
	

	//Shader ourShader("C:\\C++\\ViewPort3\\ViewPort3\\Debug\\default.vs", "C:\\C++\\ViewPort3\\ViewPort3\\Debug\\default.frag");

	while (!glfwWindowShouldClose(window))
	{

		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		// Draw stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		{
			glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);           // top left
			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			gluPerspective(80, (double)windowWidth / (double)windowHeight, 0.1, 100);
			glMatrixMode(GL_MODELVIEW_MATRIX);
			glTranslatef(0, 0, -5);
			//ourShader.Use();  // as soon as i use shader, image wont rotate
			drawTriangle();
			
		}

		{
			glViewport(windowWidth / 2, 0, windowWidth / 2, windowHeight / 2);           // bottom right
			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			gluPerspective(-45, (double)windowWidth / (double)windowHeight, 0.1, 100);
			glMatrixMode(GL_MODELVIEW_MATRIX);
			glTranslatef(0, 0, -5);
			drawCube();
		}

		glfwSwapBuffers(window);
		
		glfwPollEvents();

	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
	return 0;
}

