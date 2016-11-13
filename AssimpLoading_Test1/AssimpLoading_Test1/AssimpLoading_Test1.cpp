// AssimpLoading_Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

#define GLEW_STATIC

// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 800;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 2.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


void initialise(GLFWwindow** window)
{
	std::cout << "Ami's OpenGL 3.3" << std::endl;

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	*window = glfwCreateWindow(WIDTH, HEIGHT, "Ami Learning Assimp OpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(*window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(*window, &width, &height);
	glViewport(0, 0, width, height);

}

void OpenFile(std::string filename, const aiScene** scene)
{
	Assimp::Importer importer;
	*scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate);

	if (!scene)
	{
		std::cerr << "Error loading " << filename.c_str() << " : " << std::string(importer.GetErrorString()) << std::endl;
	}
}

void Shaders(GLuint &shaderProgram)
{
	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void Mesh(const aiScene* scene, std::vector<GLfloat> &g_vp)
{
	int count = 0;
	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++)
	{
		const aiMesh* mesh = scene->mMeshes[m_i];
		count += mesh->mNumVertices;
		if (mesh->HasPositions())
		{
			for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++)
			{
				const aiVector3D* vp = &(mesh->mVertices[v_i]);
				g_vp.push_back(vp->x);
				g_vp.push_back(vp->y);
				g_vp.push_back(vp->z);
			}
		}
	}
}

void Rendering(int &counter, GLFWwindow* window, GLuint &shaderProgram, GLfloat *vertices)
{
	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, counter * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

						  // Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

}

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char** argv)
{


	GLFWwindow* window = NULL;
	initialise(&window);
	if (!window)
	{
		std::cout << "Could not initialise window\n";
		return -1;
	}

	GLuint shaderProgram;
	Shaders(shaderProgram);

	std::string filename = "C:\\University\\Projects\\AssimpLoading_Test1\\square_slanted.ply.obj";
	const aiScene* scene = NULL;
	OpenFile(filename, &scene);
	if (!scene)
	{
		return -1;
	}

	std::vector<GLfloat> g_vp;
	Mesh(scene, g_vp);


	// copy meshed vector to array in preperation for rendering
	GLfloat *vertices = new GLfloat[g_vp.size()];
	int counter = 0;
	for (std::vector<GLfloat>::const_iterator itr = g_vp.begin(); itr != g_vp.end(); itr++)
	{
		vertices[counter] = *itr;
		counter++;
	}


	Rendering(counter, window, shaderProgram, vertices);


	delete[] vertices;  // cleanup, to ensure no memory leak occurs


	return 0;
}





