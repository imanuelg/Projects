#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

class Shader
{
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar * fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		// Print linking errors if any
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	// Uses the current shader
	void Use()
	{
		glUseProgram(this->Program);
	}
};

#endif


#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
class Shader_Loader
{
private:

	std::string ReadShader(char *filename)
	{
		std::string shaderCode;
		std::ifstream file(filename, std::ios::in);

		if (!file.good())
		{
			std::cout << "Can't read file " << filename << std::endl;
			std::terminate();
		}

		file.seekg(0, std::ios::end);
		shaderCode.resize((unsigned int)file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&shaderCode[0], shaderCode.size());
		file.close();
		return shaderCode;
	}

	GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName)
	{
		int compile_result = 0;

		GLuint shader = glCreateShader(shaderType);
		const char *shader_code_ptr = source.c_str();
		const int shader_code_size = source.size();

		glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

		//check for errors
		if (compile_result == GL_FALSE)
		{

			int info_log_length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> shader_log(info_log_length);
			glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
			std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
			return 0;
		}
		return shader;
	}

public:

	Shader_Loader(void) { }
	~Shader_Loader(void) { }
	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename)
	{
		//read the shader files and save the code
		std::string vertex_shader_code = ReadShader(VertexShaderFilename);
		std::string fragment_shader_code = ReadShader(FragmentShaderFilename);

		GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
		GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

		int link_result = 0;
		//create the program handle, attatch the shaders and link it
		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);
		//check for link errors
		if (link_result == GL_FALSE)
		{

			int info_log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> program_log(info_log_length);
			glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
			std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
			return 0;
		}
		return program;
	}

};
#endif

