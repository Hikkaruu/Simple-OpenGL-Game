#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Platform.h"
#include "MyShader.h"
#include "Ground.h"


Platform::Platform(float positions[], unsigned int indices[], const char * vertexShaderPath, const char * fragmentShaderPath)
	:Ground(positions, indices, vertexShaderPath, fragmentShaderPath) { 

	originalUpPos = up;
	originalDownPos = down;
	originalLeftPos = left;
	originalRightPos = right;
}

void Platform::Draw(glm::vec3 translationVector) {

	glBindVertexArray(vaoId);
	myShader.Bind();

	up = originalUpPos + translationVector.y;
	down = originalDownPos + translationVector.y;
	left = originalLeftPos + translationVector.x;
	right = originalRightPos + translationVector.x;

	glm::mat4 mat4Model = glm::mat4(1.0f); 
	mat4Model = glm::translate(mat4Model, translationVector);
	myShader.setMat4Uniform("mat4Model", mat4Model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	myShader.Unbind();
	glBindVertexArray(0);
}

