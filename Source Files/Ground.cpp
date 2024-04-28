#include <GLAD/glad.h>
#include <GLM/glm.hpp>

#include "MyShader.h"
#include "Ground.h"


Ground::Ground(float positions[], unsigned int indices[], const char * vertexShaderPath, const char * fragmentShaderPath) {

	up = glm::max(positions[1], glm::max(positions[4], positions[7]));
	down = glm::min(positions[1], glm::min(positions[4], positions[7]));
	left = glm::min(positions[0], glm::min(positions[3], positions[6]));
	right = glm::max(positions[0], glm::max(positions[3], positions[6]));
	
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	unsigned int positionVBO;
	glGenBuffers(1, &positionVBO);

	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	unsigned int positionEBO;
	glGenBuffers(1, &positionEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, positionEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	myShader.Create(vertexShaderPath, fragmentShaderPath);

	glBindVertexArray(0);
}

Ground::~Ground() {

}

void Ground::Draw() {

	glBindVertexArray(vaoId);
	myShader.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	myShader.Unbind();
	glBindVertexArray(0);
}

void Ground::RemoveVao() {

	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(1, &vaoId);
}

