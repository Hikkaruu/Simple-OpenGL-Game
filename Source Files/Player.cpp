#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include "Player.h"
#include "MyShader.h"


void Player::Draw(float timeDelta, int platformNumber, std::vector<Platform>& platforms) {
	glBindVertexArray(vaoId);
	myShader.Bind();

	playerPosition.x = glm::max(-1.0f + cRadius, glm::min(1.0f - cRadius, playerPosition.x));
	playerPosition.y = glm::min(farTopPos, glm::max(playerPosition.y + velY, farBottomPos));

	canJump = false;
	if (playerPosition.y == farBottomPos) canJump = true;

	glm::mat4 mat4Model = glm::mat4(1.0f);
	mat4Model = glm::translate(mat4Model, playerPosition);
	myShader.setMat4Uniform("mat4Model", mat4Model);

	for (int i = 0; i < platformNumber; i++)
		if (CheckCollision(platforms[i])) Collision(platforms[i]);

	glDrawArrays(GL_TRIANGLE_FAN, 0, verticesNumber);

	if (canJump)
		velY = 0.0f;
	else if (playerPosition.y == farTopPos) 
		velY = glm::min(0.0f, velY - gravity * timeDelta);
	else 
		velY -= gravity * timeDelta;

	myShader.Unbind();
	glBindVertexArray(0);
}

void Player::Create(float positionAttribute[], const char* vertexShaderPath, const char* fragmentShaderPath, float radius, int vertices) {

	verticesNumber = vertices;
	cRadius = radius;
	playerPosition.y = -0.4f;
	farTopPos = 1.0f - radius;
	farBottomPos = groundUpperline + cRadius;

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	unsigned int posVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), positionAttribute, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	myShader.Create(vertexShaderPath, fragmentShaderPath);
	glBindVertexArray(0);
}

void Player::Move(Movement key, float deltaTime) {
	if (key == SPACE && canJump) velY = 0.0038f;
	if (key == D) playerPosition.x += velX * deltaTime;
	if (key == A)  playerPosition.x -=velX * deltaTime; 
}

void Player::RemoveVao() {
	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(1, &vaoId);
}

void Player::Collision(Platform platform) {

	float radius = cRadius * cRadius;

	if (closeY == platform.up && glm::abs(farX) < (0.5f * cRadius)) {
		if (closeX == platform.left) { 
			float firstTerm = (playerPosition.x - platform.left) * (playerPosition.x - platform.left);
			playerPosition.y = glm::sqrt(radius - firstTerm) + platform.up;

		} else if (closeX == platform.right) { 
			float firstTerm = (playerPosition.x - platform.right) * (playerPosition.x - platform.right);
			playerPosition.y = glm::sqrt(radius - firstTerm) + platform.up;

		} else {
			playerPosition.y = glm::max(playerPosition.y, platform.up + cRadius);
		}

		canJump = true;
	} 
	else if (closeY == platform.down) { 
		velY = glm::min(velY, 0.0f);

		if (closeX == platform.left) { 
			float firstTerm = (playerPosition.x - platform.left) * (playerPosition.x - platform.left);
			playerPosition.y = -glm::sqrt(radius - firstTerm) + platform.down;

		} else if (closeX == platform.right) { 
			float firstTerm = (playerPosition.x - platform.right) * (playerPosition.x - platform.right);
			playerPosition.y = -glm::sqrt(radius - firstTerm) + platform.down;

		} else {
			playerPosition.y = glm::min(playerPosition.y, platform.down - cRadius);
		}


	} else if (closeX == platform.left) { 
		playerPosition.x = platform.left - cRadius;

	} else if (closeX == platform.right) { 
		playerPosition.x = platform.right + cRadius;

	}
}

bool Player::CheckCollision(Platform platform) {
	closeX = glm::max(platform.left, glm::min(playerPosition.x, platform.right));
	closeY = glm::max(platform.down, glm::min(playerPosition.y, platform.up));

	farX = playerPosition.x - closeX;
	farY = playerPosition.y - closeY;
	float distanceSquare = (farX * farX) + (farY * farY);

	return (distanceSquare < (cRadius * cRadius));
}