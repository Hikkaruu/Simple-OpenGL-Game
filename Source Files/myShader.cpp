#include <GLAD/glad.h>
#include <GLM/glm.hpp>

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>

#include "MyShader.h"


void MyShader::Create(const char * vertexPath, const char * fragmentPath) {

	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vertexFStream;
	std::ifstream fragmentFStream;

	try {
		fragmentFStream.open(fragmentPath);
		vertexFStream.open(vertexPath);

		std::stringstream vrtxStringStream, frgmtStringStream;
		
		frgmtStringStream << fragmentFStream.rdbuf();
		vrtxStringStream << vertexFStream.rdbuf();
		
		fragmentFStream.close();
		vertexFStream.close();	

		fragmentSource = frgmtStringStream.str();
		vertexSource = vrtxStringStream.str();
		
	} 
	catch (std::ifstream::failure e) {
		std::cout << "File reading error" << std::endl;
	}

	const char* vertexSourceChar = vertexSource.c_str();
	const char* fragmentSourceChar = fragmentSource.c_str();

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSourceChar, NULL);
	glCompileShader(fragment);

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSourceChar, NULL);
	glCompileShader(vertex);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, fragment);
	glAttachShader(shaderProgram, vertex);
	glLinkProgram(shaderProgram);

	glDeleteShader(fragment);
	glDeleteShader(vertex);
}

void MyShader::Bind() { 
	glUseProgram(shaderProgram);
}

void MyShader::Unbind() { 
	glUseProgram(0);
}

void MyShader::setFloatUniform(const std::string & name, float val) 
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), val);
}

void MyShader::setMat4Uniform(const std::string & name, const glm::mat4 & mat) const 
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}




