#include "ShaderHelpers.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static bool ReadFile(const char* filename, std::string& stringOut)
{
	std::ifstream file;
	file.open(filename);
	if (!file.good())
	{
		return false;
	}

	std::stringstream ss;
	ss << file.rdbuf();
	stringOut = ss.str();
	return true;
}

static bool DidShaderCompile(GLuint id, GLuint type)
{
	const int bufSize = 1024;
	char msgBuf[bufSize];
	GLint success;
	
	if (type == GL_PROGRAM)
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
	}
	else
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	}
	if (!success)
	{
		if (type == GL_PROGRAM)
		{
			glGetProgramInfoLog(id, bufSize, NULL, msgBuf);
			std::cout << "Error linking program:\n";
		}
		else
		{
			glGetShaderInfoLog(id, bufSize, NULL, msgBuf);
			if (type == GL_VERTEX_SHADER)
			{
				std::cout << "Error compiling vertex shader:\n";
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				std::cout << "Error compiling fragment shader:\n";
			}
		}
		std::cout << msgBuf << std::endl;
		return false;
	}

	return true;
}

GLuint LoadProgram(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	std::string vertStrOut, fragStrOut;
	if (!ReadFile(vertexShaderFile, vertStrOut))
	{
		std::cout << "Couldn't read vertex shader file: " << vertexShaderFile << std::endl;
		return 0;
	}

	if (!ReadFile(fragmentShaderFile, fragStrOut))
	{
		std::cout << "Couldn't read fragment shader file: " << fragmentShaderFile << std::endl;
		return 0;
	}
	
	const char* vertShaderCode = vertStrOut.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShaderCode, NULL);
	glCompileShader(vertexShader);
	if (!DidShaderCompile(vertexShader, GL_VERTEX_SHADER))
	{
		return 0;
	}

	const char* fragShaderCode = fragStrOut.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);
	glCompileShader(fragmentShader);
	if (!DidShaderCompile(fragmentShader, GL_FRAGMENT_SHADER))
	{
		return 0;
	}

	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	if (!DidShaderCompile(shaderID, GL_PROGRAM))
	{
		return 0;
	}

	// No longer needed at this point as they have already been linked into the shader program.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderID;
}
